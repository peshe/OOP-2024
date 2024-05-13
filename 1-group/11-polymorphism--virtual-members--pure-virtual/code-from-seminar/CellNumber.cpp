#include <iostream>
#include "CellNumber.h"

CellBase* CellNumber::Clone() const
{
    return new CellNumber(*this);
}

void CellNumber::Print() const
{
    std::cout << "Number: " << number << '\n';
}

double CellNumber::Value() const
{
    return number;
}
