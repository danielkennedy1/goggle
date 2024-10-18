#ifndef TRIE_H
#define TRIE_H
#include <string>
#include <iostream>

class TrieNode
{
public:
  static int numOfWords;
  int wordIndex;

  TrieNode(char value)
  {
    nodeValue = value;
    wordIndex = -1;
  };

  TrieNode()
  {
    for (int i = 0; i < 26; i++)
    {
      children[i] = nullptr;
    };
    nodeValue = '\0';
    wordIndex = -1;
  }

  int insert(std::string word)
  {
    TrieNode *currentNode = this;
    bool newWord = false;
    for (int i = 0; i < word.size(); i++)
    {
      int index = word[i] - 'a';
      if (currentNode->children[index])
      {
        currentNode = currentNode->children[index];
      }
      else
      {
        newWord = true;
        currentNode->children[index] = new TrieNode(word[i]);
        currentNode = currentNode->children[index];
      }
    }
    if (newWord) {
      currentNode->wordIndex = numOfWords;
      currentNode->numOfWords++;
    }
    return currentNode->wordIndex;
  };

  void recursiveAutocomplete(TrieNode *currentNode, std::string currentWord)
  {
    if (currentNode->wordIndex != -1)
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
    if (currentNode->wordIndex != -1)
    {
      return currentNode;
    }
    return nullptr;
  }

private:
  TrieNode *children[26];
  char nodeValue;
};

#endif // TRIE_H
