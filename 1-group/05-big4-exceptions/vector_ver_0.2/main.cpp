#pragma once
#include "Vector.h"
#include <iostream>

int main() {
    Vector a;
    for (int i =0; i < 10;i++)
        a.push_back(i);

    a.print(std::cout);

    // Finish the other methods and test the code...
}