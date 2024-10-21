#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include <string>

struct Argument {
    Argument() : word(""), required(false), negated(false) {};
    Argument(std::string word, bool required, bool negated) : word(word), required(required), negated(negated) {};
    std::string word;
    bool required;
    bool negated;
};

#endif
