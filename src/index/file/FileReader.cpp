#include "FileReader.hpp"
#include <iostream>
FileReader::FileReader(const std::string& filename) : file(filename) {};

FileReader::~FileReader() {
    file.close();
}

std::vector<std::string> FileReader::read() {
    std::vector<std::string> words;
    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
    return words;
}

