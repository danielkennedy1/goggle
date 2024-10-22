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
    // for (int i = 0; i < 26; i++) {
    //   delete children[i];
    // }
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
        currentNode->children[index]
            = new TrieNode(
                    word[i], 
                    numOfWords);
        currentNode = currentNode->children[index];
      }
    }
    if (currentNode->wordIndex == -1) {
      currentNode->wordIndex = *numOfWords;
      *numOfWords = (int)*numOfWords + 1;
      return currentNode->wordIndex;
    }
    return -1;
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
        return nullptr;
    }
    if (currentNode->wordIndex != -1)
    {
      return currentNode;
    }
    return nullptr;
  }

  char nodeValue;
private:
  TrieNode *children[26];
};


class Trie {
  public:

  int* numOfWords = new int;

  Trie() {
    *numOfWords = 0;
    rootNode = new TrieNode(numOfWords);
  }

  ~Trie() {
    // delete numOfWords;
    // delete rootNode;
  }

  int insert(std::string word) {
    int index = rootNode->insert(word);
    if (index == -1) {
        return index;
    }
    while (index >= words.length) {
        words.append("\0");
    }
    words.update(index, word);
    return index;
  }

  ArrayList<std::string> autocomplete(std::string word) {
    return rootNode->autocomplete(word);
  }

  TrieNode* check(std::string word) {
    return rootNode->check(word);
  }

  void serialize(std::string filePath) {
    std::string stringRepresentation = getWordsSerializedAsString();
    std::ofstream file(filePath, std::ios::binary);
      if (!file.is_open()) {
          std::cerr
              << "Error: Failed to open file for writing."
              << std::endl;
          return;
      }
      int string_size = stringRepresentation.size();
      file.write(reinterpret_cast<const char*>(&string_size),
                  sizeof(string_size));
      const char* c_string = stringRepresentation.c_str();
      file.write(reinterpret_cast<const char*>(&c_string),
                  sizeof(c_string));
      file.close();
      std::cout << "Trie serialized successfully." << std::endl;

      return;
  }

  void loadFrom(std::string filePath) {
    const char* stringifiedSerializedData;
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr
            << "Error: Failed to open file for reading."
            << std::endl;
        return;
    }
    int string_size;
    file.read(reinterpret_cast<char*>(&string_size),
              sizeof(string_size));

    file.read(reinterpret_cast<char*>(&stringifiedSerializedData),
              string_size*4);
    file.close();

    deserializeWordsFromString(stringifiedSerializedData, string_size);

    std::cout << "Trie deserialized successfully." << std::endl;

    return;
  }

  ArrayList<std::string> words;
  TrieNode* rootNode;

  private:
  std::string getWordsSerializedAsString() {
    std::string value = "                    ";
    for (int i = 0; i < words.length; i++) {
        std::string word = words[i];
        value += std::to_string(word.length()) + "~" + word;
    }
    return value;
  } 

  std::string convertToString(const char* a, int size) {
      int i;
      std::string s = "";
      for (i = 0; i < size; i++) {
          s = s + a[i];
      }
      return s;
  }

  void deserializeWordsFromString(const char* data, int dataLength) {
    int pos = 20;
    std::string dataAsStr = convertToString(data, dataLength);
    while (pos < dataLength) {
        int lenPos = dataAsStr.find('~', pos);
        if (lenPos == std::string::npos) break;

        int length = std::stoi(dataAsStr.substr(pos, lenPos - pos));
        pos = lenPos + 1;

        std::string word = dataAsStr.substr(pos, length);        
        this->rootNode->insert(word);

        pos += length;
    }
  } 
};

#endif // TRIE_H
