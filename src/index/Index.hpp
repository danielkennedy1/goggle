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
        ArrayList<std::string>* document_paths = documents->getDocumentPaths();
        counter = new FrequencyCounter(document_paths->length);

        std::cout << "Indexing documents..." << std::endl;

        for (int i = 0; i < document_paths->length; i++) {
            std::cout << "Indexing: " << document_paths->get(i) << std::endl;
            FileReader reader = FileReader(document_paths->get(i));
            ArrayList<std::string>* words = reader.read();

            counter->addDocument(i, words, document_paths->get(i));
            counter->indexDocument(i);
        }

        std::cout << "Documents indexed: " << std::endl;

        for (int i = 0; i < counter->numOfDocuments; i++) {
            std::cout << i << ": " << counter->documents[i].name << std::endl;
        }
    }

    FrequencyCounter* counter = nullptr;
};
#endif