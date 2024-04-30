#include <iostream>
#include <string>

class Person
{
private:
    double height;

protected:
    std::string name;
    int age;

public:
    Person() : name("<unknown>"), age(0), height(0)
    {
        std::cout << "Person::Person() called" << std::endl;
    }
    Person(const std::string& name, int age, double height) : name(name), age(age), height(height)
    {
        std::cout << "Person::Person(const std::string&, int, double) called" << std::endl;
    }

    ~Person()
    {
        std::cout << "Person::~Person() called" << std::endl;
    }
};

class Student : public Person
{
private:
    std::string facultyNumber;

public:
    Student() : facultyNumber("XXXX")
    {
        std::cout << "Student::Student() called" << std::endl;
    }

    Student(const std::string& name, int age, double height, const std::string& facultyNumber)
        : Person(name, age, height), facultyNumber(facultyNumber)
    {
        std::cout << "Student::Student(const std::string&, int, double, const std::string&) called" << std::endl;
    }

    ~Student()
    {
        std::cout << "Student::~Student() called" << std::endl;
    }
};

int main ()
{
    Student student;

    Person* personPtr = new Student("Maria", 20, 160, "82208");
    Student* studentPtr = new Student("Sonya", 20, 175, "82213");

    Person* newPersonPtr = studentPtr;
    Student* newStudentPtr = (Student*)personPtr;

    Person& personRf = student;
    Student& studentRf = student;

    Person& newPersonRf = studentRf;
    Student& newStudentRf = (Student&)personRf;

    delete personPtr;
    delete studentPtr;

    return 0;
}