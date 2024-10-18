#include <fstream>
#include <string>
#include "ArrayList.h"

class FileReader
{
public:
    FileReader(const std::string &filename);
    ~FileReader();
    ArrayList<std::string>* read();

private:
    std::ifstream file;
};
