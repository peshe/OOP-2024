#include <iostream>
#include <cstring>

const std::size_t MAX_NAME_SIZE = 50;

struct Person
{
private:
    char name[MAX_NAME_SIZE];
    int age;
    double weight;

public:
    Person(const char* name, int age, double weight)
        : age(age), weight(weight)
    {
        strcpy(this->name, name);
    }

    Person(): Person("", 0, 0.0) {}

    void print() const
    {
        std::cout << "My name is " << this->name << ". I am " << this->age << 
                    " years old and I am " << this->weight << " kg." << std::endl;
    }

    void setName(const char* name)
    {
        strcpy(this->name, name);
    }

    void setAge(const int age)
    {
        this->age = age;
    }

    void setWeight(const double weight)
    {
        this->weight = weight;
    }

    const char* getName() const
    {
        return this->name;
    }

    int getAge() const
    {
        return this->age;
    }

    double getWeight() const
    {
        return this->weight;
    }
};

// RULE OF 0 - No Copy constructor, Copy assignment operator or Destructor
// You shouldn't implement them if you don't have to work with dynamic memory

int main()
{
    Person simo("Simeon", 22, 77.4);

    simo.print();

    Person simoCopy;
    simoCopy = simo;

    simoCopy.print();

    simo.setName("Simo");
    simo.setAge(23);
    simo.setWeight(74.9);

    simo.print();
    simoCopy.print();

    return 0;
}