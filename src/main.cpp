#include "core/ArrayList.h"
#include "index/FrequencyCounter.hpp"
#include "index/file/FileReader.hpp"
#include "MaxHeap.hpp"
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
    // std::string documentsPath;
    // std::cin >> documentsPath;
    
    Indexer indexer(documentsPath);

    indexer.index();

    std::string query;

    std::cout << "Please enter a search term. It can be multiple words separated by spaces. i.e. (database computer internet): ";
    std::getline(std::cin, query);

    Parser parser(query);

    ArrayList<Argument> searchArgs = parser.parse();

    ArrayList<int>* frequenciesTable = indexer.getFrequencyTable();
    TrieNode* vocabTrie = indexer.getVocabTrie();

    int frequencies[indexer.getNumOfDocuments()][searchArgs.length];

    book* documents = indexer.getDocuments();
    int numOfDocuments = indexer.getNumOfDocuments();

    MaxHeap<Result*> results;

    for (int i = 0; i < numOfDocuments; i++) {
        std::string documentName = documents[i].name;
        int score = 0;
        for (int j = 0; j < searchArgs.length; j++) {
            TrieNode* node = vocabTrie->check(searchArgs[j].word);
            if (node == nullptr) {
                frequencies[i][j] = 0;
                continue;
            }
            int index = node->wordIndex;
            int frequency = frequenciesTable[i][index];
            frequencies[i][j] = frequency;
            score += frequency;
        }
        results.insert(new Result(documentName, score), score);
    }

    for (int i = 0; i < K; i++) {
        Result* result = results.max();
        std::cout << result->name << ": " << result->score << std::endl;
    }
};
