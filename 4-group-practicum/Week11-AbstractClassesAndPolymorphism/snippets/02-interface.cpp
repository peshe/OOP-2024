#include <iostream>
#include <cmath>

class Shape
{
public:
    virtual double getPerimeter() = 0;
    virtual double getArea() = 0;

    virtual ~Shape() = default;
};

class Triangle : public Shape
{
private:
    double a, b, c;

public:
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}

    virtual double getPerimeter() override
    {
        return a + b + c;
    }

    virtual double getArea() override
    {
        double semiPerimeter = this->getPerimeter() / 2;
        return std::sqrt(semiPerimeter * (semiPerimeter - a) * 
                        (semiPerimeter - b) * (semiPerimeter - c));
    }
};

class Circle : public Shape
{
private:
    static constexpr double PI = 3.14;
    double r;

public:
    Circle(double r) : r(r) {}

    virtual double getPerimeter() override
    {
        return 2 * PI * r;
    }

    virtual double getArea() override
    {
        return PI * r * r;
    }
};

class Rectangle : public Shape
{
private:
    double a, b;

public:
    Rectangle(double a, double b) : a(a), b(b) {}

    virtual double getPerimeter() override
    {
        return 2 * (a + b);
    }

    virtual double getArea() override
    {
        return a * b;
    }
};

int main ()
{
    Shape* shapes[3];
    shapes[0] = new Triangle(3,4,5);
    shapes[1] = new Circle(2);
    shapes[2] = new Rectangle(5,4);

    for (int i = 0; i < 3; ++i)
    {
        std::cout << "Perimeter: " << shapes[i]->getPerimeter() << std::endl;
        std::cout << "Area: " << shapes[i]->getArea() << std::endl;
    }

    for (int i = 0; i < 3; ++i)
    {
        delete shapes[i];
    }

    return 0;
}