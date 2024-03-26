/* 
 Примерен код за демонстрация на статични членове на клас.
 Шаблон singleton
 ФМИ, ООП 2024
*/
#include <iostream>
#include "Singleton.hpp"

using std::cout;
using std::endl;

namespace fmi::oop{

Singleton& Singleton::getInstance()
{
    static Singleton* instancePtr; // = nullptr is not needed here!
    if (!instancePtr) instancePtr = new Singleton;

    return *instancePtr;
}

void Singleton::print() const
{
    cout << "Hello design patterns! " << endl;
}

Singleton::Singleton()
{
    cout << "The instance is created!" << endl;
}

Singleton::~Singleton()
{
    cout << "The instance is destroyed!" << endl;
}

} // fmi::oop
