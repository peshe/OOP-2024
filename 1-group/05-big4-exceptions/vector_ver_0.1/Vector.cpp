#include "Vector.h"
#include <stdexcept>

Vector::Vector()
        : size(0) // Is the order here OK
        , capacity(4) // Will this work based on the parameters` order
        , arr(nullptr)
{
    arr = new int[capacity];
}

Vector::~Vector()
{
    clean();
}

Vector::Vector(const Vector& other)
{
    copy(other);
}

Vector& Vector::operator=(const Vector& other)
{
    if (this != &other) {
        clean();
        copy(other);
    }
    return *this;
}

int& Vector::at(size_t position)
{
    if (position >= size) {
        throw std::out_of_range("Out of range");
    }
    return arr[position];
    // TODO: insert return statement here
}

void Vector::clean()
{
    delete []arr;
    arr = nullptr;
}

void Vector::copy(const Vector& other)
{
    size = other.size;
    capacity = other.capacity;
    arr = new int[capacity];
    for (size_t i = 0; i < size; i++) {
        arr[i] = other.arr[i];
    }
    // arr = other.arr; we do not want this line
}
