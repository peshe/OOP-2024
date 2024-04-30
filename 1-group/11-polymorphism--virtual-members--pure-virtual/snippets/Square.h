#pragma once

#include "Shape.h"

class Square : public Shape{
public:
    explicit Square(int a);
    ~Square() = default;
    double param() const override;
    Shape::Type getType() const override;
private:
    const int a;
};