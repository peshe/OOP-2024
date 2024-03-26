/* 
 Примерен код за демонстрация на статични членове на клас.
 Басейн с работници (resource pool)
 ФМИ, ООП 2024
*/

#pragma once

#ifndef __WORKER_HEADER_INCLUDED_
#define __WORKER_HEADER_INCLUDED_

namespace fmi::oop {

// Клас, представящ специалните ресурси - работници.
class Worker
{
    friend class ObjectPool;

public:
    void digForMe() const;
    bool hired() const { return isHired; }

private:
    // Само приятелският клас ще има достъп до тези методи.
    Worker(int num);
    ~Worker();

    Worker(const Worker&) = delete;
    Worker& operator=(const Worker&) = delete;

private:
    int getNum() const { return num; }
    
    void hire();
    void fire();

private:
    int num;
    bool isHired;
};

} // fmi::oop

#endif //__WORKER_HEADER_INCLUDED_
