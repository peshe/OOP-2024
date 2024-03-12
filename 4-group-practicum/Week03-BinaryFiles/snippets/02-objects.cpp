#include <iostream>
#include <fstream>
#include <cstring>

const std::size_t MAX_NAME_SIZE = 128;

struct Person
{
    char firstName[MAX_NAME_SIZE];
    char lastName[MAX_NAME_SIZE];
    unsigned int age;
};

void initialize(Person& person, const char* firstName, const char* lastName, unsigned int age);

void print(const Person& person);

int main ()
{
    Person person1, person2, person3;

    initialize(person1, "Peter", "Kolev", 21);
    initialize(person2, "Mirela", "Nikolova", 18);
    initialize(person3, "Borislav", "Draganov", 45);

    std::ofstream peopleOut("people.bin", std::ios::binary);

    if (!peopleOut.is_open())
    {
        std::cout << "Problem while opening the file" << std::endl;
        return 1;
    }

    peopleOut.seekp(0);

    // writing three people to a binary file, note the parameter of the 'sizeof' function
    peopleOut.write(reinterpret_cast<const char*>(&person1), sizeof(Person));
    peopleOut.write(reinterpret_cast<const char*>(&person2), sizeof(Person));
    peopleOut.write(reinterpret_cast<const char*>(&person3), sizeof(Person));

    peopleOut.close();

    Person temp;

    std::ifstream peopleIn("people.bin", std::ios::binary);

    if (!peopleIn.is_open())
    {
        std::cout << "Problem while opening the file" << std::endl;
        return 1;
    }

    peopleIn.seekg(0);
    // reading the first person
    peopleIn.read(reinterpret_cast<char*>(&temp), sizeof(Person));

    print(temp);

    peopleIn.seekg(2 * sizeof(Person), std::ios::beg);
    // moving the 'get' pointer 2 times the size of the Person class after the beginning of the file
    // which means we will print the third one
    peopleIn.read(reinterpret_cast<char*>(&temp), sizeof(Person));

    print(temp);

    peopleIn.close();

    return 0;
}

void initialize(Person& person, const char* firstName, const char* lastName, unsigned int age)
{
    strcpy(person.firstName, firstName);
    strcpy(person.lastName, lastName);
    person.age = age;
}

void print(const Person& person)
{
    std::cout << person.firstName << " " << person.lastName << ", " << person.age << " years old\n";
}