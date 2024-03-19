#include <iostream>
#include <cstring>

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

    void initialize(const char* name, int age, double weight)
    {
        strcpy(this->name, name);
        this->age = age;
        this->weight = weight;
    }
};

int main ()
{
    Person person;

    person.initialize("Stefcho", 20, 77.7);
    person.print();

    return 0;
}