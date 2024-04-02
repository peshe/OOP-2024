#include "vector.hpp"
using namespace fmi::oop;

int main()
{
    Vector V1(1);
    Vector V2(V1);
    Vector V3 = V1 + V2;

    V1[0] = 2;
    std::cout << V1 << std::endl;
    --V1;
    std::cout << V1 << std::endl;

    --V1;
    std::cout << V1 << std::endl;
    
    std::cout << (const char*)V3 << std::endl;
    return 0;
}
