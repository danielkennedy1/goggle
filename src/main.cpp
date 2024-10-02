#include <iostream>
#include <string>
#include "FileReader.hpp"

int main() {

    FileReader reader("C:\\Users\\danie\\Development\\ISE\\cs4437\\goggle\\data\\simple_documents\\1 Computers.txt");
    std::cout << "FileReader created" << std::endl;

    std::vector<std::string> words = reader.read();

    for (std::string word : words) {
        std::cout << word << std::endl;
    }

    
    return 0;
}
