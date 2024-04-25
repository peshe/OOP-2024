/* Примерен код за демонстрация на наследяване и наслояване;
   бавози и производни класове.
 ФМИ, ООП 2024
*/

#pragma once

#ifndef __POINT_HEADER_INCLUDED_
#define __POINT_HEADER_INCLUDED_

#include <iostream>

namespace fmi::oop {

// Помощен клас Точка. Използва се за задаване на двойка координати, както и вектор в 2D
class Point
{
public:
    // Конструктор с аргументи по подразбиране
    Point(int x = 0, int y = 0);

    // методи за достъп до координатите
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);

    // Два метода за промяна на позиция на точка
    void moveWith(const Point& vec);   // транслация
    void moveTo(const Point& point);   // присвояване

private:
    // За простота са избрани целочислени координати
    int x, y;
};

using std::ostream;
using std::istream;
ostream& operator << (ostream& os, const Point& p);
istream& operator >> (istream& is, Point& p);

}

#endif // __POINT_HEADER_INCLUDED_
