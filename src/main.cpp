#include <cassert>
#include <iostream>
#include <ostream>
#include <string>

#include "ArrayList.h"
#include "Autocomplete.hpp"
#include "Index.hpp"
#include "Parser.hpp"
#include "Search.hpp"
#include "StringUtils.hpp"
#include "Trie.hpp"

#define K 5

std::string frequenciesTableLocation = std::string(SERIALIZED_DATA_DIR) + std::string("/frequencies_table.bin");
std::string vocabTrieLocation = std::string(SERIALIZED_DATA_DIR) + std::string("/vocab_trie.bin");
std::string bookPathsLocation = std::string(SERIALIZED_DATA_DIR) + std::string("/book_paths.txt");
std::string bookLengthsLocation = std::string(SERIALIZED_DATA_DIR) + std::string("/book_lengths.txt");
std::string tableWidthLocation = std::string(SERIALIZED_DATA_DIR) + std::string("/table_width.txt");

void search(Trie *vocabTrie)
{
    std::string query;

    std::cout << "Please enter a search term. It can be multiple words "
                 "separated by logical operators (AND and OR). Negation can "
                 "also be used (NOT water AND wave): "
              << std::endl;

    std::getline(std::cin, query);

    Parser parser(query);

    ArrayList<Argument> searchArgs = parser.parse();

    Search search(
        frequenciesTableLocation,
        vocabTrie,
        bookPathsLocation,
        bookLengthsLocation,
        tableWidthLocation);

    ArrayList<Result *> *results = search.search(searchArgs, K);

    assert(results->length == K);

    std::cout << "Rank\tName\t(tf-idf score)\tPath" << std::endl;

    for (int i = 0; i < results->length; i++)
    {
        std::cout
            << i + 1 << ":\t"
            << StringUtils::parseDocNameFromPath(results->get(i)->name) << "\t\t"
            << "(" << results->get(i)->score << ")\t"
            << results->get(i)->name
            << std::endl;
    }
}

int main()
{
    Index index(GUTENBERG_DATA_DIR);
    if (DEBUG)
        std::cout << "INDEX CREATED" << std::endl;
    index.index();
    if (DEBUG)
        std::cout << "INDEX INDEXED" << std::endl;
    index.persist(
        frequenciesTableLocation,
        vocabTrieLocation,
        bookPathsLocation,
        bookLengthsLocation,
        tableWidthLocation);
    if (DEBUG)
        std::cout << "INDEX PERSISTED" << std::endl;
    Autocomplete autocomplete(index.counter->getVocabTrie());
    if (DEBUG)
        std::cout << "AUTOCOMPLETE CREATED" << std::endl;
    autocomplete.start();
    if (DEBUG)
        std::cout << "AUTOCOMPLETE STARTED" << std::endl;
    // search(index.counter->getVocabTrie());
    // int numOfWords = 0;
    // Trie *trie = new Trie(&numOfWords);
    // trie->loadFrom("/Users/conor/ISE/Data Structures & Algorithms III/project/goggle/data/serialized_data/vocab_trie.bin");
    // std::cout << trie->check("the")->wordIndex << std::endl;
    // std::cout << trie->check("project")->wordIndex << std::endl;
    // std::cout << trie->check("use")->wordIndex << std::endl;
    // search(trie);
    search(index.counter->getVocabTrie());
};
