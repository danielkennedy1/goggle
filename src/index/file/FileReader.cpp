#include "FileReader.hpp"

FileReader::FileReader(const std::string& filename) : file(filename) {};

FileReader::~FileReader() {
    file.close();
}

ArrayList<std::string>* FileReader::read() {
    ArrayList<std::string>* words = new ArrayList<std::string>();
    std::string word;
    while (file >> word) {
        for (auto& x : word) { 
            x = tolower(x); 
        } 
        words->append(word);
    }
    return words;
}

