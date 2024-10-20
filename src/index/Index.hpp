#ifndef INDEX_H
#define INDEX_H
#include "ArrayList.h"
#include "DocumentSet.hpp"
#include "HashMap.hpp"
#include "FrequencyCounter.hpp"
#include <string>

class Indexer {
public:
    Indexer(std::string directory) {
        DocumentSet* documents = new DocumentSet(directory);
        documentPaths = documents->getDocumentPaths();
        numOfDocuments = documentPaths->length;
        counter = new FrequencyCounter(numOfDocuments);       
    }

    ~Indexer() {
        delete documentPaths;
        delete counter;
    }

    void index() {
        std::cout << "Indexing documents..." << std::endl;

        for (int i = 0; i < numOfDocuments; i++) {
            std::cout << "Indexing: " << documentPaths->get(i) << std::endl;
            FileReader reader = FileReader(documentPaths->get(i));
            ArrayList<std::string>* words = reader.read();

            counter->addDocument(i, words, documentPaths->get(i));
            counter->indexDocument(i);
        }

        std::cout << "Documents indexed: " << std::endl;

        for (int i = 0; i < counter->numOfDocuments; i++) {
            std::cout << i << ": " << counter->documents[i].name << std::endl;
        }
    }

    TrieNode* getVocabTrie() {
        return counter->getVocabTrie();
    }

    ArrayList<int>* getFrequencyTable() {
        return counter->getFreqTable();
    }

    int getNumOfDocuments() {
        return numOfDocuments;
    }

    book* getDocuments() {
        return counter->documents;
    }

private:
    FrequencyCounter* counter = nullptr;
    ArrayList<std::string>* documentPaths;
    int numOfDocuments;
};
#endif