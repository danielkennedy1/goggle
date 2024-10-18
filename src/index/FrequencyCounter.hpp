#include <string>
#include <utility>
#include <iostream>
#include "core/Trie.hpp"
#include "ArrayList.h"

int TrieNode::numOfWords = 0;

class FrequencyCounter
{
public:

    FrequencyCounter(ArrayList<std::string>* arraylist_of_words) {
        words = arraylist_of_words;
        trie = new TrieNode();
        frequencyTable = new ArrayList<int>();
    }

    ~FrequencyCounter() {
        delete trie;
        delete frequencyTable;
    }

    void count() {
        for(int i = 0; i < words->length; i++) {
            int index = trie->insert(words->get(i));
            while (index >= frequencyTable->length) {
                frequencyTable->append(0);
            }
            int frequency = frequencyTable->get(index);
            std::cerr << words->get(i) << std::endl;
            std::cerr << index << std::endl;
            frequencyTable->update(index, frequency + 1);
        }
    }

    TrieNode* getTrie() {return trie;}

    ArrayList<int>* getFreqTable() {return frequencyTable;}

private:
    ArrayList<int>* frequencyTable;
    TrieNode* trie;
    ArrayList<std::string>* words;
};
