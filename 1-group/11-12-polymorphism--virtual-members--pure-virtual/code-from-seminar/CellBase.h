#pragma once
#include "CellTypes.h"

class CellBase
{
public:
    CellBase(CellType type) : type(type) {}
    virtual ~CellBase() = default;  // IMPORTANT!

    virtual CellBase* Clone() const = 0;
    virtual void Print() const = 0;

    CellType Type() const { return type; };

private:
    const CellType type;
};
