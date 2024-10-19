#include <gtest/gtest.h>
#include "Trie.hpp"

// int TrieNode::numOfWords = 0;

TEST(TrieTests, TestInsertionAndCheck)
{
    int numOfWords = 0;

    TrieNode *trie = new TrieNode(&numOfWords);

    trie->insert("testing");
    trie->insert("testy");
    trie->insert("task");
    trie->insert("talk");
    trie->insert("testable");

    ASSERT_TRUE(trie->check("testing"));
    ASSERT_TRUE(trie->check("task"));
    ASSERT_FALSE(trie->check("test"));
    ASSERT_FALSE(trie->check("abc"));
}

TEST(TrieTests, TestSerializationDeserialization) {
    int numOfWords = 0;

    TrieNode *trie = new TrieNode(&numOfWords);

    trie->insert("testing");
    trie->insert("testy");
    trie->insert("task");
    trie->insert("talk");
    trie->insert("testable");

    std::string documentsPath = SERIALIZED_DATA_DIR;

    trie->serialize(documentsPath + "/testing_trie_serialization");

    int numOfWordsBefore = *(trie->numOfWords);

    TrieNode deserTrie = TrieNode::deserialize(documentsPath + "/testing_trie_serialization");

    std::remove((documentsPath + "/testing_trie_serialization").c_str() );

    int numOfWordsAfter = *(deserTrie.numOfWords);

    deserTrie.insert("one");
    deserTrie.insert("two");
    deserTrie.insert("three");

    int numOfWordsAfterAfter = *(deserTrie.numOfWords);

    ASSERT_TRUE(deserTrie.check("testing"));
    ASSERT_FALSE(deserTrie.check("tes"));
    ASSERT_EQ(numOfWordsBefore, numOfWordsAfter);
    ASSERT_EQ(numOfWordsAfter+3, numOfWordsAfterAfter);
}