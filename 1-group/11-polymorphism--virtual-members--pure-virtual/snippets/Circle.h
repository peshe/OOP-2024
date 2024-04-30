#pragma once
#include "Shape.h"


class Circle : public Shape {
public:
    explicit Circle (int radius);
    ~Circle() = default;
    double param() const override;
    Shape::Type getType() const override;
private:
    const int radius; 
};
