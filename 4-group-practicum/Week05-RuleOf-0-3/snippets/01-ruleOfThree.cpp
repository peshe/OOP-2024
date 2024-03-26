#include <iostream>
#include <cstring>
#include <cassert>

const std::size_t MAX_COLOR_SIZE = 128;

class Balloon
{
private:
    double price;
    char* color;

    void copy(const Balloon& other)
    {
        this->color = new (std::nothrow) char[strlen(other.color) + 1];
        if (!this->color)
        {
            std::cout << "Memory problem!" << std::endl;
            return;
        }
        strcpy(this->color, other.color);

        this->price = other.price;
    }

    void deallocate()
    {
        delete[] this->color;
    }

public:
    Balloon(): price(0.0), color(nullptr) {}

    Balloon(const double price, const char* color)
        : color(nullptr)
    {
        this->setPrice(price);
        this->setColor(color);
    }

    void print() const
    {
        assert(this->color != nullptr);

        std::cout << "I am a baloon, my color is " << this->color << " and my price is " << this->price << std::endl; 
    }

    double getPrice() const
    {
        return this->price;
    }

    const char* getColor() const
    {
        return this->color;
    }

    void setPrice(const double price)
    {
        assert(price >= 0.0);

        this->price = price;
    }

    void setColor(const char* color)
    {
        assert(color != nullptr);

        delete[] this->color;
        this->color = new (std::nothrow) char[strlen(color) + 1];
        if (!this->color)
        {
            std::cout << "Memory problem!" << std::endl;
            return;
        }

        strcpy(this->color, color);
    }

    ~Balloon()
    {
        this->deallocate();
    }

    Balloon(const Balloon& other) // copy constructor
    {
        std::cout << "Inside copy constructor" << std::endl;

        this->copy(other);
    }

    Balloon& operator = (const Balloon& other) // copy assignment operator
    {
        std::cout << "Inside operator =" << std::endl;

        if (this != &other)
        {
            this->deallocate();
            this->copy(other);
        }

        return *this;
    }
};

// RULE OF 3 - Copy constructor, Copy assignment operator and Destructor
// You should implement them if you work with dynamic memory

int main ()
{
    int a = 5;

    int copyA;
    copyA = a;

    a = 6;

    std::cout << a << " " << copyA << std::endl;


    Balloon red(10, "red");

    Balloon copyAssignementRed;
    copyAssignementRed = red;

    red.setColor("more red");

    red.print();
    copyAssignementRed.print();

    Balloon copyConstructorRed(red);
    copyConstructorRed.print();

    Balloon mysteriousRed = red;
    mysteriousRed.print();

    return 0;
}