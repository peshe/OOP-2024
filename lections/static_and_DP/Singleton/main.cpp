#include <iostream>
#include "Singleton.hpp"

using std::cout;
using std::endl;
using fmi::oop::Singleton;

int main()
{
    cout << "The main..." << endl;
    Singleton::getInstance().print();
    cout << "And once more: ";
    Singleton::getInstance().print();
    cout << "end main... " << endl;
    return 0;
}
