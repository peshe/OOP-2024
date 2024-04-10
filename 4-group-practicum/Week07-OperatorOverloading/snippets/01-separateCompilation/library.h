#pragma once

#include "book.h"

class Library
{
private:
    Book* books;
    std::size_t size;
    std::size_t capacity;

    void deallocate();
    void copy(const Library& other);
    void resize();

public:
    Library();
    Library(const Library& other);
    Library& operator = (const Library& other);
    ~Library();

    void addBook(const Book& toAdd);
    bool removeBook(const char* name);
    void printInfo() const;
};