#include <string>
#include <utility>
#include <iostream>
#include "core/Trie.hpp"
#include "ArrayList.h"


class FrequencyCounter
{
public:

    FrequencyCounter(int numOfDocs) {
        *nextFreeIndex = 0;
        trie = new TrieNode(nextFreeIndex);
        texts = new ArrayList<std::string>[numOfDocs];
        frequencyTable = new ArrayList<int>[numOfDocs];
    }

    ~FrequencyCounter() {
        delete trie;
        delete[] frequencyTable;
        delete[] texts;
        delete nextFreeIndex;
    }

    void addDocument(int docNum, ArrayList<std::string> words) {
        texts[docNum] = words;
    }


    void indexDocument(int docNum) {
        for(int i = 0; i < texts[docNum].length; i++) {
            std::cout << texts[docNum].get(i) << std::endl;
            int index = trie->insert(texts[docNum].get(i));
            while (index >= frequencyTable[docNum].length) {
                frequencyTable[docNum].append(0);
            }
            int frequency = frequencyTable[docNum].get(index);
            frequencyTable[docNum].update(index, frequency + 1);
        }
    }

    TrieNode* getTrie() {return trie;}

    ArrayList<int>* getFreqTable() {return frequencyTable;}

private:
    TrieNode* trie;
    ArrayList<int>* frequencyTable;
    ArrayList<std::string>* texts;
    int* nextFreeIndex = new int;
};