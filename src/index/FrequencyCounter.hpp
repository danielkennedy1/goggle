#include <string>
#include <utility>
#include <iostream>
#include "core/Trie.hpp"
#include "ArrayList.h"
#include "DocumentSet.hpp"
#include "StringUtils.hpp"

struct book {
    public:
    book() : name(""), contents(nullptr) {};
    book(std::string name, ArrayList<std::string>* contents) : name(name), contents(contents) {};
    std::string name;
    ArrayList<std::string>* contents;
};

class FrequencyCounter
{
public:
    int numOfDocuments;
    book* documents;

    FrequencyCounter(int numOfDocs) {
        numOfDocuments = numOfDocs;
        *nextFreeIndex = 0;
        *nextFreeIndexTitles = 0;
        vocabularyTrie = new TrieNode(nextFreeIndex);
        titleTrie = new TrieNode(nextFreeIndexTitles);
        documents = new book[numOfDocs];
        frequencyTable = new ArrayList<int>[numOfDocs];
    }

    ~FrequencyCounter() {
        delete vocabularyTrie;
        delete titleTrie;
        delete[] frequencyTable;
        delete[] documents;
        delete nextFreeIndex;
    }

    void addDocument(int docNum, ArrayList<std::string>* words, std::string name) {
        documents[docNum].name = StringUtils::parseDocNameFromPath(name);
        documents[docNum].contents = words;
    }


    void indexDocument(int docNum) {
        titleTrie->insert(StringUtils::removeInvalidChars(StringUtils::parseDocNameFromPath(documents[docNum].name)));
        for(int i = 0; i < documents[docNum].contents->length; i++) {
            int index = vocabularyTrie->insert(documents[docNum].contents->get(i));
            while (index >= frequencyTable[docNum].length) {
                frequencyTable[docNum].append(0);
            }
            int frequency = frequencyTable[docNum].get(index);
            frequencyTable[docNum].update(index, frequency + 1);
        }
    }

    TrieNode* getVocabTrie() {return vocabularyTrie;}

    TrieNode* getTitleTrie() {return titleTrie;}

    ArrayList<int>* getFreqTable() {return frequencyTable;}

private:
    TrieNode* vocabularyTrie;
    TrieNode* titleTrie;
    ArrayList<int>* frequencyTable;
    int* nextFreeIndex = new int;
    int* nextFreeIndexTitles = new int;
};