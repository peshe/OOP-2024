#include <iostream>
#include <cstring>
#include <cassert>

const std::size_t MAX_NAME_SIZE = 50;

struct Person
{
    char name[MAX_NAME_SIZE];
    int age;
    double weight;

    void print()
    {
        std::cout << "My name is " << this->name << ". I am " << this->age << 
                    " years old and I am " << this->weight << " kg." << std::endl;
    }

    Person(const char* name, int age, double weight)
    {
        strcpy(this->name, name);
        this->age = age;
        this->weight = weight;
    }
};

int main ()
{
    Person person("Stefcho", 20, 77.7);

    person.print();

    Person* dynamicallyAllocatedPerson = new (std::nothrow) Person("Dinamichen", 12, 45.2);
    if (!dynamicallyAllocatedPerson)
    {
        std::cout << "Memory problem!" << std::endl;
        return 1;
    }

    dynamicallyAllocatedPerson->print();
    delete dynamicallyAllocatedPerson;

    return 0;
}