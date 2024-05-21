#include <iostream>

class Flyable
{
public:
    Flyable()
    {
        std::cout << "I can fly" << std::endl;
    }

    virtual ~Flyable()
    {
        std::cout << "Bye, bye, flyable" << std::endl;
    }
};

class Mammal
{
public:
    Mammal()
    {
        std::cout << "I am mammal" << std::endl;
    }

    virtual ~Mammal()
    {
        std::cout << "Bye, bye, mammal" << std::endl;
    }
};

class Bat : public Mammal, public Flyable
{
public:
    Bat()
    {
        std::cout << "I am a bat" << std::endl;
    }

    ~Bat()
    {
        std::cout << "Bat destroyed" << std::endl;
    }
};

int main ()
{
    Bat b;

    return 0;
}