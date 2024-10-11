#include "index/file/DocumentSet.hpp"
#include "index/file/FileReader.hpp"
#include "core/ArrayList.h"
#include <iostream>
#include <ostream>

int main() {
    DocumentSet* documents = new DocumentSet(DATA_DIR);

    ArrayList<std::string>* document_paths = documents->getDocumentPaths();

    for(int i = 0; i < document_paths->length; i++) {
        std::cout << "Reading: " << document_paths->get(i) << std::endl;
        FileReader reader = FileReader(document_paths->get(i));
        ArrayList<std::string> words = reader.read();
        for(int i = 0; i < words.length; i++) {
            std::cout << words.get(i) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
