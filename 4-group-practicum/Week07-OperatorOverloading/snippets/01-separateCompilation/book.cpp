#include "book.h"
#include <cstring>
#include <cassert>
#include <iostream>

Book::Book() : Book("", 0) {}

Book::Book(const char* name, const int yearOfPublication)
    : yearOfPublication(yearOfPublication)
{
    assert(name != nullptr);

    strcpy(this->name, name);
}

const char* Book::getName() const
{
    return this->name;
}

void Book::print() const
{
    assert(this->name != nullptr);

    std::cout << this->name << ", " << this->yearOfPublication << std::endl;
}