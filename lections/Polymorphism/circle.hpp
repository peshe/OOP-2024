/* Примерен код за демонстрация на наследяване и наслояване;
   бавози и производни класове. Полиморфизъм.
 ФМИ, ООП 2024
*/

#pragma once

#ifndef __CIRCLE_HEADER_INCLUDED_
#define __CIRCLE_HEADER_INCLUDED_

#include "point.hpp"
#include "shape.hpp"

namespace fmi::oop {

// Окръжност. Тя Е форма -> наследява Shape.
// Използва (наслоява върху) Point
class Circle : public Shape
{
public:
    Circle(const Point& center, int r);

    // Специфични за окръжността методи
    Point getCenter() const;
    void resize(unsigned int radius);   // Променя радиуса на окръжността
    void moveTo(const Point& center);

    // Собствени имплементации на методите наследени от Shape
    virtual double getArea() const override;
    virtual void print() const override;

    virtual Shape* clone() const override;
private:
    Point center;
    int radius;
};

class CircleCreator : public ShapeCreator
{
public :
    CircleCreator() : ShapeCreator("circle") {}  // Задаваме име circle
    virtual Shape* createShape(istream&) const override;
};

}

#endif // __CIRCLE_HEADER_INCLUDED_
