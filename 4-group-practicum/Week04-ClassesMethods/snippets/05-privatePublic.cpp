#include <iostream>
#include <cstring>
#include <cassert>

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

    Person() : Person("", 0, 0.0) {}

    void print()
    {
        std::cout << "My name is " << this->name << ". I am " << this->age << 
                    " years old and I am " << this->weight << " kg." << std::endl;
    }
};

int main ()
{
    Person person("Stefcho", 20, 77.7);

    person.print();

    // std::cout << person.age << std::endl;
    
    return 0;
}