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
#include "Autocomplete.hpp"

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

        Book* documents = indexer.getDocuments();
        MaxHeap<Result*> results;

        for (int document_index = 0; document_index < indexer.getNumOfDocuments(); document_index++) {
            std::string documentName = documents[document_index].name;
            int score = 0;
            for (int j = 0; j < searchArgs.length; j++) {
                TrieNode* node = vocabTrie->check(searchArgs[j].word);
                if (node == nullptr) {
                    continue;
                }
                int frequency = frequenciesTable[document_index][node->wordIndex];
                score += frequency;
            }
            results.insert(new Result(documentName, score), score);
        }

        for (int i = 0; i < K; i++) {
            Result* result = results.max();
            std::cout << result->name << ": " << result->score << std::endl;
        }
    }
};
