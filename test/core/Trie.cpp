#include <gtest/gtest.h>
#include <filesystem>
#include "Trie.hpp"

TEST(TrieTests, TestInsertionAndCheck)
{
    int numOfWords = 0;

    Trie *trie = new Trie(&numOfWords);

    trie->insert("testing");
    trie->insert("testy");
    trie->insert("task");
    trie->insert("talk");
    trie->insert("testable");
    trie->insert("the");

    ASSERT_TRUE(trie->check("testing"));
    ASSERT_TRUE(trie->check("testing")->wordIndex == 0);
    ASSERT_TRUE(trie->check("testy"));
    ASSERT_TRUE(trie->check("testy")->wordIndex == 1);
    ASSERT_TRUE(trie->check("task"));
    ASSERT_TRUE(trie->check("task")->wordIndex == 2);
    ASSERT_FALSE(trie->check("test"));
    ASSERT_FALSE(trie->check("abc"));
    ASSERT_FALSE(trie->check("there"));
}

TEST(TrieTests, TestTrieWordsArrayList)
{
    int numOfWords = 0;

    Trie *trie = new Trie(&numOfWords);

    trie->insert("testing");
    trie->insert("testy");
    trie->insert("task");
    trie->insert("talk");
    trie->insert("testable");
    trie->insert("the");

    ArrayList<std::string> words = trie->words;

    ASSERT_EQ(words[0], "testing");
    ASSERT_EQ(words[2], "task");
    ASSERT_EQ(words[4], "testable");
    ASSERT_EQ(words[5], "the");
}

TEST(TrieTests, TestSerializationDeserialization)
{
    int numOfWords = 0;
    Trie *trie = new Trie(&numOfWords);

    trie->insert("testing");
    trie->insert("testy");
    trie->insert("task");
    trie->insert("talk");
    trie->insert("testable");

    std::filesystem::path filepath = std::string(SERIALIZED_DATA_DIR);
    bool filepathExists = std::filesystem::is_directory(filepath);

    std::string documentsPath = SERIALIZED_DATA_DIR;

    if (!filepathExists)
    {
        std::filesystem::create_directory(filepath);
    }

    trie->serialize(documentsPath + "/testing_trie_serialization");
    int numOfWordsBefore = *(trie->numOfWords);
    delete trie;

    int numOfWords2 = 0;

    Trie *deserTrie = new Trie(&numOfWords2);
    deserTrie->loadFrom(documentsPath + "/testing_trie_serialization");

    int numOfWordsAfter = *(deserTrie->numOfWords);

    deserTrie->insert("one");
    deserTrie->insert("two");
    deserTrie->insert("three");

    int numOfWordsAfterAfter = *(deserTrie->numOfWords);

    std::cout << deserTrie->check("testing")->wordIndex << std::endl;
    std::cout << deserTrie->check("testy")->wordIndex << std::endl;
    std::cout << deserTrie->check("task")->wordIndex << std::endl;

    ASSERT_TRUE(deserTrie->check("testing"));
    ASSERT_EQ(deserTrie->check("testing")->wordIndex, 0);
    ASSERT_TRUE(deserTrie->check("testy"));
    ASSERT_EQ(deserTrie->check("testy")->wordIndex, 1);
    ASSERT_TRUE(deserTrie->check("testable"));
    ASSERT_EQ(deserTrie->check("testable")->wordIndex, 4);
    ASSERT_TRUE(deserTrie->check("one"));
    ASSERT_TRUE(deserTrie->check("two"));
    ASSERT_TRUE(deserTrie->check("three"));
    ASSERT_EQ(deserTrie->check("three")->wordIndex, 7);
    ASSERT_FALSE(deserTrie->check("tes"));
    ASSERT_EQ(numOfWordsBefore, numOfWordsAfter);
    ASSERT_EQ(numOfWordsAfter + 3, numOfWordsAfterAfter);
}
