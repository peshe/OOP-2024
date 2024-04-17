/* Примерен код за демонстрация на наследяване и наслояване;
   бавози и производни класове.
 ФМИ, ООП 2024
*/

#include "filled_circle.hpp"

#include <iostream>
#include <cstring>

namespace fmi::oop {

using std::cout;
using std::endl;


FilledCircle::FilledCircle(const Point& center, int r, const char* color)
    : Circle(center, r)
{
    setColor(color);
}

FilledCircle::~FilledCircle()
{
    delete[] color;
}

FilledCircle::FilledCircle(const FilledCircle& rhs)
    : Circle(rhs)
{
    setColor(rhs.color);
}

FilledCircle& FilledCircle::operator=(const FilledCircle& rhs)
{
    if (this != &rhs) {
        Circle::operator=(rhs);
        delete[] color;
        setColor(rhs.color);
    }
    return *this;
}

void FilledCircle::print() const
{
    cout << "Filled circle: ";
    Circle::print();
    cout << color << endl;
}

void FilledCircle::setColor(const char* color)
{
    this->color = new char[strlen(color)+1];
    strcpy(this->color, color);
}

}
