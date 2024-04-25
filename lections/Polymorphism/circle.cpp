/* Примерен код за демонстрация на наследяване и наслояване;
   бавози и производни класове. Полиморфизъм.
 ФМИ, ООП 2024
*/

#include "circle.hpp"

#include <iostream>

namespace fmi::oop {

using std::cout;
using std::endl;

Circle::Circle(const Point& center, int r)
    : center(center)
{
    if (r <= 0) throw "Incorrect value for radius";

    resize(r);
}

Point Circle::getCenter() const
{
    return center;
}

void Circle::moveTo(const Point& point)
{
    Point moveVector(point.getX() - center.getX(), point.getY() - center.getY());
    moveWith(moveVector);

    center = point;
}

void Circle::resize(unsigned int radius)
{
    if (radius > 0) {
        this->radius = radius;
        setTopLeft(Point(center.getX() - (radius+1)/2, center.getY() + (radius+1)/2));
        setBtmRight(Point(center.getX() + (radius+1)/2, center.getY() - (radius+1)/2));
    }
}

double Circle::getArea()const
{
    return radius*radius*3.1415;
}

void Circle::print() const
{
    cout << "Info for a circle:\n";
    // Използване на базов метод и надграждането му в наследника
    Shape::print();
    cout << "Center: " << center << "\n";
    cout << "Radius: " << radius << endl;
}

// Стандартна имплементация на полиморфно клониране
Shape* Circle::clone() const
{
    return new Circle(*this);
}

// Някакъв начин за четене на данни и създаване на окръжност от поток
Shape* CircleCreator::createShape(istream& is) const
{
    Point p;
    is >> p;
    int r;
    is >> r;
    return new Circle(p, r);
}

static CircleCreator __;

}
