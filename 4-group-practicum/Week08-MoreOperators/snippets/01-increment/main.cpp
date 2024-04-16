#include "money.h"
#include <iostream>

int main ()
{
    Money m1(2, 20), m2(m1);

    std::cout << m1++ << std::endl;
    std::cout << ++m2 << std::endl;

    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;

    return 0;
}