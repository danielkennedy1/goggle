#include <gtest/gtest.h>
#include <iostream>
#include "FrequencyCounter.hpp"
#include "FileReader.hpp"

TEST(FrequencyCounterTests, TestFrequencyCounterCanCountFrequency) {    
    std::string s(TEST_DATA_DIR);
    FileReader *reader = new FileReader(s + "/11 TestDoc.txt");
    
    ArrayList<std::string> words = reader->read();


    FrequencyCounter counter = FrequencyCounter(&words);


    counter.count();

    TrieNode* trie = counter.getTrie();
    TrieNode* searchTermNode = trie->check("testing");
    TrieNode* incorrectSearchTermNode = trie->check("dog");

    ASSERT_EQ(incorrectSearchTermNode, nullptr);

    ArrayList<int>* wordFrequencies = counter.getFreqTable();

    int freqOfWord = wordFrequencies->get(searchTermNode->wordIndex);

    ASSERT_EQ(freqOfWord, 1);
}
