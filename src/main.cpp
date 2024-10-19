#include <iostream>
#include <string>
#include <ostream>
#include "index/file/FileReader.hpp"
#include "core/ArrayList.h"
#include "Parser.hpp"
#include "Index.hpp"

int main() {
    std::cout << "Welcome to Goggle!\nPlease enter the path to the directory of books (in .txt format) that you would like to index." <<std::endl;
    std::string documentsPath = TEST_DATA_DIR;
    // std::string documentsPath;
    // std::cin >> documentsPath;
    
    Indexer indexer(documentsPath);

    std::string searchTerm;

    std::cout << "Please enter a search term. It can be multiple words separated by spaces. i.e. (database computer internet): ";
    std::getline(std::cin, searchTerm);

    ArrayList<std::string> searchTerms = Parser::splitString(searchTerm);
    
    // TrieNode* vocabTrie = counter.getVocabTrie();
    // ArrayList<int>* frequenciesTable = counter.getFreqTable();

    // int frequencies[counter.numOfDocuments][searchTerms.length];


    // for (int i = 0; i < counter.numOfDocuments; i++) {
    //     std::string documentName = counter.documents[i].name;
    //     for (int j = 0; j < searchTerms.length; j++) {
    //         TrieNode* node = vocabTrie->check(searchTerms[j]);
    //         if (node == nullptr) {
    //             frequencies[i][j] = 0;
    //             continue;
    //         }
    //         int index = node->wordIndex;
    //         int frequency = frequenciesTable[i][index];
    //         frequencies[i][j] = frequency;
    //     }
    // }

    // std::cout << '\t' << '\t';
    // for (int i = 0; i < searchTerms.length; i++) {
    //     std::cout << searchTerms[i] << '\t';
    // }
    // std::cout << std::endl;

    // for (int i = 0; i < counter.numOfDocuments; i++) {
    //     std::string documentName = counter.documents[i].name;
    //     std::cout << documentName << '\t';
    //     for (int j = 0; j < searchTerms.length; j++) {
    //         std::cout << frequencies[i][j] << '\t';
    //     }
    //     std::cout << std::endl;
    // }
};
