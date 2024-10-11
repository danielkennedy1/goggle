#include "FileReader.hpp"

FileReader::FileReader(const std::string& filename) : file(filename) {};

FileReader::~FileReader() {
    file.close();
}

ArrayList<std::string> FileReader::read() {
    ArrayList<std::string> words;
    std::string word;
    while (file >> word) {
        words.append(word);
    }
    return words;
}

