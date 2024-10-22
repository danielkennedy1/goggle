#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <fstream>
#include <string>

#include "ArrayList.h"
#include "MaxHeap.hpp"
#include "Trie.hpp"

#include "Argument.hpp"
#include "Result.hpp"

class Search {

private:
    ArrayList<std::string>* file_paths;
    ArrayList<int>* file_lengths;
    std::string frequency_table_location;
    int tablewidth;

public:
    Trie* vocabTrie;

    Search(std::string frequency_table_location,
           std::string vocab_trie_location,
           std::string book_paths_location,
           std::string book_lengths_location,
           std::string table_width_location) : 
        frequency_table_location(frequency_table_location), 
        file_paths(new ArrayList<std::string>),
        file_lengths(new ArrayList<int>)
        {
        vocabTrie->loadFrom(vocab_trie_location);
        std::ifstream paths_in(book_paths_location);
        std::string path;
        while (paths_in >> path) {
            file_paths->append(path);
        }
        paths_in.close();

        std::ifstream table_width_file(table_width_location);
        std::string table_width_str;
        table_width_file >> table_width_str;
        tablewidth = std::stoi(table_width_str);
        table_width_file.close();

        std::ifstream lengths_in(book_lengths_location);
        std::string length;
        while (lengths_in >> length) {
            file_lengths->append(std::stoi(length));
        }
        lengths_in.close();
    }

    ArrayList<Result*>* search(ArrayList<Argument> searchArgs, int k) {

        std::cout << "ARGUMENTS: " << std::endl;

        for(int i = 0; i < searchArgs.length; i++) {
            std::cout << "ARGUMENT " << i+1 << std::endl;
            std::cout << "term:" << searchArgs[i].word << std::endl;
            std::cout << "required:" << searchArgs[i].required << std::endl;
            std::cout << "negated:" << searchArgs[i].negated << std::endl;
        }

        std::ifstream frequencyTableFile(frequency_table_location, std::ios::binary);

        // NOTE: 1st Dimension: arg, 2nd: Document

        ArrayList<ArrayList<int>*>* frequencies = new ArrayList<ArrayList<int>*>;
        ArrayList<int>* occurrences = new ArrayList<int>;

        ArrayList<ArrayList<double>*>* tf_scores = new ArrayList<ArrayList<double>*>;
        ArrayList<ArrayList<double>*>* tf_idf_scores = new ArrayList<ArrayList<double>*>;

        for (int argument_index = 0; argument_index < searchArgs.length; argument_index++) {

            frequencies->append(new ArrayList<int>);
            tf_scores->append(new ArrayList<double>);
            tf_idf_scores->append(new ArrayList<double>);
            occurrences->append(0);

            for (int document_index = 0; document_index < file_paths->length; document_index++) {

                std::string term = searchArgs[argument_index].word;
                std::string documentName = file_paths->get(document_index);
                int documentLength = file_lengths->get(document_index);

                TrieNode* node = vocabTrie->check(term);
                if (node == nullptr) {
                    continue;
                }

                int frequency;
                frequencyTableFile.seekg((document_index * tablewidth + node->wordIndex) * sizeof(int), std::ios::beg);
                frequencyTableFile.read(reinterpret_cast<char*>(&frequency), sizeof(int));
                frequencies->get(argument_index)->append(frequency);
                tf_scores->get(argument_index)->append(static_cast<double>(frequencies->get(0)->get(document_index)) / static_cast<double>(file_lengths->get(document_index)));

                if (frequency > 0) occurrences->get(argument_index)++;
            }

            double idf = log10((static_cast<double>(file_paths->length)) / static_cast<double>(1 + occurrences->get(argument_index)));

            for (int i = 0; i < file_paths->length; i++)
                tf_idf_scores->get(argument_index)->append(idf * tf_scores->get(argument_index)->get(i));
        }

        MaxHeap<Result*> results;
        for (int i = 0; i < file_paths->length; i++) {
            std::cout << "Document: " << file_paths->get(i);
            bool zero_flag = false;
            double score = 0;
            for (int argument_index = 0; argument_index < searchArgs.length; argument_index++) {
                double tf_idf = tf_idf_scores->get(argument_index)->get(i);

                if (searchArgs[argument_index].required && tf_idf == 0.0) zero_flag = true;

                if (searchArgs[argument_index].negated && score != 0) {
                    score -= tf_idf;
                } else {
                    score += tf_idf;                
                }
            }

            std::cout << " zero_flag = " << zero_flag << std::endl;

            if (zero_flag) score = 0;

            std::cout << "score = " << score << std::endl;

            results.insert(new Result(file_paths->get(i), score), score * 10e7);
        }

        frequencyTableFile.close();

        ArrayList<Result*>* returnValue = new ArrayList<Result*>();

        for (int i = 0; i < k; i++) {
            returnValue->append(results.max());
        }
        return returnValue;
    }
};

#endif
