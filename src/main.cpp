#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#include "Trie.hpp"
#include "MaxHeap.hpp"
#include "ArrayList.h"
#include "Parser.hpp"
#include "Index.hpp"

#include "Result.hpp"

#define K 5

std::string frequenciesTableLocation = std::string(SERIALIZED_DATA_DIR) + std::string("/frequencies_table.bin");
std::string vocabTrieLocation = std::string(SERIALIZED_DATA_DIR) + std::string("/vocab_trie.bin");
std::string bookPathsLocation = std::string(SERIALIZED_DATA_DIR) + std::string("/book_paths.txt");
std::string tableWidthLocation = std::string(SERIALIZED_DATA_DIR) + std::string("/table_width.txt");


void index() {
    Index index(GUTENBERG_DATA_DIR);
    index.index();
    index.persist(
           frequenciesTableLocation,
           vocabTrieLocation,
           bookPathsLocation,
           tableWidthLocation
            );
};

void search() {
    std::string query;

    std::cout << "Please enter a search term. It can be multiple words separated by spaces. i.e. (database computer internet): ";
    std::getline(std::cin, query);

    Parser parser(query);

    ArrayList<Argument> searchArgs = parser.parse();

    std::ifstream paths_in(bookPathsLocation);

    ArrayList<std::string>* file_paths = new ArrayList<std::string>();

    std::cout << "getting paths..." << std::endl;
    std::string path;
    while (paths_in >> path) {
        file_paths->append(path);
    }
                                                      
    paths_in.close();

    std::ifstream table_width_file(tableWidthLocation);

    std::string table_width_str;
    table_width_file >> table_width_str;

    int tablewidth = std::stoi(table_width_str);

    std::cout << "before deserialize" << std::endl;
                                                      
    TrieNode deserVocabTrie = TrieNode::deserialize(vocabTrieLocation);

    std::cout << "numOfWords: " << *deserVocabTrie.numOfWords << std::endl;

    std::ifstream frequencyTableFile(frequenciesTableLocation, std::ios::binary);
    int frequency;

    MaxHeap<Result*> results;

    for (int document_index = 0; document_index < file_paths->length; document_index++) {
        std::string documentName = file_paths->get(document_index);
        int score = 0;
        for (int j = 0; j < searchArgs.length; j++) {
            TrieNode* node = deserVocabTrie.check(searchArgs[j].word);
            if (node == nullptr) {
                continue;
            }
            frequencyTableFile.seekg((document_index * tablewidth + node->wordIndex) * sizeof(int), std::ios::beg);
            frequencyTableFile.read(reinterpret_cast<char*>(&frequency), sizeof(int));

            score += frequency;
        }
        results.insert(new Result(documentName, score), score);
    }

    frequencyTableFile.close();

    for (int i = 0; i < K; i++) {
        Result* result = results.max();
        std::cout << result->name << ": " << result->score << std::endl;
    }
}


int main() {
    index();
    std::cout << "INDEX FINISHED" << std::endl;
    search();
};

