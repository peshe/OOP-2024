#include <iostream>
#include "Person.h"

int main()
{
    Person p; // The default constructor is called
    Person person("gosho"); // Parameterized constructor
    Person p2 = person; // Copy constructor
    Person p3(person);  // Copy constructor

    Person p5("tosho"); // Parameterized constructor

    person = p5;        // Operator=
    person = person;    // Operator=

    p2.SetName("Some really really really really long name");
    std::cout << person.GetName() << '\n';
    std::cout << p2.GetName() << '\n';

    return 0;
} // Destructors are automatically called here
