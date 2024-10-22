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

void search()
{
    std::string query;

    std::cout << "Please enter a search term. It can be multiple words "
                 "separated by logical operators (AND and OR). Negation can "
                 "also be used (NOT water AND wave): "
              << std::endl;

    std::getline(std::cin, query);

    Parser parser(query);

    ArrayList<Argument> searchArgs = parser.parse();

    int why_did_we_do_it_this_way = 0;

    Trie* vocabTrie = new Trie(&why_did_we_do_it_this_way);

    vocabTrie->loadFrom(vocabTrieLocation);

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

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <index|autocomplete|search>" << std::endl;
        return 1;
    }

    std::string arg = argv[1];

    if (arg == "index")
    {
        Index index(GUTENBERG_DATA_DIR);
        index.index();

        index.persist(
            frequenciesTableLocation,
            vocabTrieLocation,
            bookPathsLocation,
            bookLengthsLocation,
            tableWidthLocation);
    }
    else if (arg == "autocomplete")
    {
        int numOfWords = 0;
        Trie *vocabTrie = new Trie(&numOfWords);
        vocabTrie->loadFrom(vocabTrieLocation);
        Autocomplete autocomplete(vocabTrie);
        autocomplete.start();
    }
    else if (arg == "search")
    {
        search();
    }
    else
    {
        std::cerr << "Invalid option: " << arg << std::endl;
        std::cerr << "Valid options are: index, autocomplete, search" << std::endl;
        return 1;
    }

    return 0;
}
