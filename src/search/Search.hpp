#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <string>

#include "ArrayList.h"
#include "Trie.hpp"
#include "MaxHeap.hpp"

#include "Result.hpp"
#include "Argument.hpp"

class Search {

private:
    ArrayList<std::string>* file_paths;
    std::string frequency_table_location;
    int tablewidth;

public:
    Trie* vocabTrie;
    // FIXME: This only works within the same process at the moment
    Search(std::string frequency_table_location,
           std::string vocab_trie_location,
           std::string book_paths_location,
           std::string table_width_location) : 
        frequency_table_location(frequency_table_location), 
        // vocabTrie(Trie::deserialize(vocab_trie_location)),
        file_paths(new ArrayList<std::string>)
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
    }

    Search(std::string frequency_table_location,
            Trie* vocab_trie,
           std::string book_paths_location,
           std::string table_width_location) : 
        frequency_table_location(frequency_table_location), 
        vocabTrie(vocab_trie),
        file_paths(new ArrayList<std::string>)
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
    }
    
    void search(ArrayList<Argument> searchArgs, int k) {

        std::ifstream frequencyTableFile(frequency_table_location,
                                         std::ios::binary);
        int frequency;
        MaxHeap<Result*> results;

        for (int document_index = 0; document_index < file_paths->length;
             document_index++) {
            std::string documentName = file_paths->get(document_index);
            int score = 0;
            for (int j = 0; j < searchArgs.length; j++) {
                TrieNode* node = vocabTrie->check(searchArgs[j].word);
                if (node == nullptr) {
                    continue;
                }
                frequencyTableFile.seekg(
                    (document_index * tablewidth + node->wordIndex) *
                        sizeof(int),
                    std::ios::beg);
                frequencyTableFile.read(reinterpret_cast<char*>(&frequency),
                                        sizeof(int));

                score += frequency;
            }
            results.insert(new Result(documentName, score), score);
        }

        frequencyTableFile.close();

        for (int i = 0; i < k; i++) {
            Result* result = results.max();
            std::cout << result->name << ": " << result->score << std::endl;
        }
    }
};

#endif
