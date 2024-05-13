#include <iostream>
#include <string>

class Animal
{
private:
    std::string name;
    int age;

public:
    Animal(const std::string& name, int age) : name(name), age(age) {}

    virtual void whoAmI() const
    {
        std::cout << "Name: " << this->name << std::endl;
        std::cout << "Age: " << this->age << std::endl;
    }

    virtual void makeSound() const = 0;

    virtual ~Animal() = default;
};

class Dog : public Animal
{
public:
    Dog(const std::string& name, int age) : Animal(name, age) {}

    virtual void makeSound() const override
    {
        std::cout << "Bau" << std::endl;
    }

    virtual void whoAmI() const override
    {
        Animal::whoAmI();
        std::cout << "A am a dog" << std::endl;
    }

    virtual ~Dog() = default;
};

class Pitbull : public Dog
{
public:
    Pitbull() : Dog("Pit", 2) {}

    virtual void makeSound() const override final
    {
        std::cout << "Bau, Bau" << std::endl;
    }

    virtual void whoAmI() const override final
    {
        Dog::whoAmI();
        std::cout << "Pitbull" << std::endl;
    }

    virtual ~Pitbull() = default;
};

class Cat : public Animal
{
public:
    Cat(const std::string& name, int age) : Animal(name, age) {}

    virtual void makeSound() const override
    {
        std::cout << "Mqu" << std::endl;
    }

    virtual void whoAmI() const override
    {
        Animal::whoAmI();
        std::cout << "I am a cat" << std::endl;
    }

    virtual ~Cat() = default;
};

class Glarus : public Animal
{
public:
    Glarus(const std::string& name, int age) : Animal(name, age) {}

    virtual void makeSound() const override
    {
        std::cout << "Dai mi duneraaa" << std::endl;
    }

    virtual void whoAmI() const override
    {
        Animal::whoAmI();
        std::cout << "Az sam gadina" << std::endl;
    }

    virtual ~Glarus() = default;
};

int main ()
{
    Animal* animals[4];
    animals[0] = new Dog("Sharo", 3);
    animals[1] = new Pitbull();
    animals[2] = new Cat("Bela", 5);
    animals[3] = new Glarus("Gadina 365", 1); 

    for (int i = 0; i < 4; ++i)
    {
        animals[i]->makeSound();
        animals[i]->whoAmI();
        std::cout << "-----------" << std::endl;
    }   

    for (int i = 0; i < 4; ++i)
    {
        delete animals[i];
    }

    return 0;
}