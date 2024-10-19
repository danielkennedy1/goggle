#include <string>
#include <utility>
#include <iostream>
#include "core/Trie.hpp"
#include "ArrayList.h"

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

    FrequencyCounter(int numOfDocs) {
        *nextFreeIndex = 0;
        vocabularyTrie = new TrieNode(nextFreeIndex);
        titleTrie = new TrieNode();
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
        documents[docNum].name = name;
        documents[docNum].contents = words;
    }


    void indexDocument(int docNum) {
        std::cout << documents[docNum].name << std::endl;
        titleTrie->insert(documents[docNum].name);
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
    book* documents;
    int* nextFreeIndex = new int;
};