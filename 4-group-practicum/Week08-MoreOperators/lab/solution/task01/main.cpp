#include "time.h"
#include <iostream>

int main ()
{
    Time t1(2, 20), t2(22, 30);

    std::cout << t1 + t2 << std::endl;

    std::cout << t1 + 3 << std::endl;

    std::cout << 2 + t1 << std::endl;

    std::cout << ++t1 << std::endl;
    std::cout << t1++ << std::endl;
    std::cout << t1 << std::endl;

    std::cout << std::boolalpha << (t1 < t2) << std::endl;

    return 0;
}