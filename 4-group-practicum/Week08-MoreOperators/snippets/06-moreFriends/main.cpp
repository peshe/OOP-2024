#include "money.h"
#include <iostream>

int main ()
{
    Money m(2, 20);

    std::cout << m + 1 << std::endl;
    std::cout << 2 + m << std::endl;

    return 0;
}