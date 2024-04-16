#include "dummyArray.h"
#include <cassert>

DummyArray::DummyArray(const int* array, std::size_t size)
    : size(size)
{
    for (std::size_t i = 0; i < size; ++i)
    {
        this->array[i] = array[i];
    }
}

int& DummyArray::operator [] (std::size_t index)
{
    assert(index < this->size);

    return this->array[index];
}

const int& DummyArray::operator [] (std::size_t index) const
{
    assert(index < this->size);

    return this->array[index];
}