#include <iostream>
#include <cstring>

class Person
{
protected:
    char* name;
    int age;

    void copy(const Person& other)
    {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);

        this->age = other.age;
    }
    void deallocate()
    {
        delete[] this->name;
        this->name = nullptr;
    }

public:
    Person() : name(nullptr), age(0) {}
    Person(const char* name, int age) : name(new char[strlen(name) + 1]), age(age)
    {
        strcpy(this->name, name);
    }
    Person(const Person& other)
    {
        this->copy(other);
    }
    Person& operator = (const Person& other)
    {
        if (this != &other)
        {
            this->deallocate();
            this->copy(other);
        }

        return *this;
    }
    virtual ~Person()
    {
        std::cout << "~Person()\n";
        this->deallocate();
    }
};

class Student : public Person
{
private:
    char* facultyNumber;

    void copy(const Student& other)
    {
        this->facultyNumber = new char[strlen(other.facultyNumber) + 1];
        strcpy(this->facultyNumber, other.facultyNumber);
    }

    void deallocate()
    {
        delete[] this->facultyNumber;
        this->facultyNumber = nullptr;
    }

public:
    Student() : Person(), facultyNumber(nullptr) {}
    Student(const char* name, int age, const char* facultyNumber) :
        Person(name, age), facultyNumber(new char[strlen(facultyNumber) + 1])
    {
        strcpy(this->facultyNumber, facultyNumber);
    }
    Student(const Student& other) : Person(other)
    {
        this->copy(other);
    }
    Student& operator = (const Student& other)
    {
        if (this != &other)
        {
            this->deallocate();
            Person::deallocate();
            Person::copy(other);
            this->copy(other);
        }

        return *this;
    }
    ~Student()
    {
        std::cout << "~Student()\n";
        this->deallocate();
    }

    void setName(const char* name)
    {
        delete[] this->name;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    void print() const
    {
        std::cout << "Name: " << this->name << std::endl;
        std::cout << "Age: " << this->age << std::endl;
        std::cout << "FN: " << this->facultyNumber << std::endl;
    }
};

int main ()
{
    Student student("Mihail", 20, "72453");

    Student studentCopyCtr(student);
    studentCopyCtr.setName("Mishou");

    Student studentOp;
    studentOp = student;
    studentOp.setName("Pernichanina");

    student.print();
    studentCopyCtr.print();
    studentOp.print();

    Person* personPtr = new Student(student);
    delete personPtr; // What happens when ~Person() is not virtual?

    return 0;
}