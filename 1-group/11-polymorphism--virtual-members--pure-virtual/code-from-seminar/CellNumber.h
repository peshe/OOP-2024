#pragma once
#include "CellBase.h"

class CellNumber : public CellBase
{
public:
    CellNumber(double num) : CellBase(CellType::NUMBER), number(num) {}

    CellBase* Clone() const override;
    void Print() const override;
    double Value() const;

private:
    double number;
};
