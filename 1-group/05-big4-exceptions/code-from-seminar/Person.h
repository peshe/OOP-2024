#pragma once

/** 
 * This is a sample class containing dynamically allocated memory (the name)
 * and thus implementing the rule of three (the big four)
 * ```Constructor, Copy constructor, Assignment operator, Destructor```
 **/
class Person
{
// Public methods
public:
    // Default Constructor
    Person();

    // Parameterized constructor
    Person(const char* name);

    // Copy constructor
    Person(const Person& other);

    // Assignment operator
    Person& operator=(const Person& other);

    // Destructor
    ~Person();

    // Change the person's name
    // @returns true if the change was successful, false otherwise
    bool SetName(const char* name);

    // @returns the person's name
    const char* GetName() const;

// Private utility methods
private:
    // Deletes all of the object's dynamic memory
    void clear();

    // Deep copies from another object (person)
    // @throws bad_alloc when there's not enough memory
    void copy(const Person& other);

// Private fields
private:
    // Dynamically allocated char array storing the person's name
    char* fName;
};
