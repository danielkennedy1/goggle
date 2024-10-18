#include <gtest/gtest.h>
#include "Trie.hpp"

int TrieNode::numOfWords = 0;

TEST(TrieTests, TestInsertionAndCheck)
{
    TrieNode *trie = new TrieNode();

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
