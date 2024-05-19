#include "Triangle.h"

Triangle::Triangle(int a, int b, int c) 
        : a(a),b(b),c(c)
        { }

double Triangle::param() const {
    return a + b + c;
}

Shape::Type Triangle::getType() const {
    return TriangleType;
}
