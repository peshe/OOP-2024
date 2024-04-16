/*
 * Example source code by Dinesh Khandelwal from Quora.com
 * Modified to fit the OOP course style @ FMI
 */

#include <iostream>

const int DEFAULT_ENGINE_CYLINDERS = 8;

class Engine
{
public:
    Engine(int cylinders) : m_cylinders(cylinders) {}

    void start() {
        std::cout << "Engine with" << m_cylinders << " cylinders starts." << std::endl;
    }

protected:
    int m_cylinders;
};


class Car : private Engine  // "has-a" / "is-implemented-in-terms-of"
{
public:
    Car() : Engine(DEFAULT_ENGINE_CYLINDERS) {}
    using Engine::start;

    /// Very similar to using Engine::start();
    // void start() {
    //     Engine::start();
    // }
};


/// Variant with the classic composition
// class Car
// {
// public:
//     Car() : m_engine(DEFAULT_ENGINE_CYLINDERS) {}
//     void start() { m_engine.start(); }
// private:
//     Engine m_engine;
// };


/*
 * Differences between Composition and Private inharitnce:
 * The simple-composition variant is needed if you want to contain several Engines per Car.
 * The private-inheritance variant allows members of Car to convert a Car* to an Engine*
 * The private-inheritance variant allows access to the protected members of the base class
 * The private-inheritance variant allows Car to override Engine’s virtual functions.
 */


int main()
{
    Car c;
    c.start();

    

    return 0;
}
