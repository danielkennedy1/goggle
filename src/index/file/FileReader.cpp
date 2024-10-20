#include "FileReader.hpp"
#include "StringUtils.hpp"

FileReader::FileReader(const std::string& filename) : file(filename) {};

FileReader::~FileReader() {
    file.close();
}

ArrayList<std::string>* FileReader::read() {
    ArrayList<std::string>* words = new ArrayList<std::string>();
    std::string word;
    while (file >> word) {
        words->append(StringUtils::removeInvalidChars(word));
    }
    return words;
}

