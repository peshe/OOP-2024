/* Примерен код за демонстрация на наследяване и наслояване;
   бавози и производни класове. Полиморфизъм.
 ФМИ, ООП 2024
*/

#pragma once

#ifndef __SHAPEFACTORY_HPP_INCLUDED_
#define __SHAPEFACTORY_HPP_INCLUDED_

#include "shape.hpp"

#include <string>
#include <cassert>

namespace fmi::oop {

// Клас фабрика за създаване на фигури по данни в поток
class ShapeFactory
{
public:
    // Тя ще е сингълтон.
    static ShapeFactory& getFactory()
    {
        static ShapeFactory theFactory;
        return theFactory;
    }

    // Метод за регистрация на абстрактен клас фабрика
    void registerShape(const ShapeCreator* creator)
    {
        assert(cnt < MaxNumShapeCreators);
        creators[cnt++] = creator;      // просто го забучваме в края на масива
    }

    // Метод фабрика
    Shape* createShape(istream& stream)
    {
        // Четем име
        std::string name;
        stream >> name;

        // и опитваме да намерим клас фабрика, който я разбира
        const ShapeCreator* crt = getCreator(name);
        if (crt) {
            // Ако да - обръщаме се към неговия абстрактен метод
            //  и оставяме той да се оправя...
            return crt->createShape(stream);
        }
        else {
            // иначе прескачаме до края на реда и казваме, че не сме се справили
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return nullptr;
        }
    }

private:
    // Метод за търсене на подходяща фабрика
    const ShapeCreator* getCreator(const std::string& str) const
    {
        // Питаме подред всички регистрирани дали познават командата
        for (int i = 0; i < cnt; ++i)
            // Ако да - намерили сме каквото искаме
            if (creators[i]->getShapeName() == str)
                return creators[i];

        // Ако никой не си познае името - връщаме невалидна стойност
        return nullptr;
    }

private:
    ShapeFactory():cnt(0){};
    ~ShapeFactory() = default;
    ShapeFactory(const ShapeFactory&) = delete;
    ShapeFactory& operator=(const ShapeFactory&) = delete;

private:
    static const int MaxNumShapeCreators = 10;

    // И собствени данни - колекция регистрирани фабрики
    const ShapeCreator* creators[MaxNumShapeCreators];
    int cnt;
};

}

#endif // __SHAPEFACTORY_HPP_INCLUDED_
