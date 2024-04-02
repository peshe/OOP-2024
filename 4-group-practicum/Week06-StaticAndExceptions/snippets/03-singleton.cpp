#include <iostream>

class Singleton
{
private:
    static int counter;
    int id;

    Singleton()
    {
        this->id = counter++;
    }
public:
    Singleton(const Singleton& other) = delete;
    Singleton& operator = (const Singleton& other) = delete;

    static Singleton& getInstance()
    {
        static Singleton object;

        return object;
    }

    void whoAmI() const
    {
        std::cout << "I am instance #" << this->id << std::endl;
    }
};

int Singleton::counter = 0;

int main ()
{
    Singleton::getInstance().whoAmI();
    Singleton::getInstance().whoAmI();
    Singleton::getInstance().whoAmI();
    Singleton::getInstance().whoAmI();
    Singleton::getInstance().whoAmI();
    
    return 0;
}