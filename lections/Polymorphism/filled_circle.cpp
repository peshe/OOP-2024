/* Примерен код за демонстрация на наследяване и наслояване;
   бавози и производни класове. Полиморфизъм.
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
    color = color ? color : "";
    this->color = new char[strlen(color)+1];
    strcpy(this->color, color);
}

FilledCircle::FilledCircle(const FilledCircle& rhs)
    : Circle(rhs)
{
    this->color = new char[strlen(rhs.color)+1];
    strcpy(this->color, rhs.color);
}

FilledCircle::~FilledCircle()
{
    delete[] color;
}

FilledCircle& FilledCircle::operator=(const FilledCircle& rhs)
{
    if (this != &rhs)
    {
        Circle::operator=(rhs);
        size_t len = strlen(rhs.color);
        if (len > strlen (this->color)) {
            char* newColor = new char[len + 1];
            delete[] color;
            color = newColor;
        }
        strcpy(this->color, rhs.color);
    }
    return *this;
}

void FilledCircle::print() const
{
    cout << "Filled circle: ";
    Circle::print();
    cout << color << endl;
}

Shape* FilledCircle::clone() const
{
    return new FilledCircle(*this);
}

// Някакъв начин за четене на данни и създаване на кръг от поток
Shape* FCCreator::createShape(istream& is) const
{
    Point p;
    is >> p;
    int r;
    is >> r;
    char color[1024];
    is >> color;
    return new FilledCircle(p, r, color);
}

static FCCreator __;

}
