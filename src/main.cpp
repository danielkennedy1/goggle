#include "core/ArrayList.h"
#include "index/FrequencyCounter.hpp"
#include "index/file/FileReader.hpp"
#include "MaxHeap.hpp"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include "core/ArrayList.h"
#include "Parser.hpp"
#include "Indexer.hpp"

#define K 5

struct Result {
    std::string name;
    int score;
    Result(std::string name, int score) : name(name), score(score) {}
};

int main() {
    std::cout << "Welcome to Goggle!\nPlease enter the path to the directory "
                 "of books (in .txt format) that you would like to index."
              << std::endl;
    std::string documentsPath = GUTENBERG_DATA_DIR;
    
    Indexer indexer(documentsPath);

    indexer.index();

    std::string query;

    std::cout << "Please enter a search term. It can be multiple words separated by spaces. i.e. (database computer internet): ";
    std::getline(std::cin, query);

    Parser parser(query);

    ArrayList<Argument> searchArgs = parser.parse();


    ArrayList<int>* frequenciesLists = indexer.getFrequencyTable();

    int tablewidth = 0;
    for (int i = 0; i < indexer.getNumOfDocuments(); i++) {
        if (frequenciesLists[i].length > tablewidth) tablewidth = frequenciesLists[i].length;
    }
    std::cout << "tableWidth: " << tablewidth << std::endl;

    for (int i = 0; i < indexer.getNumOfDocuments(); i++) {
        frequenciesLists[i].resize(tablewidth);
    }

    ArrayList<int>* allFrequencies = new ArrayList<int>();

    for (int i = 0; i < indexer.getNumOfDocuments(); i++) {
        for (int j = 0; j < tablewidth; j++) {
            allFrequencies->append(frequenciesLists[i][j]);
        }
    }

    TrieNode* vocabTrie = indexer.getVocabTrie();

    std::string frequenciesTableLocation = std::string(SERIALIZED_DATA_DIR) + std::string("/frequencies_table.bin");
    allFrequencies->serialize(frequenciesTableLocation);

    ArrayList<int> deserFrequenciesTable = ArrayList<int>::deserialize(frequenciesTableLocation);

    Book* documents = indexer.getDocuments();

    MaxHeap<Result*> results;

    std::ifstream file(frequenciesTableLocation, std::ios::binary);
    int frequency;

    for (int document_index = 0; document_index < indexer.getNumOfDocuments(); document_index++) {
        std::string documentName = documents[document_index].name;
        int score = 0;
        for (int j = 0; j < searchArgs.length; j++) {
            TrieNode* node = vocabTrie->check(searchArgs[j].word);
            if (node == nullptr) {
                continue;
            }
            file.seekg((document_index * tablewidth + node->wordIndex) * sizeof(int), std::ios::beg);
            file.read(reinterpret_cast<char*>(&frequency), sizeof(int));

            score += frequency;
        }
        results.insert(new Result(documentName, score), score);
    }

    file.close();

    for (int i = 0; i < K; i++) {
        Result* result = results.max();
        std::cout << result->name << ": " << result->score << std::endl;
    }
};
