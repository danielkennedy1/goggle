#ifndef PARSER_H
#define PARSER_H
#include "ArrayList.h"
#include "Trie.hpp"
#include <stack>

struct Argument {
    Argument(int index, bool required, bool negated) : index(index), required(required), negated(negated) {};
    int index;
    bool required;
    bool negated;
};

class Parser {
    public:
    int numOfArgs = 0;

    const std::string symbols[3] = {"or", "and", "not"};

    Parser(std::string query, TrieNode* vocabTrie) : rawQuery(query), vocabTrie(vocabTrie) {};

    Argument* parse() {
        std::string lowerCaseQuery = Parser::removeInvalidChars(rawQuery);
        ArrayList<std::string> queryComponents = Parser::splitString(lowerCaseQuery);

        std::stack<Argument> args;

        bool negate = false;
        bool expectWord = true;
        bool require = false;

        for (int i = 0; i < queryComponents.length; i++) {
            std::string symbol = queryComponents[i];
            if (symbol == "or") {
                if (expectWord == true) {
                    std::cout << "INVALID QUERY - EXPECTED WORD" << std::endl;
                    return nullptr;
                }
                expectWord = true;
                continue;
            }
            if (symbol == "and") {
                if (expectWord == true) {
                    std::cout << "INVALID QUERY - EXPECTED WORD" << std::endl;
                    return nullptr;
                }
                if (args.size() == 0) {
                    std::cout << "INVALID QUERY" << std::endl;
                    return nullptr;
                }
                Argument previouArg = args.top();
                args.pop();
                previouArg.required = true;
                args.push(previouArg);
                expectWord = true;
                require = true;
                continue;
            }
            if (symbol == "not") {
                negate = true;
                expectWord = true;
                continue;
            }

            if (expectWord == false) {
                std::cout << "INVALID QUERY" << std::endl;
                return nullptr;
            }

            TrieNode* node = vocabTrie->check(symbol);
            if (node == nullptr) {
                std::cout << "WORD " << symbol << " NOT IN CORPUS VOCABULARY" << std::endl;
                return nullptr;
            }

            args.push(Argument(node->wordIndex, require, negate));
            require = false;
            negate = false;
            expectWord = false;
        }

        Argument* argsArray;

        while(!args.empty()) {
            argsArray[args.size()-1] = args.top();
            args.pop();
            numOfArgs++;
        }

        return argsArray;
    }

    static ArrayList<std::string> splitString(std::string input) {
    ArrayList<std::string> output;
    std::string word;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == ' ' || i == input.size()-1) {
            if (i == input.size()-1) {
                word += input[i];
            }
            output.append(word);
            word = "";
            continue;
        }
        word += input[i];
    }
    return output;
  }

  static std::string removeInvalidChars(std::string input) {
    std::string output = "";
    for (int i = 0; i < input.size(); i++) {
        if(input[i] == 32) {
            output += input[i];
            continue;
        }
      if (!((int)input[i] <= 122 && (int)input[i] >= 65) || ((int)input[i] > 90 && (int)input[i] < 97)) {
          continue;
      }
      if ((int)input[i] <= 90) {
          input[i] += 32;
      }
      output += input[i];
    }
    return output;
  }

  private:
  std::string rawQuery;
  TrieNode* vocabTrie;
};

#endif