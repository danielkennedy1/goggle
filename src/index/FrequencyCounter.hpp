#ifndef FREQUENCYCOUNTER_H
#define FREQUENCYCOUNTER_H
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
    book(std::string name, ArrayList<std::string>* contents) : name(name), path(path), contents(contents) {};
    std::string name;
    std::string path;
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
        documents = new book[numOfDocs];
        frequencyTable = new ArrayList<int>[numOfDocs];
    }

    ~FrequencyCounter() {
        delete vocabularyTrie;
        delete[] frequencyTable;
        delete[] documents;
        delete nextFreeIndex;
    }

    void addDocument(int docNum, ArrayList<std::string>* words, std::string path) {
        documents[docNum].path = path;
        documents[docNum].name = StringUtils::parseDocNameFromPath(path);
        documents[docNum].contents = words;
    }


    void indexDocument(int docNum) {
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

    ArrayList<int>* getFreqTable() {return frequencyTable;}

private:
    TrieNode* vocabularyTrie;
    ArrayList<int>* frequencyTable;
    int* nextFreeIndex = new int;
    int* nextFreeIndexTitles = new int;
};
#endif