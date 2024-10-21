#ifndef RESULT_HPP
#define RESULT_HPP

#include <string>

struct Result {
    std::string name;
    int score;
    Result(std::string name, int score) : name(name), score(score) {}
};

#endif
