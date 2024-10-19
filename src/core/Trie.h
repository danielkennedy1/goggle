#ifndef TRIE_H
#define TRIE_H
#include <string>
#include <iostream>

class TrieNode
{
public:
  TrieNode(char value)
  {
    nodeValue = value;
  };

  TrieNode()
  {
    for (int i = 0; i < 26; i++)
    {
      children[i] = nullptr;
    };
    nodeValue = '\0';
  }

  void insert(std::string word)
  {
    TrieNode *currentNode = this;
    for (int i = 0; i < word.size(); i++)
    {
      int index = word[i] - 'a';
      if (currentNode->children[index])
      {
        currentNode = currentNode->children[index];
      }
      else
      {
        currentNode->children[index] = new TrieNode(word[i]);
        currentNode = currentNode->children[index];
      }
    }
    currentNode->completeWord = true;
  };

  void recursiveAutocomplete(TrieNode *currentNode, std::string currentWord)
  {
    if (currentNode->completeWord)
    {
      std::cout << currentWord + currentNode->nodeValue << std::endl;
    }
    for (int i = 0; i < 26; i++)
    {
      if (currentNode->children[i])
      {
        recursiveAutocomplete(currentNode->children[i], currentWord + currentNode->nodeValue);
      }
    }
  }

  void autocomplete(std::string word)
  {
    TrieNode *searchOrigin = this;
    for (int i = 0; i < word.size(); i++)
    {
      for (int j = 0; j < 26; j++)
      {
        if (searchOrigin->children[j] && searchOrigin->children[j]->nodeValue == word[i])
        {
          searchOrigin = searchOrigin->children[j];
          break;
        }
      }
    }
    for (int i = 0; i < 26; i++)
    {
      if (searchOrigin->children[i])
      {
        recursiveAutocomplete(searchOrigin->children[i], word);
      }
    }
  }

  TrieNode *check(std::string word)
  {
    TrieNode *currentNode = this;
    for (int i = 0; i < word.size(); i++)
    {
      for (int j = 0; j < 26; j++)
      {
        if (currentNode->children[j] && currentNode->children[j]->nodeValue == word[i])
        {
          currentNode = currentNode->children[j];
          break;
        }
      }
    }
    if (currentNode->completeWord)
    {
      return currentNode;
    }
    return nullptr;
  }

private:
  TrieNode *children[26];
  char nodeValue;
  bool completeWord;
};

#endif // TRIE_H
