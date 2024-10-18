#include <filesystem>
#include <regex>
#include <string>
#include "ArrayList.h"

class DocumentSet {
public:
  DocumentSet(std::string directory) : directory(directory) {}
  ArrayList<std::string>* getDocumentPaths() {
    ArrayList<std::string>* result = new ArrayList<std::string>();


    for (const auto &entry :
         std::filesystem::recursive_directory_iterator(directory)) {

      if (entry.is_regular_file()) {
        std::string filename = entry.path().filename().string();

        if (std::regex_match(filename, regex_pattern)) {
            result->append(entry.path().string());
        }
      }
    }
    return result;
  }

private:
  std::regex regex_pattern = std::regex(R"(.*\.txt)");
  std::string directory;
};
