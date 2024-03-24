#include "Vector.h"
#include <stdexcept>
#include <fstream>
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

void Vector::push_back(int element) {
    if(size == capacity) {
        resize();
    }
    arr[this->size] = element;
    this->size++;
}

void Vector::resize() {
    capacity *=2;
    makeNewArr();
}

void Vector::makeNewArr() {
    int* newArr = new (std::nothrow) int[this->capacity];
    if(!newArr) {
        throw "Err";
    }
    for (size_t i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
}

void Vector::print(std::ostream& out) const {
    for (int i = 0; i < size; i++)
        out << arr[i] << " ";
}