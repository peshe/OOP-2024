#include "Person.h"
#include <cstring>
#include <new>

Person::Person() : fName(nullptr)
{
}

Person::Person(const char* name) : Person()
{
    this->SetName(name);
}

Person::Person(const Person& other)
{
    copy(other);
}

Person& Person::operator=(const Person& other)
{
    // Standard implementation for an assignment operator
    if (this != &other)
    {
        clear();
        copy(other);
    }

    return *this;
}

Person::~Person()
{
    clear();
}

bool Person::SetName(const char* name)
{
    // Nothing to do if we're given a nullptr
    if (name == nullptr)
        return false;

    // Check if there's enough memory to hold the new name first
    char* tempName = new (std::nothrow) char[strlen(name) + 1];
    if (tempName == nullptr)
        return false;

    // If we allocated enough memory for the new name
    // then we can proceed to actually change the name
    delete[] fName;
    fName = tempName;
    strcpy(fName, name);
    return true;
}

const char* Person::GetName() const
{
    return fName;
}

void Person::clear()
{
    delete[] fName;
    fName = nullptr;
}

void Person::copy(const Person& other)
{
    fName = new char[strlen(other.fName) + 1];
    strcpy(fName, other.fName);
}
