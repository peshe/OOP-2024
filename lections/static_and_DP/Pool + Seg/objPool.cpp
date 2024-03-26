/* 
 Примерен код за демонстрация на статични членове на клас.
 Басейн с работници (resource pool)
 ФМИ, ООП 2024
*/

#include "objPool.hpp"
#include <cassert>
#include <iostream>

namespace fmi::oop {

ObjectPool& ObjectPool::getPool()
{
    static ObjectPool thePool(maxWorkers);

    return thePool;
}

ObjectPool::ObjectPool(unsigned num)
    : numWorkers(num)
    , pool(nullptr)
    , isDigging(nullptr)
{
    pool = new(std::nothrow) Worker* [num];
    isDigging = new(std::nothrow) bool[num];
    if (!pool || !isDigging) {
        throw std::bad_alloc();
    }

    for (numFree = 0; numFree < num; ++numFree) {
        pool[numFree] = nullptr;
        isDigging[numFree] = false;
    }
}

ObjectPool::~ObjectPool()
{
    for (unsigned i = 0; i < numWorkers; ++i)
        delete pool[i];
    delete[] pool;
    delete[] isDigging;
}

Worker& ObjectPool::hireWorker()
{
    // В случай, че няма повече свободни работници
    if (!numFree) {
        throw "No free workers!\n";
    }

    for (unsigned i = 0; i < numWorkers; ++i) {
        // Търсим първия, който не е зает
        if (!isDigging[i]) {
            if (!pool[i]) { // Ако още не е създаден го създаваме
                // Какво ще стане, ако възникне изключение?
                pool[i] = new Worker(i);
            }
            // отеблязваме, че имаме нает
            --numFree;
            isDigging[i] = true;
            assert(!pool[i]->hired());
            pool[i]->hire();

            // и връщаме псевдоним на клиента
            return *pool[i];
        }
    }

    // Никога не трябва да стигнем този ред...
    assert(false);
}

void ObjectPool::dismissWorker(Worker& w)
{
    // Проверки за валидност
    assert (w.getNum() >= 0 && w.getNum() < numWorkers);
    if (!isDigging[w.getNum()]) {
        throw "Worker already dismissed!\n";
    }

    assert(w.hired());

    // Отбелязваме работника като свободен.
    w.fire();
    isDigging[w.getNum()] = false;
    ++numFree;
}

} // fmi::oop
