#include "FileReader.hpp"

FileReader::FileReader(const std::string& filename) : file(filename) {};

FileReader::~FileReader() {
    file.close();
}

ArrayList<std::string>* FileReader::read() {
    ArrayList<std::string>* words = new ArrayList<std::string>();
    std::string word;
    while (file >> word) {
        for (int i = 0; i < word.size(); i++) {
            if (!((int)word[i] <= 122 && (int)word[i] >= 65) || ((int)word[i] > 90 && (int)word[i] < 97)) {
                word.erase(i, i+1);
            }
            if ((int)word[i] <= 90) {
                word[i] += 32;
            }
        } 
        words->append(word);
    }
    return words;
}

