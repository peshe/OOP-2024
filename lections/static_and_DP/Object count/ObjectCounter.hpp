/*
 Примерен код за демонстрация на статични членове на клас
 ФМИ, ООП 2024
*/

#pragma once

#ifndef __OBJECT_COUNTER_HEADER_INCLUDED_
#define __OBJECT_COUNTER_HEADER_INCLUDED_

namespace fmi::oop {

// Пример за клас, следящ броя на живите обекти
// Всеки обект има също свой уникален идентификатор.
class ObjectCounter
{
public:
    // Връща броя обекти, живи в момента.
    static int getCurrentCount();

public:
    // Подразбиращ се и копиращ конструктор. Променят броя живи обекти.
    // Задават уникален идентификатор
    ObjectCounter();
    ObjectCounter(const ObjectCounter&);

    // Деструктор - намалява броя живи обекти
    ~ObjectCounter();

    // При присвояване трябва да запазваме уникалния идентификатор
    ObjectCounter& operator=(const ObjectCounter& rhs);

    int getObjID() const;

private:
    static int count;
    static int nextID;

private:
    int x;
    const int id;

private:
    // Помощна функция за пресмятане на следващо ID на обект
    static int getNextID();
};

}// fmi::oop

#endif // __OBJECT_COUNTER_HEADER_INCLUDED_
