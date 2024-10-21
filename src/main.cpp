#include <iostream>
#include <ostream>
#include <string>

#include "Search.hpp"
#include "ArrayList.h"
#include "Parser.hpp"
#include "Index.hpp"

#define K 5

std::string frequenciesTableLocation = std::string(SERIALIZED_DATA_DIR) + std::string("/frequencies_table.bin");
std::string vocabTrieLocation = std::string(SERIALIZED_DATA_DIR) + std::string("/vocab_trie.bin");
std::string bookPathsLocation = std::string(SERIALIZED_DATA_DIR) + std::string("/book_paths.txt");
std::string tableWidthLocation = std::string(SERIALIZED_DATA_DIR) + std::string("/table_width.txt");

void index() {
    Index index(GUTENBERG_DATA_DIR);
    index.index();
    index.persist(
           frequenciesTableLocation,
           vocabTrieLocation,
           bookPathsLocation,
           tableWidthLocation
            );
};

void search() {
    std::string query;

    std::cout << "Please enter a search term. It can be multiple words separated by spaces. i.e. (database computer internet): ";
    std::getline(std::cin, query);

    Parser parser(query);

    ArrayList<Argument> searchArgs = parser.parse();

    Search search(
           frequenciesTableLocation,
           vocabTrieLocation,
           bookPathsLocation,
           tableWidthLocation
            );

    search.search(searchArgs, K);
}


int main() {
    index();
    std::cout << "INDEX FINISHED" << std::endl;
    search();
};
