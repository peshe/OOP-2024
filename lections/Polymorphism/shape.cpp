/* Примерен код за демонстрация на наследяване и наслояване;
   бавози и производни класове. Полиморфизъм.
 ФМИ, ООП 2024
*/

#include "shape.hpp"
#include "shape_factory.hpp"

#include <iostream>

namespace fmi::oop {

using std::cout;
using std::endl;


Shape::Shape()
{
    //cout << "Shape created!" << endl;
}

Shape::~Shape()
{
    //cout << "Shape destroied!" << endl;
}

void Shape::moveWith(const Point& vec)
{
    // Използваме знанията за преместане, описани в класа за точка.
    TL.moveWith(vec);
    BR.moveWith(vec);
}

double Shape::getArea() const
{
    // Няма как да пресметнем лицето на базова (обща) фигура.
    // Затова изписваме някаква информация и връщаме 0.
    // Тази функция е обявена като чисто виртуална
    //   - няма как да се използва 'случайно'
    cout << "Calculating the ares - it is unknown..." << endl;
    return 0.0;
}

void Shape:: print() const
{
    cout << "Top left point: " << TL << endl;
    cout << "Bottom right point: " << BR << endl;
}

Point Shape::getTopLeft() const
{
    return TL;
}

void Shape::setTopLeft(const Point& point)
{
    TL = point;
    swapIfNeeded();
}

Point Shape::getBtmRight() const
{
    return BR;
}

void Shape::setBtmRight(const Point& point)
{
    BR = point;
    swapIfNeeded();
}

// Подреждаме точките, ако е нужно.
// Приемаме, че работим със стандартна, положителна координатна сиситема.
void Shape::swapIfNeeded()
{
    if (TL.getX() > BR.getX())
    {
        int x = TL.getX();
        TL.setX(BR.getX());
        BR.setX(x);
    }

    if (TL.getY() < BR.getY())
    {
        int y = TL.getY();
        TL.setY(BR.getY());
        BR.setY(y);
    }
}


// Работата на конструктора е да запомни името, но...
ShapeCreator::ShapeCreator(const char* name):name(name)
{
    // по-важното да се регистрира във фабриката!
    ShapeFactory::getFactory().registerShape(this);
}

}
