#ifndef TRIE_H
#define TRIE_H
#include <string>
#include <iostream>
#include <fstream>
#include "ArrayList.h"

class TrieNode
{
public:
  int wordIndex;
  int* numOfWords;

  TrieNode(char value, int* numOfWords)
  {
    for (int i = 0; i < 26; i++)
    {
      children[i] = nullptr;
    };
    nodeValue = value;
    wordIndex = -1;
    this->numOfWords = numOfWords;
  };


  TrieNode(int* numOfWords)
  {
    for (int i = 0; i < 26; i++)
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
      words.append(currentWord + currentNode->nodeValue);
    }
    for (int i = 0; i < 26; i++)
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
      if (searchOrigin->children[index])
      {
        searchOrigin = searchOrigin->children[index];
        continue;
      }
      return words;
    }
    if (searchOrigin->wordIndex != -1) {
      words.append(word);
    }
    for (int i = 0; i < 26; i++)
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

  void serialize(const std::string& filename)
    {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr
                << "Error: Failed to open file for writing."
                << std::endl;
            return;
        }
        file.write(reinterpret_cast<const char*>(this),
                   sizeof(*this));
        file.close();
        std::cout << "Object serialized successfully." << std::endl;
    }

  static TrieNode deserialize(const std::string& filename)
    {
        TrieNode node = TrieNode(0);
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr
                << "Error: Failed to open file for reading."
                << std::endl;
            return NULL;
        }
        file.read(reinterpret_cast<char*>(&node),
                  sizeof(node));
        file.close();
        std::cout << "Object deserialized successfully." << std::endl;
        return node;
    }


  char nodeValue;
private:
  TrieNode *children[26];
};

#endif // TRIE_H
