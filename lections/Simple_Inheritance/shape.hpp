/* Примерен код за демонстрация на наследяване и наслояване;
   бавози и производни класове.
 ФМИ, ООП 2024
*/

#pragma once

#ifndef __SHAPE_HEADER_INCLUDED_
#define __SHAPE_HEADER_INCLUDED_

#include "point.hpp"

namespace fmi::oop {

// Базов клас, описващ произволна фигура.
// Използва (наслоява, влага) класа точка.
class Shape
{
public:
    Shape();
    ~Shape();

    // Общи методи за всички форми
    void moveWith(const Point& vec);    // Транслация
    double getArea() const;             // Изчислява лицето
    void print() const;                 // Извежда информация за фигурата

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
    // Координати на ограждащия правоъгълник
    // Заради специфичния контрол на достъпа за частни
    Point TL, BR;
};

}
#endif // __SHAPE_HEADER_INCLUDED_
