#include "core/ArrayList.h"
#include "index/FrequencyCounter.hpp"
#include "index/file/FileReader.hpp"
#include "MaxHeap.hpp"
#include <iostream>
#include <ostream>
#include "core/ArrayList.h"
#include "Parser.hpp"
#include "Index.hpp"

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

    for (int i = 0; i < numOfDocuments; i++) {
        std::string documentName = documents[i].name;
        for (int j = 0; j < searchArgs.length; j++) {
            TrieNode* node = vocabTrie->check(searchArgs[j].word);
            if (node == nullptr) {
                frequencies[i][j] = 0;
                continue;
            }
            int index = node->wordIndex;
            int frequency = frequenciesTable[i][index];
            frequencies[i][j] = frequency;
        }
    }
    

    std::cout << '\t' << '\t';
    for (int i = 0; i < searchArgs.length; i++) {
        std::cout << searchArgs[i].word << '\t';
    }
    std::cout << std::endl;

    for (int i = 0; i < numOfDocuments; i++) {
        std::string documentName = documents[i].name;
        if(documentName.size() < 10) {
            std::cout << documentName << '\t' << '\t';    
        } else {
            std::cout << documentName << '\t';
        }
        for (int j = 0; j < searchArgs.length; j++) {
            std::cout << frequencies[i][j] << '\t';
        }
        std::cout << std::endl;
    }
};
