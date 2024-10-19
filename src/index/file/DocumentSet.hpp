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

  static std::string parseDocNameFromPath(std::string path) {
    std::string documentName = "";
    for (int i = 0; i < path.size(); i++) {
      if (path[i] == '/') {
        documentName = "";
        continue;
      }
      if (path[i] == '.') {
        break;
      }
      if (!((int)path[i] <= 122 && (int)path[i] >= 65) || ((int)path[i] > 90 && (int)path[i] < 97)) {
          continue;
      }
      if ((int)path[i] <= 90) {
          path[i] += 32;
      }
      documentName += path[i];
    }
    return documentName;
  }

private:
  std::regex regex_pattern = std::regex(R"(.*\.txt)");
  std::string directory;
};
