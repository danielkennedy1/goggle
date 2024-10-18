#include "index/Index.hpp"

int main() {
    Index* index = new Index(TEST_DATA_DIR);

    std::cout << index->counters->get(0)->getFreqTable()->get(0) << std::endl;

    return 0;
}
