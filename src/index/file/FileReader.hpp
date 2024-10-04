#include <fstream>
#include <string>
#include <vector>

class FileReader
{
public:
    FileReader(const std::string &filename);
    ~FileReader();
    std::vector<std::string> read();

private:
    std::ifstream file;
};
