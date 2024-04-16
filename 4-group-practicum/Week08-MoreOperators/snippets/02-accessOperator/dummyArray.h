#pragma once
#include <iostream>

const std::size_t MAX_CAPACITY = 128;

class DummyArray
{
private:
    int array[MAX_CAPACITY];
    std::size_t size;

public:
    DummyArray(const int* array, std::size_t size);

    int& operator [] (std::size_t index);
    const int& operator [] (std::size_t index) const;
};