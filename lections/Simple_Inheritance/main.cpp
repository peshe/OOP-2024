/* Примерен код за демонстрация на наследяване и наслояване;
   бавози и производни класове.
 ФМИ, ООП 2024
*/

#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "filled_circle.hpp"

#include <iostream>
using namespace fmi::oop;

static void print(const Shape& s)
{
    s.print();
    std::cout << "Area: " << s.getArea() << '\n';
}

static void printCircle(const Circle& c)
{
    c.print();
    std::cout << "Area: " << c.getArea() << '\n';
}

void inheritanceTest()
{
    Point zero;
    Point point(3, 5);

    std::cout << "Shape test:\n";
    Shape unknown;
    unknown.print();
    unknown.moveWith(point);
    unknown.print();
    
    std::cout << "\n\nCircle test:\n";
    Circle c(zero, 3);
    print(c);
    printCircle(c);
    
    return;
    std::cout << "\n\nFilled Circle test:\n";
    FilledCircle fc(point, 5, "Black");
    printCircle(fc);
    fc.print();

    return;

    print(Rectangle(zero, point));
}


int main()
{
    inheritanceTest();
    return 0;
}
