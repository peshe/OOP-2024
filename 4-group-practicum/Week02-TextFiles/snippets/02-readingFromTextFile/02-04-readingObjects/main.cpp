#include <iostream>
#include <fstream>

const std::size_t MAX_NAME_SIZE = 64;

struct Person
{
    char firstName[MAX_NAME_SIZE];
    char lastName[MAX_NAME_SIZE];
    unsigned int age;
};

void readPerson (std::ifstream& in, Person& person);

void printPerson (const Person& person);

int main ()
{
    std::ifstream people("people.txt"); 

    if (!people.is_open()) // always check if the opening is successfull
    {
        std::cout << "Problem while opening the file" << std::endl;
        return 1;
    }

    // Reading the file line by line

    Person tempPerson;
    while (!people.eof()) // reading until end of file
    {
        readPerson(people, tempPerson);
        printPerson(tempPerson);
    }

    people.close();

    return 0;
}

void readPerson (std::ifstream& in, Person& person)
{
    in >> person.firstName >> person.lastName >> person.age;
}

void printPerson (const Person& person)
{
    std::cout << person.firstName << " " << person.lastName 
        << " " << person.age << std::endl;
}