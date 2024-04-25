/* Примерен код за демонстрация на наследяване и наслояване;
   бавози и производни класове. Полиморфизъм.
 ФМИ, ООП 2024
*/

#pragma once

#ifndef __RECTANGLE_HEADER_INCLUDED_
#define __RECTANGLE_HEADER_INCLUDED_

#include "point.hpp"
#include "shape.hpp"

namespace fmi::oop {

// Клас правоъгълник.
// Той Е форма, така че наследява Shape
class Rectangle : public Shape
{
public:
    // Различни конструктори
    Rectangle(const Point& TopLeft, int width, int height);
    Rectangle(const Point& TopLeft, const Point& BtmRight);

    void moveTo(const Point& TopLeft);

    // Собствени имплементации на методите от Shape
    virtual double getArea() const override;
    virtual void print() const override;

    virtual Shape* clone() const override;

    // Методи за достъп до измеренията на класа (ширина и височина)
    void setWidth(unsigned int width);
    int getWidth() const;
    void setHeight(unsigned int height);
    int getHeight() const;

    // Методи за достъп до върховете.
    using Shape::getTopLeft;
    using Shape::getBtmRight;
};


class RectangleCreator : public ShapeCreator
{
public :
    RectangleCreator() : ShapeCreator("rectangle"){}
    virtual Shape* createShape(istream&) const override;
};

}

#endif // __RECTANGLE_HEADER_INCLUDED_
