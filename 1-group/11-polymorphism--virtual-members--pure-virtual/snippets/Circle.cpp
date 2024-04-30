#include "Circle.h"

static const double pi = 3.14;

Circle::Circle(int radius) :radius(radius)
{ }

double Circle::param() const {
    return (2 * pi * radius);
}

Shape::Type Circle::getType() const {
    return CircleType;
}
