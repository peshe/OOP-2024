/* 
Примерен код за демонстрация на статични членове на клас
 ФМИ, ООП 2024
*/

#include "ObjectCounter.hpp"

namespace fmi::oop {

//Инициализиране на статичните членове
int ObjectCounter::count = 0;
int ObjectCounter::nextID = 0;

int ObjectCounter::getCurrentCount()
{
    return count;
}

ObjectCounter::ObjectCounter()
    :id(ObjectCounter::getNextID())
{
    ++count;
    x = 0;
}

ObjectCounter::ObjectCounter(const ObjectCounter& rhs)
    :id(ObjectCounter::getNextID())
{
    ++count;
    this->x = rhs.x;
}

ObjectCounter::~ObjectCounter()
{
    --count;
}

ObjectCounter& ObjectCounter::operator=(const ObjectCounter& rhs)
{
    // В левия обект идентификаторът не се променя - пазим ID-то.
    x = rhs.x;
    return *this;
}

int ObjectCounter::getObjID() const
{
    return id;
}

int ObjectCounter::getNextID()
{
    return nextID++;
}

}// fmi::oop
