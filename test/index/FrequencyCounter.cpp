#include <gtest/gtest.h>
#include <iostream>
#include "FrequencyCounter.hpp"
#include "FileReader.hpp"

TEST(FrequencyCounterTests, TestFrequencyCounterCanCountFrequency)
{

    std::string s(TEST_DATA_DIR);
    FileReader *reader = new FileReader(s + "/11_TestDoc.txt");

    ArrayList<std::string> *words = reader->read();

    FrequencyCounter counter = FrequencyCounter(1);

    counter.addDocument(0, words, StringUtils::parseDocNameFromPath(s + "/11_TestDoc.txt"));

    counter.indexDocument(0);

    ArrayList<int> documentFrequencies = counter.getFreqTable()[0];

    Trie *vocabTrie = counter.getVocabTrie();

    TrieNode *searchTermNode = vocabTrie->check("testing");

    TrieNode *incorrectSearchTermNode = vocabTrie->check("dog");

    int freqOfWord = documentFrequencies.get(searchTermNode->wordIndex);

    ASSERT_TRUE(incorrectSearchTermNode == nullptr);
    ASSERT_EQ(freqOfWord, 1);
}
