#pragma once
#include <ostream>

class Vector
{
    // Lifetime
public:
    Vector();
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    ~Vector();

    // Interface
public:
    int& at(size_t position);
    void push_back(int element);
    void pop_back();
    void print(std::ostream& out) const;
    size_t getSize() const;

    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    // Utility methods
private:
    void clean();
    void copy(const Vector& other);
    void expand();

    // Fields
private:
    int* pArr;
    size_t size;
    size_t capacity;

    // Consts
private:
    static const size_t DEFAULT_CAPACITY;
};
