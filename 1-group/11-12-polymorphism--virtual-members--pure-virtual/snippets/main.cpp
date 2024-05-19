#include <iostream>
#include <typeinfo>
#include "Shape.h"
#include "Triangle.h"
#include "Square.h"
#include "Circle.h"

double sumOfPerimeters(const Shape* const*  arr,int size) {
    double sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += arr[i]->param();
    }
    return sum;
}

// This function is example how we can detect type of a child instane class
// This is a hacky way to do it
int countShapes(const Shape* const*  arr,int size, Shape::Type type) {
    int count = 0;
    for (size_t i = 0; i < size; i++) {
        if(arr[i]->getType() == type)
            count++;
    }
    return count;
}

int main() {
    Triangle a(1,2,3);
    Square square(1);
    Circle cirlce(5);

    // And this is the other hacky way to understant the type of the instance
    // In case it`s not castable to the expected type, it will return nullptr
    Shape* s = &square;
    Circle* whatsInHere = dynamic_cast<Circle*>(s);
    
    if(!whatsInHere){
        std::cout << "Nothing" << '\n';
    }
    else 
    std::cout << "Something" << '\n';

    const int size = 3;
    Shape* arr[size];
    arr[0] = &a;
    arr[1] = &square;
    arr[2] = &cirlce;

    std::cout << sumOfPerimeters(arr,size) << '\n';
    std::cout << countShapes(arr,size,Shape::TriangleType) << '\n';
    return 0;
}