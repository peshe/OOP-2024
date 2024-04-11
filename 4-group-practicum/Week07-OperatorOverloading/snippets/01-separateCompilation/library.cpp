#include "library.h"
#include <iostream>
#include <cassert>
#include <cstring>

const std::size_t INITIAL_CAPACITY = 2;
const std::size_t INCREASE_STEP = 2;

void Library::deallocate()
{
    delete[] this->books;
}

void Library::copy(const Library& other)
{
    this->books = new (std::nothrow) Book[other.capacity];
    if (!this->books)
    {
        std::cout << "Memory problem" << std::endl;
        return;
    }

    for (std::size_t i = 0; i < other.size; ++i)
    {
        this->books[i] = other.books[i];
    }

    this->size = other.size;
    this->capacity = other.capacity;
}

void Library::resize()
{
    Book* newBooks = new (std::nothrow) Book[this->capacity * INCREASE_STEP];
    if (!newBooks)
    {
        std::cout << "Memory problem!" << std::endl;
        return;
    }

    for (std::size_t i = 0; i < this->size; ++i)
    {
        newBooks[i] = this->books[i];
    }

    this->deallocate();
    this->books = newBooks;
    this->capacity *= INCREASE_STEP;
}

Library::Library()
{
    this->books = new (std::nothrow) Book[INITIAL_CAPACITY];
    if (!this->books)
    {
        std::cout << "Memory problem" << std::endl;
        return;
    }

    this->capacity = INITIAL_CAPACITY;
    this->size = 0;
}

Library::Library(const Library& other)
{
    this->copy(other);
}

Library& Library::operator = (const Library& other)
{
    if (this != &other)
    {
        this->deallocate();
        this->copy(other);
    }

    return *this;
}

Library::~Library()
{
    this->deallocate();
}

void Library::addBook(const Book& toAdd)
{
    if (this->size == this->capacity)
    {
        this->resize();
    }

    this->books[this->size++] = toAdd;
}

bool Library::removeBook(const char* name)
{
    assert(name != nullptr);

    for (std::size_t i = 0; i < this->size; ++i)
    {
        if (strcmp(name, this->books[i].getName()) == 0)
        {
            this->books[i] = this->books[this->size - 1];
            --this->size;
            return true;
        }
    }

    return false;
}

void Library::printInfo() const
{
    std::cout << "SIZE: " << this->size << std::endl;
    std::cout << "CAPACITY: " << this->capacity << std::endl;
    for (std::size_t i = 0; i < this->size; ++i)
    {
        this->books[i].print();
    }
}