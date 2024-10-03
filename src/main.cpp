#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <utility>
#include "index/file/FileReader.hpp"

int main() {
    std::vector<std::string> paths = {
      "C:\\Users\\danie\\Development\\ISE\\cs4437\\goggle\\data\\simple_documents\\1 Computers.txt",
      "C:\\Users\\danie\\Development\\ISE\\cs4437\\goggle\\data\\simple_documents\\10 Databases.txt",
      "C:\\Users\\danie\\Development\\ISE\\cs4437\\goggle\\data\\simple_documents\\2 Programming.txt",
      "C:\\Users\\danie\\Development\\ISE\\cs4437\\goggle\\data\\simple_documents\\3 Networks.txt",
      "C:\\Users\\danie\\Development\\ISE\\cs4437\\goggle\\data\\simple_documents\\4 Data.txt",
      "C:\\Users\\danie\\Development\\ISE\\cs4437\\goggle\\data\\simple_documents\\5 Algorithims.txt",
      "C:\\Users\\danie\\Development\\ISE\\cs4437\\goggle\\data\\simple_documents\\6 Internet.txt",
      "C:\\Users\\danie\\Development\\ISE\\cs4437\\goggle\\data\\simple_documents\\7 Software.txt",
      "C:\\Users\\danie\\Development\\ISE\\cs4437\\goggle\\data\\simple_documents\\8 Files.txt",
      "C:\\Users\\danie\\Development\\ISE\\cs4437\\goggle\\data\\simple_documents\\9 Hardware.txt",
    };

    // Read all the documents
    std::vector<std::vector<std::string>> documents;

    for (std::string path : paths) {
        std::cout << "Reading " << path << std::endl;
        FileReader reader(path);
        std::vector<std::string> content = reader.read();
        documents.push_back(content);
    }

    for (std::vector<std::string> content : documents) {
      std::cout << "Words: " << content.size() << std::endl;
    }

    // Create an index of the documents
    std::unordered_set<std::string> unique_words;

    for (std::vector<std::string> content : documents) {
        for (std::string word : content) {
            unique_words.insert(word);
        }
    }

    std::unordered_map<std::string, std::vector<int>> index;

    for (std::string word : unique_words) {
      index.insert(std::make_pair(word, std::vector<int>()));
    }

    for (int i = 0; i < documents.size(); i++) {
      for (std::string word : unique_words) {
        int count = 0;
        for (std::string doc_word : documents[i]) {
          if (word == doc_word) {
            count++;
          }
        }
        index[word].push_back(count);
      }
    }

    // Index created now

//    for (std::pair<std::string, std::vector<int>> pair : index) {
//      std::cout << pair.first << ": ";
//      for (int i : pair.second) {
//        std::cout << i << " ";
//      }
//      std::cout << std::endl;
//    }

    // Now we can search the index
    // For example, let's search for the word "computer"
    std::string search_word = "be";
    std::vector<int> search_results = index[search_word];
    std::map<int, std::vector<int>> ranked_results;

    for (int i = 0; i < search_results.size(); i++) {
      if (search_results[i] > 0) {
        ranked_results[search_results[i]].push_back(i);
      }
    }

    int rank = 1;

    for (int i = ranked_results.rbegin()->first; i >= 0; i--) {
      if (ranked_results.find(i) != ranked_results.end()) {
        std::cout << "Rank " << rank << std::endl;
        for (int j : ranked_results[i]) {
          std::cout << j << " ";
        }
        std::cout << std::endl;
        rank++;
      }
    }

    std::vector<std::string> result_words = documents[ranked_results[ranked_results.rbegin()->first][0]];

    for (std::string word : result_words) {
      std::cout << word << " ";
    }
    std::cout << std::endl;


    // rank the documents by the number of instances of the search word (0 means don't rank)
    
    return 0;
}
