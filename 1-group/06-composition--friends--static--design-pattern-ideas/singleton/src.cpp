#include <iostream>
#include "singleton.h"

int main()
{
    Singleton::Instance()->DoCount(42);
    Singleton::Instance()->DoCount(1337);

    std::cout << Singleton::Instance()->GetData() << std::endl;

    Singleton::Release();
    return 0;
}
