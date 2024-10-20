#include <iostream>
#include <string>
#include <ostream>
#include "index/file/FileReader.hpp"
#include "core/ArrayList.h"
#include "Parser.hpp"
#include "Index.hpp"
#include "Autocomplete.hpp"

int main() {
    std::cout << "Welcome to Goggle!\nPlease enter the path to the directory of books (in .txt format) that you would like to index." <<std::endl;
    // std::string documentsPath = GUTENBERG_DATA_DIR;
    std::string documentsPath = TEST_DATA_DIR;
    // std::string documentsPath;
    // std::cin >> documentsPath;
    
    Indexer indexer(documentsPath);

    indexer.index();

    Autocomplete autocomplete(indexer.getVocabTrie());

    while (true) {
        system("clear");
        std::cout << "Welcome to Goggle! Enter \"search\" to search for a book or enter \"autocomplete\" to use our autocomplete feature!\n";
        std::string choice;
        std::cin >> choice;

        if (choice == "autocomplete") {
            autocomplete.start();
            continue;
        }

        std::string query;

        std::cout << "Please enter a search term. It can be multiple words separated by logical operators (AND and OR). Negation can also be used (NOT water AND wave): " << std::endl;
        
        std::cin.ignore();
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
            if (searchArgs[i].word.size() < 8) {
                std::cout << searchArgs[i].word << "\t" << "\t";
            } else {
                std::cout << searchArgs[i].word << "\t";
            }
        }
        std::cout << std::endl;

        for (int i = 0; i < numOfDocuments; i++) {
            std::string documentName = documents[i].name;
            if(documentName.size() < 8) {
                std::cout << documentName << "\t" << "\t";    
            } else {
                std::cout << documentName << "\t";
            }
            for (int j = 0; j < searchArgs.length; j++) {
                std::cout << frequencies[i][j] << "\t\t";
            }
            std::cout << std::endl;
        }
    }
};
