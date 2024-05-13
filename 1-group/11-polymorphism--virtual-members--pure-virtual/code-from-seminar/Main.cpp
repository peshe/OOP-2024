#include <iostream>
#include "CellString.h"
#include "CellNumber.h"
#include "PolyDynArray.h"
#include "PolyVector.h"

void Print(const CellBase* pCell)
{
    if (!pCell)
        return;

    pCell->Print();  // this uses the child's implementation of Print()
}

double SumNumberCells(const PolyDynArray& arr)
{
    double sum = 0;
    for (size_t i = 0; i < arr.Size(); i++)
    {
        const CellNumber* pNum = dynamic_cast<const CellNumber*>(arr[i]);
        if (pNum)
            sum += pNum->Value();
    }
    return sum;
}

size_t CountStringCells(const PolyVector& vec)
{
    size_t count = 0;
    for (size_t i = 0; i < vec.Size(); i++)
    {
        // We don't need to use CellString method's so we don't need to dynamic_cast
        if (vec[i]->Type() == CellType::STRING)
            count++;
    }
    return count;
}

int main()
{
    // CellNumber num(5);
    // CellString str("fmi");

    // Print(&num);
    // Print(&str);
    
    /// Polymorphic Dynamic Array
    std::cout << " --- Polymorphic Dynamic Array ---\n";

    PolyDynArray arr;
    arr.PushBack(new CellNumber(42));
    arr.PushBack(new CellString("not fmi"));
    arr.PushBack(new CellNumber(124));

    for (size_t i = 0; i < arr.Size(); i++)
        arr[i]->Print();
    
    std::cout << "Sum of numbers: " << SumNumberCells(arr) << '\n';

    /// Polymorphic Vector
    std::cout << " --- Polymorphic Vector ---\n";

    PolyVector vec;
    vec.PushBack(new CellString("vector fmi"));
    vec.PushBack(new CellNumber(13));
    vec.PushBack(new CellNumber(9));
    vec.PushBack(new CellNumber(120));

    for (size_t i = 0; i < vec.Size(); i++)
        vec[i]->Print();

    std::cout << "String cells count: " << CountStringCells(vec) << '\n';

    return 0;
}
