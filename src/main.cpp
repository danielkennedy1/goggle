#include <iostream>
#include <ostream>
#include <string>

#include "ArrayList.h"
#include "Autocomplete.hpp"
#include "Index.hpp"
#include "Parser.hpp"
#include "Search.hpp"
#include "Trie.hpp"

#define K 5

std::string frequenciesTableLocation =
    std::string(SERIALIZED_DATA_DIR) + std::string("/frequencies_table.bin");
std::string vocabTrieLocation =
    std::string(SERIALIZED_DATA_DIR) + std::string("/vocab_trie.bin");
std::string bookPathsLocation =
    std::string(SERIALIZED_DATA_DIR) + std::string("/book_paths.txt");
std::string tableWidthLocation =
    std::string(SERIALIZED_DATA_DIR) + std::string("/table_width.txt");

void search(TrieNode* vocabTrie) {
    std::string query;

    std::cout << "Please enter a search term. It can be multiple words "
                 "separated by logical operators (AND and OR). Negation can "
                 "also be used (NOT water AND wave): "
              << std::endl;

    std::cin.ignore();
    std::getline(std::cin, query);

    Parser parser(query);

    ArrayList<Argument> searchArgs = parser.parse();

    Search search(frequenciesTableLocation, vocabTrie,
                  bookPathsLocation, tableWidthLocation);

    search.search(searchArgs, K);
    
}

int main() {
    Index index(GUTENBERG_DATA_DIR);
    index.index();
    index.persist(frequenciesTableLocation, vocabTrieLocation,
                  bookPathsLocation, tableWidthLocation);
    Autocomplete autocomplete(index.counter->getVocabTrie());
    autocomplete.start();
    std::cout << "INDEX FINISHED" << std::endl;
    search(index.counter->getVocabTrie());
};
