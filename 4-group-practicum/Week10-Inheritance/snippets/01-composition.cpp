#include <iostream>

class Point2D
{
private:
    int x, y;

public:
    Point2D()
    {
        std::cout << "Point2D::Point2D() called" << std::endl;
    }
    Point2D(int x, int y) : x(x), y(y)
    {
        std::cout << "Point2D::Point2D(int x, int y) called" << std::endl;
    }

    ~Point2D()
    {
        std::cout << "Point2D::~Point2D() called" << std::endl;
    }
};

class Triangle
{
private:
    Point2D a, b, c;

public:
    Triangle() // : a(0,0), b()
    {
        std::cout << "Triangle::Triangle() called" << std::endl;
    }
    Triangle(int x1, int y1, int x2, int y2, int x3, int y3) : a(x1, y1), b(x2, y2), c(x3, y3)
    {
        std::cout << "Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3) called" << std::endl;
    }
    ~Triangle()
    {
        std::cout << "Triangle::~Triangle() called" << std::endl;
    }
};

int main ()
{
    Triangle triangleOnStack;
    // Triangle triangleWithParameters(1,2,3,4,5,6);

    // Triangle* dynamicallyAllocatedTriangle = new Triangle();

    return 0;
}