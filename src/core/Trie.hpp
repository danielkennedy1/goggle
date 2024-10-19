#ifndef TRIE_H
#define TRIE_H
#include <string>
#include <iostream>
#include "ArrayList.h"

class TrieNode
{
public:
  int wordIndex;
  int* numOfWords;

  TrieNode(char value, int* numOfWords)
  {
    nodeValue = value;
    wordIndex = -1;
    this->numOfWords = numOfWords;
  };


  TrieNode(int* numOfWords)
  {
    for (int i = 0; i < 27; i++)
    {
      children[i] = nullptr;
    };
    nodeValue = '\0';
    wordIndex = -1;
    this->numOfWords = numOfWords;
  }

  ~TrieNode() {
  }

  int insert(std::string word)
  {
    TrieNode *currentNode = this;
    for (int i = 0; i < word.size(); i++)
    {
      int index = word[i] - 'a';
      if(index < 0 || index > 25) {
        index = 26;
      }
      if (currentNode->children[index])
      {
        currentNode = currentNode->children[index];
      }
      else
      {
        currentNode->children[index] = new TrieNode(word[i], numOfWords);
        currentNode = currentNode->children[index];
      }
    }
    if (currentNode->wordIndex == -1) {
      currentNode->wordIndex = *numOfWords;
      *numOfWords = (int)*numOfWords + 1;
    }
    return currentNode->wordIndex;
  };

  ArrayList<std::string> recursiveAutocomplete(TrieNode *currentNode, std::string currentWord)
  {
    ArrayList<std::string> words;
    if (currentNode->wordIndex != -1)
    {
      std::cout << "VALUE: " << currentNode->nodeValue << std::endl;
      ArrayList<std::string> returnVal;
      returnVal.append(currentWord + currentNode->nodeValue);
      return returnVal;
    }
    for (int i = 0; i < 27; i++)
    {
      if (currentNode->children[i])
      {
        ArrayList<std::string> returnVal = recursiveAutocomplete(currentNode->children[i], currentWord + currentNode->nodeValue);
        for (int i = 0; i < returnVal.length; i++) {
          words.append(returnVal[i]);
        }
      }
    }
    return words;
  }

  ArrayList<std::string> autocomplete(std::string word)
  {
    ArrayList<std::string> words;
    TrieNode *searchOrigin = this;
    for (int i = 0; i < word.size(); i++)
    {
      int index = word[i] - 'a';
      if(index < 0 || index > 25) {
        index = 26;
      }
      if (searchOrigin->children[index])
      {
        searchOrigin = searchOrigin->children[index];
        continue;
      }
    }
    for (int i = 0; i < 27; i++)
    {
      if (searchOrigin->children[i])
      {
        ArrayList<std::string> returnVal = recursiveAutocomplete(searchOrigin->children[i], word);
        for (int i = 0; i < returnVal.length; i++) {
          words.append(returnVal[i]);
        }
      }
    }
    return words;
  }

  TrieNode *check(std::string word)
  {
    TrieNode *currentNode = this;
    for (int i = 0; i < word.size(); i++)
    {
      int index = word[i] - 'a';
      if(index < 0 || index > 25) {
        index = 26;
      }
      if (currentNode->children[index])
        {
          currentNode = currentNode->children[index];
          continue;
        }
    }
    if (currentNode->wordIndex != -1)
    {
      return currentNode;
    }
    return nullptr;
  }

  char nodeValue;
private:
  TrieNode *children[27];
};

#endif // TRIE_H
