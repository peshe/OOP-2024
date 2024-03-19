#include <iostream>
#include <cstring>
#include <cassert>

const std::size_t MAX_NAME_SIZE = 50;

class Person
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

    Person() : Person("", 0, 0.0) {}

    void setName(const char* name)
    {
        assert(name != nullptr);

        strcpy(this->name, name);
    }

    void setAge(const int age)
    {
        assert(age >= 0);

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

    void print() const
    {
        std::cout << "My name is " << this->name << ". I am " << this->age << 
                    " years old and I am " << this->weight << " kg." << std::endl;
    }
};

int main ()
{
    Person person("Stefcho", 20, 77.7);

    person.print();

    Person defaultPerson;
    defaultPerson.setName("Niki");
    defaultPerson.setAge(21);
    defaultPerson.setWeight(88.8);

    std::cout << "Name: " << defaultPerson.getName() << std::endl;
    std::cout << "Age: " << defaultPerson.getAge() << std::endl;
    std::cout << "Weight: " << defaultPerson.getWeight() << std::endl;

    return 0;
}