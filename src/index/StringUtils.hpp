#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP
#include <string>

class StringUtils {
    public: 
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
      documentName += path[i];
    }
    return documentName;
  }

  static std::string removeInvalidChars(std::string input) {
    std::string output = "";
    for (int i = 0; i < input.size(); i++) {
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
  
};

#endif
