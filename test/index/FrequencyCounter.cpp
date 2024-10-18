#include <gtest/gtest.h>
#include <iostream>
#include "FrequencyCounter.hpp"
#include "FileReader.hpp"

TEST(FrequencyCounterTests, TestFrequencyCounterCanCountFrequency) {    
    std::string s(TEST_DATA_DIR);
    FileReader *reader = new FileReader(s + "/11 TestDoc.txt");
    
    ArrayList<std::string> words = reader->read();

    int nextFreeIndex = 0;

    FrequencyCounter counter = FrequencyCounter(1); 

    // counter.addDocument(0, words);

    // counter.indexDocument(0);

    // ArrayList<int> documentFrequencies = counter.getFreqTable()[0];

    // TrieNode* trie = counter.getTrie();
    // TrieNode* searchTermNode = trie->check("testing");
    // TrieNode* incorrectSearchTermNode = trie->check("dog");
    // std::cout << "GOT TO HERE" << std::endl;
    // std::cout << documentFrequencies.get(searchTermNode->wordIndex) << std::endl;

    // int freqOfWord = documentFrequencies.get(searchTermNode->wordIndex);

    // ASSERT_TRUE(incorrectSearchTermNode == nullptr);
    // ASSERT_EQ(freqOfWord, 1);
}
