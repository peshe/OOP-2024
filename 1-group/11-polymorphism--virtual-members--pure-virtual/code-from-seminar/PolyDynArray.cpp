#include <stdexcept>  // for std::out_of_range
#include "PolyDynArray.h"

static const size_t DEFAULT_CAPACITY = 4;

PolyDynArray::PolyDynArray() : pArr(nullptr), size(0), capacity(0)
{}

PolyDynArray::PolyDynArray(const PolyDynArray& other) : PolyDynArray()
{
    Copy(other);
}

PolyDynArray& PolyDynArray::operator=(const PolyDynArray& other)
{
    if (this != &other)
    {
        Clear();
        Copy(other);
    }
    return *this;
}

PolyDynArray::~PolyDynArray()
{
    Clear();
}

void PolyDynArray::PushBack(CellBase* pElem)
{
    if (size >= capacity)
        Expand();

    pArr[size] = pElem;  // doesn't copy, just saves the pointer (address) of the element
    size++;
}

bool PolyDynArray::PopBack()
{
    if (size == 0)
        return false;

    delete[] pArr[size - 1];
    size--;

    return true;
}

size_t PolyDynArray::Size() const
{
    return size;
}

CellBase* PolyDynArray::operator[](size_t index)
{
    return pArr[index];
}

const CellBase* PolyDynArray::operator[](size_t index) const
{
    return pArr[index];
}

CellBase* PolyDynArray::At(size_t index)
{
    if (index >= size)
        throw std::out_of_range("PolyDynArray::At() called with an index out of bounds.");

    return pArr[index];
}

const CellBase* PolyDynArray::At(size_t index) const
{
    if (index >= size)
        throw std::out_of_range("PolyDynArray::At() called with an index out of bounds.");

    return pArr[index];
}

void PolyDynArray::Expand()
{
    if (capacity == 0)
        capacity = DEFAULT_CAPACITY;
    else
        capacity *= 2;

    CellBase** tempArr = new CellBase* [capacity];
    for (size_t i = 0; i < size; i++)
        tempArr[i] = pArr[i];  // doesn't copy, just saves the pointer (address) of the element
    
    delete[] pArr;
    pArr = tempArr;
}

void PolyDynArray::Copy(const PolyDynArray &other)
{
    pArr = new CellBase* [other.capacity];
    capacity = other.capacity;
    size = 0;

    try
    {
        for (size_t i = 0; i < other.size; i++)
        {
            pArr[i] = other.pArr[i]->Clone();
            size++;
        }
    }
    catch(...)
    {
        Clear();
        throw;
    }
}

void PolyDynArray::Clear()
{
    for (size_t i = 0; i < size; i++)
        delete pArr[i];
    
    delete[] pArr;
    pArr = nullptr;
    size = 0;
    capacity = 0;
}
