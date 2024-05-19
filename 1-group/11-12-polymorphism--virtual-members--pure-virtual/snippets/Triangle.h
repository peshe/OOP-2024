#pragma once
#include "Shape.h"


class Triangle : public Shape{
public:
    Triangle(int a, int b, int c);
    ~Triangle() = default;
    double param() const override;
    Shape::Type getType() const override;
private:
    const int a;
    const int b;
    const int c;
};
