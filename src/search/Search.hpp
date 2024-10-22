#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <fstream>
#include <string>

#include "ArrayList.h"
#include "Trie.hpp"
#include "MaxHeap.hpp"

#include "Result.hpp"
#include "Argument.hpp"

class Search {

private:
    ArrayList<std::string>* file_paths;
    ArrayList<int>* file_lengths;
    std::string frequency_table_location;
    int tablewidth;

public:
    TrieNode* vocabTrie;
    // FIXME: This only works within the same process at the moment
    Search(std::string frequency_table_location,
           std::string vocab_trie_location,
           std::string book_paths_location,
           std::string book_lengths_location,
           std::string table_width_location) : 
        frequency_table_location(frequency_table_location), 
        vocabTrie(TrieNode::deserialize(vocab_trie_location)),
        file_paths(new ArrayList<std::string>),
        file_lengths(new ArrayList<int>)
        {

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

    Search(std::string frequency_table_location,
            TrieNode* vocab_trie,
            std::string book_paths_location,
            std::string book_lengths_location,
            std::string table_width_location) : 
        frequency_table_location(frequency_table_location), 
        vocabTrie(vocab_trie),
        file_paths(new ArrayList<std::string>),
        file_lengths(new ArrayList<int>)
        {

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

        std::ifstream lengths_in(book_lengths_location);
        std::string length;
        while (lengths_in >> length) {
            file_lengths->append(std::stoi(length));
        }
        lengths_in.close();
    }
    
    // FIXME: put in negation logic here
    ArrayList<Result*>* search(ArrayList<Argument> searchArgs, int k) {

        std::ifstream frequencyTableFile(frequency_table_location, std::ios::binary);

        int frequency;
        ArrayList<int> frequencies;

        int documents_with_term = 0;

        for (int document_index = 0; document_index < file_paths->length; document_index++) {
            std::string documentName = file_paths->get(document_index);
            int documentLength = file_lengths->get(document_index);
            int score = 0;
            std::string term = searchArgs[0].word;
            TrieNode* node = vocabTrie->check(term);

            if (node == nullptr) {
                continue;
            }

            frequencyTableFile.seekg((document_index * tablewidth + node->wordIndex) * sizeof(int), std::ios::beg);
            frequencyTableFile.read(reinterpret_cast<char*>(&frequency), sizeof(int));

            frequencies.append(frequency);

            if (frequency > 0) documents_with_term++;
        }

        MaxHeap<Result*> results;
        
        double idf = log10((static_cast<double>(file_paths->length)) / static_cast<double>(1 + documents_with_term));

        for (int i = 0; i < file_paths->length; i++) {
            double tf = static_cast<double>(frequencies.get(i)) / static_cast<double>(file_lengths->get(i));
            results.insert(new Result(file_paths->get(i), tf * idf), (tf * idf) * 10e7);
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
