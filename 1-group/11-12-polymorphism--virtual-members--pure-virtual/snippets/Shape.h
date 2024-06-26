#pragma once

class Shape {
public:
    enum Type { // In case we want to add a new derived class, we should change the base class as well, not the clearest approach.
    // On the other hand, this is in terms of OOP a bad practice. For some tasks/problems, it will be necessary.
        TriangleType,
        SquareType,
        CircleType
    };
    Shape() = default;
    virtual ~Shape() = default;
    virtual double param() const = 0;
    virtual Type getType()const = 0;
};