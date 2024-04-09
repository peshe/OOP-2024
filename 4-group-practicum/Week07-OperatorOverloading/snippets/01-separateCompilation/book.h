#pragma once

#include <cstddef>

const std::size_t MAX_BOOK_NAME_SIZE = 100;

class Book
{
private:
    char name[MAX_BOOK_NAME_SIZE];
    int yearOfPublication;

public:
    Book();
    Book(const char* name, const int yearOfPublication);

    const char* getName() const;

    void print() const;
};