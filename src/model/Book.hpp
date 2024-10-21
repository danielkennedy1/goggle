#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include "ArrayList.h"

struct Book {
    public:
    Book() : name(""), contents(nullptr) {};
    Book(std::string name, ArrayList<std::string>* contents) : name(name), path(path), contents(contents) {};
    std::string name;
    std::string path;
    ArrayList<std::string>* contents;
};

#endif
