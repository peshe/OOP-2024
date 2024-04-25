/* Примерен код за демонстрация на наследяване и наслояване;
   бавози и производни класове. Полиморфизъм.
 ФМИ, ООП 2024
*/

#pragma once

#ifndef __SHAPE_HEADER_INCLUDED_
#define __SHAPE_HEADER_INCLUDED_

#include "point.hpp"

namespace fmi::oop {

// Базов клас описващ произволна фигура.
// Използва (наслоява) точка.
// Задава корен на полиморфна йерархия.
class Shape
{
public:
    Shape();
    virtual ~Shape();   // ЗАДЪЛЖИТЕЛНО виртуален деструктор!!!!

    // Общи методи за всички форми
    virtual void moveWith(const Point& vec);    // Транслация
    virtual double getArea() const = 0;         // Изчислява лицето -> чисто виртуален
    virtual void print() const;                 // Извежда информация за фигурата

    virtual Shape* clone() const = 0;           // Създава ПОЛИМОРФНО копие на обекта. Чисто виртуален

protected:
    // Понеже ограждащия правоъгълник е специфична данна
    // се осигуряват защитени методи за достъп.
    Point getTopLeft() const;
    void setTopLeft(const Point&);

    Point getBtmRight() const;
    void setBtmRight(const Point&);

private:
    // Помощен метод за поправка на ограждащия правоъгълник.
    // Използва се след промяна на някой от координатите му.
    void swapIfNeeded();

private:
    // Координати на ограждащия правоъгълник.
    // Заради специфичния контрол на достъп са частни
    Point TL, BR;
};

// Базов клас, нужен за да реализираме абстрактна фабрика за фигури.
class ShapeCreator
{
public:
    ShapeCreator(const char* shape);    // Определя каква форма може да създава по нейното име
    virtual ~ShapeCreator() = default;  // ЗАДЪЛЖИТЕЛНО виртуален деструктор
    const char* getShapeName() const {return name;}

    // Чисто виртуален метод, носещ знанието за създаване на специфична фигура
    virtual Shape* createShape(istream&) const = 0;

protected:
    // Име на фигура, по което ще се разпознава
    const char* name;
};

}

#endif // __SHAPE_HEADER_INCLUDED_
