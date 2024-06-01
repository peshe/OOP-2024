#include <iostream>
#include <cmath>

class Shape
{
public:
    virtual double getPerimeter() = 0;
    virtual double getArea() = 0;

    virtual void print() const = 0;

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

    virtual void print() const
    {
        std::cout << "Triangle with sides " << a << " " << b << " " << c << std::endl;
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

    virtual void print() const
    {
        std::cout << "Circle with radius " << r << std::endl;
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

    virtual void print() const
    {
        std::cout << "Rectangle with sides " << a << " " << b << std::endl;
    }
};

class ShapeFactory
{
private:
    static char askUser()
    {
        std::cout << "What kind of shape do you want to create?\n";
        std::cout << "C - Circle\n";
        std::cout << "T - Triangle\n";
        std::cout << "R - Rectangle\n";
        std::cout << "Enter your choice: ";

        char ch;
        std::cin >> ch;

        while (tolower(ch) != 'c' && tolower(ch) != 't' && tolower(ch) != 'r')
        {
            std::cout << "Invalid choice, try again: ";
            std::cin >> ch;
        }

        return tolower(ch);
    }

    static double enterPositiveNumber(const char* label)
    {
        double number;
        std::cout << "Enter " << label << ": ";
        std::cin >> number;

        while (number <= 0)
        {
            std::cout << "The " << label << " should be a positive number, try again: ";
            std::cin >> number;
        }

        return number;
    }

    static Circle* createCircle()
    {
        double radius = enterPositiveNumber("radius of the circle");

        return new Circle(radius);
    }

    static Triangle* createTringle()
    {
        double firstSide = enterPositiveNumber("first side of the triangle");
        double secondSide = enterPositiveNumber("second side of the triangle");
        double thirdSide = enterPositiveNumber("third side of the triangle");

        return new Triangle(firstSide, secondSide, thirdSide);
    }

    static Rectangle* createRectangle()
    {
        double length = enterPositiveNumber("length of the rectangle");
        double width = enterPositiveNumber("width of the rectangle");

        return new Rectangle(length, width);
    }

public:
    static Shape* createShape()
    {
        switch (askUser())
        {
        case 'c':
            return createCircle();
        case 't':
            return createTringle();
        case 'r':
            return createRectangle();
        }

        return nullptr;
    }

};

int main ()
{
    Shape* shape = ShapeFactory::createShape();
        
    shape->print();

    delete shape;

    return 0;
}