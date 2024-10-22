#include <strstream>
#include <filesystem>
#include <string>
#include <iostream>

#include "DocumentSet.hpp"
#include "FrequencyCounter.hpp"
#include "FileReader.hpp"
#include "Book.hpp"

class Index {
public:
    Index(std::string documents_path) {
        DocumentSet* documents = new DocumentSet(documents_path);
        documentPaths = documents->getDocumentPaths();
        numOfDocuments = documentPaths->length;
        counter = new FrequencyCounter(numOfDocuments);       
    }

    void persist(std::string frequency_table_location,
                 std::string vocab_trie_location,
                 std::string document_path_location,
                 std::string table_width_location) {

        std::filesystem::remove_all(SERIALIZED_DATA_DIR);
        std::filesystem::create_directory(SERIALIZED_DATA_DIR);

        persist_frequencies(frequency_table_location);

        persist_vocab_trie(vocab_trie_location);

        persist_document_paths(document_path_location);

        persist_table_width(table_width_location);

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

    FrequencyCounter* counter = nullptr;
private:
    int table_width;

    ArrayList<std::string>* documentPaths;
    int numOfDocuments;

    void persist_frequencies(std::string frequency_table_location) {

        ArrayList<int>* frequencies = counter->getFreqTable();

        for (int i = 0; i < numOfDocuments; i++) {
            if (frequencies[i].length > table_width)
                table_width = frequencies[i].length;
        }

        for (int i = 0; i < numOfDocuments; i++) {
            frequencies[i].resize(table_width);
        }

        ArrayList<int>* flat_frequencies = new ArrayList<int>();

        for (int i = 0; i < numOfDocuments; i++) {
            for (int j = 0; j < table_width; j++) {
                flat_frequencies->append(frequencies[i][j]);
            }
        }
        flat_frequencies->serialize(frequency_table_location);
    }

    void persist_vocab_trie(std::string vocab_trie_location) {
        Trie* vocabTrie = counter->getVocabTrie();

        vocabTrie->serialize(vocab_trie_location);
    }

    void persist_document_paths(std::string document_path_location) {
        Book* documents = counter->documents;

        std::strstream book_paths;

        for (int i = 0; i < numOfDocuments; i++) {
            book_paths << documents[i].path << " ";
        }

        std::string pathsString = book_paths.str();

        std::ofstream paths_out(document_path_location);

        if (paths_out.is_open()) {
            paths_out.write(pathsString.c_str(), pathsString.length());
        }

        paths_out.close();
    }

    void persist_table_width(std::string table_width_location) {
        std::ofstream table_width_file(table_width_location);

        std::string table_width_str = std::to_string(table_width);

        table_width_file.write(table_width_str.c_str(),
                               table_width_str.length());
        table_width_file.close();
    }
};
