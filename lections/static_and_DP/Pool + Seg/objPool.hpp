/*
 Примерен код за демонстрация на статични членове на клас.
 Басейн с работници (resource pool)
 ФМИ, ООП 2024
*/

#pragma once

#ifndef __OBJECT_POOL_HEADER_INCLUDED_
#define __OBJECT_POOL_HEADER_INCLUDED_

#include "worker.hpp"

namespace fmi::oop {

// Клас, реализиращ басейна с работници.
// Самият той е сингълтон.
// Предоставя определен брой обекти от Worker, създадени при първа нужда.
class ObjectPool
{

public:
    // Максимален брой работници
    static const unsigned maxWorkers = 5;

public:
    // Връща единствената инстанция на клас
    static ObjectPool& getPool();

public:
    // Връща свободен работник от басейна или хвърля изключение
    Worker& hireWorker();

    // Освобождава нает работник.
    void dismissWorker(Worker& w);

private:
    ObjectPool(unsigned numWorkers);
    ~ObjectPool();

    ObjectPool(const ObjectPool&) = delete;
    ObjectPool& operator=(const ObjectPool&) = delete;

private:
    unsigned numWorkers;        // Общ брой работници
    unsigned numFree;           // Брой свободни работници
    Worker** pool;              // Басейн с работниците
    bool* isDigging;            // Индекс кои са свободни и кои работят
};

} // oop::fmi

#endif //__OBJECT_POOL_HEADER_INCLUDED_
