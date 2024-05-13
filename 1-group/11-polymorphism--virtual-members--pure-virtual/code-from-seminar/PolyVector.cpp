#include "PolyVector.h"

PolyVector::PolyVector()
{}

PolyVector::PolyVector(const PolyVector& other) : PolyVector()
{
    Copy(other);
}

PolyVector& PolyVector::operator=(const PolyVector& other)
{
    if (this != &other)
    {
        Clear();
        Copy(other);
    }
    return *this;
}

PolyVector::~PolyVector()
{
    Clear();
}

void PolyVector::PushBack(CellBase* pElem)
{
    vec.push_back(pElem);
}

bool PolyVector::PopBack()
{
    if (vec.size() == 0)
        return false;

    delete[] vec[vec.size() - 1];

    return true;
}

size_t PolyVector::Size() const
{
    return vec.size();
}

CellBase* PolyVector::operator[](size_t index)
{
    return vec[index];
}

const CellBase* PolyVector::operator[](size_t index) const
{
    return vec[index];
}

CellBase* PolyVector::At(size_t index)
{
    return vec.at(index);
}

const CellBase* PolyVector::At(size_t index) const
{
    return vec.at(index);
}

void PolyVector::Copy(const PolyVector &other)
{
    try
    {
        vec.reserve(other.vec.size());
        for (size_t i = 0; i < other.vec.size(); i++)
            vec.push_back(other.vec[i]->Clone());
    }
    catch(...)
    {
        Clear();
        throw;
    }
}

void PolyVector::Clear()
{
    for (size_t i = 0; i < vec.size(); i++)
        delete vec[i];
    
    vec.clear();
}
