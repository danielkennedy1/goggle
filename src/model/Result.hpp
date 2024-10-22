#ifndef RESULT_HPP
#define RESULT_HPP

#include <string>

struct Result {
    std::string name;
    double score;
    Result(std::string name, double score) : name(name), score(score) {}
};

#endif
