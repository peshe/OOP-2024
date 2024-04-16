#pragma once
#include <cstdlib>
#include <iostream>

class String
{
    // Rule of three
public:
    String();
    String(const String& other);
    String& operator=(const String& other);
    ~String();

    String(const char* str);
    explicit operator const char*() const;
    friend std::ostream& operator<<(std::ostream& out, const String& str);

    // Public interface
public:
    size_t length() const { return size; }
    void reserve(size_t capacity);
    // TODO: [], ==, !=, <, >, <=, >=, +, +=, *, *=, <<

    // TODO: For bonus points:
    //       getline, >>

    // Utility methods
private:
    void copy(const String& other);
    void clear();

    // Member fields
private:
    char* pData;
    size_t size;
    size_t capacity;

    // Static data
private:
    static const size_t DEFAULT_CAPACITY;
};
