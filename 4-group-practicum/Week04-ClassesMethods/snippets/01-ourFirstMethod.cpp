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
};

void printPerson(const Person& person)
{
    std::cout << "My name is " << person.name << ". I am " << person.age << 
                    " years old and I am " << person.weight << " kg." << std::endl;
}

void initialize(Person& person, const char* name, int age, double weight)
{
    strcpy(person.name, name);
    person.age = age;
    person.weight = weight;
}

int main ()
{
    Person person;

    initialize(person, "Stefcho", 20, 77.7);

    printPerson(person);
    person.print();

    return 0;
}