#pragma once
#include <vector>
#include "CellBase.h"

// This class implements a polymorphic (heterogeneous) vector
class PolyVector
{
public:
    PolyVector();
    PolyVector(const PolyVector& other);
    PolyVector& operator=(const PolyVector& other);
    ~PolyVector();

public:
    void PushBack(CellBase* pElem);
    bool PopBack();
    size_t Size() const;

    CellBase* operator[](size_t index);
    const CellBase* operator[](size_t index) const;

    CellBase* At(size_t index);
    const CellBase* At(size_t index) const;

private:
    void Copy(const PolyVector& other);
    void Clear();

private:
    std::vector<CellBase*> vec;
};
