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

    void whoAmI() const
    {
        std::cout << "I am a person. My name is " << name << ". I am " << age << " years old." << std::endl;
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

    void whoAmI() const
    {
        Person::whoAmI();
        std::cout << "I am also a student, whose faculty number is " << this->facultyNumber << std::endl;
    }

    ~Student()
    {
        std::cout << "Student::~Student() called" << std::endl;
    }
};

int main ()
{
    Person* sonya = new Student("Sonya", 20, 175, "82213");

    Person ivancho("Ivancho", 56, 180);
    ivancho.whoAmI();

    Student kireto("Kireto", 22, 180, "7MI0800146");
    kireto.whoAmI();

    // sonya->whoAmI();

    delete sonya;

    return 0;
}