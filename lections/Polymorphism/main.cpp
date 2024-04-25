#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "filled_circle.hpp"
#include "shape_factory.hpp"

#include <iostream>
#include <fstream>

using namespace fmi::oop;

static void print(const Shape& s)
{
    s.print();
    std::cout << "Area: " << s.getArea() << "\n";
}

static void printCircle(const Circle& c)
{
    c.print();
    std::cout << "Area: " << c.getArea() << "\n";
}

void inheritanceTest()
{
    Point zero;
    Point point(3, 5);

// Това вече не работи. Защо?
/*
    std::cout << "Shape test: \n";
    Shape unknown;
    unknown.print();
    unknown.moveWith(point);
    unknown.print();
*/

    std::cout << "\n\nCircle test:\n";
    Circle c(zero, 3);
    print(c);
    printCircle(c);

    std::cout << "\n\nFilled Circle test:\n";
    FilledCircle fc(point, 5, "Black");
    print(Rectangle(zero, point));
    printCircle(fc);
    fc.print();
}

static void clearShapes(Shape**& picture, int cnt)
{
    for (int i = 0; i < cnt; ++i)
        delete picture[i];
    delete[] picture;
    picture = nullptr;
}

static double totalShapeArea(Shape*const* picture, int cnt)
{
    double sum = 0;
    for (int i = 0; i < cnt; ++i) {
        if (picture[i]) sum += picture[i]->getArea();
    }
    return sum;
}

void polyDemo()
{
    // Четем данни за фигури от файл
    std::ifstream file("test.txt");
    if(!file) return;   // проверка за успешно отваряне - не я забравяме :)

    // четем броя на фигурите
    int s;
    file >> s;

    // и създаваме ПОЛИМОРФЕН контейнер с толкова на брой елемента
    Shape** picture = new Shape*[s];

    // Посредством фабриката ги създаваме една по една
    for (int i = 0; i < s; ++i)
        picture[i] = ShapeFactory::getFactory().createShape(file);
    file.close();

    // След това обхождаме масива и правим нещо с него
    for (int i = 0; i < s; ++i) {
        if (picture[i]) {
            picture[i]->print();     // ПОЛИМОРФНО поведение
            std::cout << "\n\n";
        }
        else {
            std::cout << "Bad or unknown shape!\n\n\n";
        }
    }

    // Накрая разчистваме след себе си
    clearShapes(picture, s);
}

void polyDemo2()
{
    std::ifstream file("test.txt");
    int s;
    file >> s;

    Shape** picture = new Shape * [s];
    for (int i = 0; i < s; ++i)
        picture[i] = ShapeFactory::getFactory().createShape(file);
    file.close();
    std::cout << totalShapeArea(picture, s) << "\n";

    // Как да си направим копие на масива?
    int i;
    Shape** pictureCopy = new(std::nothrow) Shape * [s];
    if (pictureCopy) {
        try {
            for (i = 0; i < s; ++i) {
                pictureCopy[i] = picture[i] ? picture[i]->clone() : nullptr;
            }
        }
        catch (const std::bad_alloc&) {
            clearShapes(pictureCopy, i);
            std::cout << "Memory problem! All resources are cleared!\n";
        }
        catch (...) {
            clearShapes(pictureCopy, i);
            std::cout << "Unknown problem! All resources are cleared!\n";
        }
    }
    clearShapes(picture, s);

    if (pictureCopy) {
        std::cout << totalShapeArea(pictureCopy, s) << "\n";
        clearShapes(pictureCopy, s);
    }
}


int main()
{
    inheritanceTest();
//    polyDemo();
//    polyDemo2();

    return 0;
}
