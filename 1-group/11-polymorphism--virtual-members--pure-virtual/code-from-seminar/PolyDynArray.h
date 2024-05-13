#pragma once
#include <cstddef>  // for size_t
#include "CellBase.h"

// This class implements a polymorphic (heterogeneous) dynamicly resizing array
class PolyDynArray
{
public:
    PolyDynArray();
    PolyDynArray(const PolyDynArray& other);
    PolyDynArray& operator=(const PolyDynArray& other);
    ~PolyDynArray();

public:
    void PushBack(CellBase* pElem);
    bool PopBack();
    size_t Size() const;

    CellBase* operator[](size_t index);
    const CellBase* operator[](size_t index) const;

    CellBase* At(size_t index);
    const CellBase* At(size_t index) const;

private:
    void Expand();
    void Copy(const PolyDynArray& other);
    void Clear();

private:
    CellBase** pArr;
    size_t size;
    size_t capacity;
};
