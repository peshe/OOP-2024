/*
 Примерен код за демонстрация на статични членове на клас.
 Шаблон singleton
 ФМИ, ООП 2024
*/

#pragma once

#ifndef __SINGLETON_HEADER_INCLUDED_
#define __SINGLETON_HEADER_INCLUDED_

namespace fmi::oop {

// Пример за клас, от който има единствена инстанция.
class Singleton
{
public:
    // Статичен метод, през който се достъпва единствената инстанция
    static Singleton& getInstance();

public:
    // Някакво действие, което очакваме класа да извършва
    void print() const;

private:
    // Скриваме специалните методи
    Singleton();                    // Ако е са ни нужни добавяме параметри
    ~Singleton();                   // Скриване на деструктора ни предпазва от delete

    Singleton(const Singleton&);        // НЯМА да имплементираме копиращия конструктор
    void operator=(const Singleton&);   // също и оператора =. Забележете връщания тип.
};

} //fmi::oop

#endif //__SINGLETON_HEADER_INCLUDED_
