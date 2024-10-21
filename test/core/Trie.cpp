#include <gtest/gtest.h>
#include <filesystem>
#include "Trie.hpp"

TEST(TrieTests, TestInsertionAndCheck)
{
    int numOfWords = 0;

    TrieNode *trie = new TrieNode(&numOfWords);

    trie->insert("testing");
    trie->insert("testy");
    trie->insert("task");
    trie->insert("talk");
    trie->insert("testable");
    trie->insert("the");

    ASSERT_TRUE(trie->check("testing"));
    ASSERT_TRUE(trie->check("task"));
    ASSERT_FALSE(trie->check("test"));
    ASSERT_FALSE(trie->check("abc"));
    ASSERT_FALSE(trie->check("there"));
}

TEST(TrieTests, TestSerializationDeserialization) {
    int numOfWords = 0;

    TrieNode *trie = new TrieNode(&numOfWords);

    trie->insert("testing");
    trie->insert("testy");
    trie->insert("task");
    trie->insert("talk");
    trie->insert("testable");

    std::filesystem::path filepath = std::string(SERIALIZED_DATA_DIR);
    bool filepathExists = std::filesystem::is_directory(filepath.parent_path());

    std::string documentsPath = SERIALIZED_DATA_DIR;
    
    if(!filepathExists) {
        std::filesystem::create_directory(documentsPath + "/testing_arraylist_serialization");
    }

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