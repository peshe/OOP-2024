#include "Square.h"

Square::Square(int a) : a(a)
{ }

double Square::param() const {
    return 4 * a;
}

Shape::Type Square::getType() const {
    return SquareType;
}
