#include <iostream>

struct Point
{
    double x;
    double y;
};

void printPoint(const Point& pt)
{
    std::cout << pt.x << ", " << pt.y;
}

int main()
{
    Point p1;
    p1.x = 3.0;
    p1.y = 2.0;

    Point p2 = { 3.0, 2.0 };
    Point p3 = p1;
    
    Point* ptrPoint = &p1;
    (*ptrPoint).x = 42.0;
    ptrPoint->y = 3.141592;

    //int* a, b, c;

    std::cout << p1.x << ", " << p1.y << "\n";
    std::cout << p2.x << ", " << p2.y << "\n";
    std::cout << p3.x << ", " << p3.y << "\n";
    std::cout << ptrPoint->x << ", " << ptrPoint->y << "\n";

    // std::cin >> p1;
    // std::cout << p1;

    printPoint( p3 );
    std::cout << "\n";

    return 0;
}
