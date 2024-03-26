/* 
 Примерен код за демонстрация на статични членове на клас.
 Басейн с работници (resource pool)
 ФМИ, ООП 2024
*/

#include <iostream>
#include <cassert>

#include "worker.hpp"


namespace fmi::oop {

void Worker::digForMe() const
{
    if (!isHired) {
        std::cout << "No! You have to hire me first!\n";
    }
    else {
        std::cout << "I'm " << num
                  << " and I will dig for you, Master!\n";
    }
}

Worker::Worker(int num) : num(num), isHired(false)
{
    std::cout << "Worker " << num << " created." << std::endl;
}

Worker::~Worker()
{
    std::cout << "Worker " << num << " destroyed." << std::endl;
}

void Worker::hire()
{
    assert(!isHired);
    isHired = true;
}

void Worker::fire()
{
    assert(isHired);
    isHired = false;
}

} // fmi::oop
