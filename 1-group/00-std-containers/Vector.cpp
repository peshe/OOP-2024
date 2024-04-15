#include "Vector.h"
#include <stdexcept>
#include <fstream>

const size_t Vector::DEFAULT_CAPACITY = 4; 

Vector::Vector()
    : pArr(nullptr)
    , size(0)
    , capacity(0)
{
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
        throw std::out_of_range("Vector.at: Out of range");
    }
    return pArr[position];
}

void Vector::clean()
{
    delete[] pArr;
    pArr = nullptr;
}

void Vector::copy(const Vector& other)
{
    size = other.size;
    capacity = other.capacity;
    pArr = new int[capacity];
    for (size_t i = 0; i < size; i++) {
        pArr[i] = other.pArr[i];
    }
}

void Vector::push_back(int element)
{
    if (size >= capacity)
        expand();
    
    pArr[this->size] = element;
    this->size++;
}

void Vector::pop_back()
{
    if (size == 0)
        throw std::out_of_range("Vector.pop_back: No element to pop!");

    this->size--;
}

void Vector::expand()
{
    if (capacity == 0)
        capacity = DEFAULT_CAPACITY;
    else
        capacity *= 2;

    int* pNewArr = new int[this->capacity];

    for (size_t i = 0; i < size; i++) {
        pNewArr[i] = pArr[i];
    }
    delete[] pArr;
    pArr = pNewArr;
}

void Vector::print(std::ostream& out) const
{
    for (size_t i = 0; i < size; i++)
        out << pArr[i] << " ";
}

size_t Vector::getSize() const
{
    return size;
}

int& Vector::operator[](size_t index)
{
    return pArr[index];
}

const int& Vector::operator[](size_t index) const
{
    return pArr[index];
}
