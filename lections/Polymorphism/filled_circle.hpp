/* Примерен код за демонстрация на наследяване и наслояване;
   бавози и производни класове. Полиморфизъм.
 ФМИ, ООП 2024
*/

#pragma once

#ifndef __FILLED_CIRCLE_HEADER_INCLUDED_
#define __FILLED_CIRCLE_HEADER_INCLUDED_

#include "circle.hpp"
#include <string>

namespace fmi::oop {

using std::string;

// По-широк вид окръжност - запълнена с фон окръжност.
// Тя Е окръжност -> наследява Circle
class FilledCircle : public Circle
{
public:
    FilledCircle(const Point& center, int r, const char* color = "white");
    FilledCircle(const FilledCircle& rhs);
    ~FilledCircle();
    FilledCircle& operator=(const FilledCircle& rhs);

    // Предефинира единствено метода за извеждане на информация
    virtual void print() const override;

    virtual Shape* clone() const override;
private:
    // Има специфични данни за цвят
    char* color;
};


class FCCreator : public ShapeCreator
{
public :
    FCCreator() : ShapeCreator("filled"){}
    virtual Shape* createShape(istream&) const override;
};

}

#endif // __FILLED_CIRCLE_HEADER_INCLUDED_
