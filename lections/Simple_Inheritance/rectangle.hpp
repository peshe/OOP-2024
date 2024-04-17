/* Примерен код за демонстрация на наследяване и наслояване;
   бавози и производни класове.
 ФМИ, ООП 2024
*/

#pragma once

#ifndef __RECTANGLE_HEADER_INCLUDED_
#define __RECTANGLE_HEADER_INCLUDED_

#include "point.hpp"
#include "shape.hpp"

namespace fmi::oop {


// Клас правоъгълник.
// Той СЪЩО Е и форма така че наследява Shape
class Rectangle : public Shape
{
public:
    // Различни конструктори
    Rectangle(const Point& TopLeft, int width, int height);
    Rectangle(const Point& TopLeft, const Point& BtmRight);

    // Собствени имплементации на методите от Shape
    void moveTo(const Point& TopLeft);
    double getArea()const;
    void print() const;

    // Методи за достъп до измеренията на класа (ширина и височина)
    void setWidth(unsigned int width);
    int getWidth() const;
    void setHeight(unsigned int height);
    int getHeight() const;

    // Методи за достъп до върховете.
    // Зажелебете използването на имплементации от базовия клас.
    // Така можете да "извадите на открито" защитени методи.
    // Някои компилатори все още не го позволяват, въпреки, че е по стандарт.
    using Shape::getTopLeft;
    using Shape::getBtmRight;

    // Това има ефекта на горния код, но е с по-различен синтаксис.
    //Point getTopLeft()const { return Shape::getTopLeft(); }
    //Point getBtmRight()const { return Shape::getBtmRight(); }
};

}

#endif // __RECTANGLE_HEADER_INCLUDED_
