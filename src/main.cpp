#include "index/file/DocumentSet.hpp"
#include "index/file/FileReader.hpp"
#include "core/ArrayList.h"
#include "index/FrequencyCounter.hpp"
#include <iostream>
#include <string>
#include <ostream>

int main() {
    std::cout << "Welcome to Goggle!\nPlease enter the path to the directory of books (in .txt format) that you would like to index." <<std::endl;
    std::string documentsPath = "/home/conorc/ISE/goggle/data/simple_documents";
    // std::string documentsPath;
    // std::cin >> documentsPath;
    
    
    DocumentSet* documents = new DocumentSet(documentsPath);
    ArrayList<std::string>* document_paths = documents->getDocumentPaths();

    FrequencyCounter counter = FrequencyCounter(document_paths->length);

    std::cout << "Indexing documents..." << std::endl;

    for(int i = 0; i < document_paths->length; i++) {
        std::cout << "Indexing: " << document_paths->get(i) << std::endl;
        FileReader reader = FileReader(document_paths->get(i));
        ArrayList<std::string> words = reader.read();
        counter.addDocument(i, &words, DocumentSet::parseDocNameFromPath(document_paths->get(i)));
        counter.indexDocument(i);
    }

    TrieNode* vocabTrie = counter.getVocabTrie();
    // TrieNode* titleTrie = counter.getTitleTrie();
    ArrayList<int>* frequencyTable = counter.getFreqTable();

    for(int i = 0; i < document_paths->length; i++) {
        FileReader reader = FileReader(document_paths->get(i));
        ArrayList<std::string> words = reader.read();
        for(int j = 0; j < words.length; j++) {
            std::cout << words.get(j) << ": ";
            int wordIndex = vocabTrie->check(words[j])->wordIndex;
            int frequency = frequencyTable[i].get(wordIndex);
            std::cout << frequency << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
