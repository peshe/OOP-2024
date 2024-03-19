#include <iostream>
#include <cstring>
#include <cassert>

class Teacher
{
private:
    char* name;
    char* subject;
    
public:
    void initialize(const char* name, const char* subject)
    {
        std::cout << "Inside initialize" << std::endl;

        this->setName(name);

        if (!this->name) 
        {            
            return;
        }

        this->setSubject(subject);

        if (!this->subject) 
        {
            delete[] this->name;
            return;
        }
    }

    void setName(const char* name) 
    {
        delete[] this->name;
        this->name = new (std::nothrow) char[strlen(name) + 1];

        if (!this->name)
        {
            std::cout << "Memory problem" << std::endl;
            return;
        }
        
        strcpy(this->name, name);
    }

    void setSubject(const char* subject) 
    {
        delete[] this->subject;
        this->subject = new (std::nothrow) char[strlen(subject) + 1];
        
        if (!this->subject)
        {
            std::cout << "Memory problem" << std::endl; 
            return;
        }
        
        strcpy(this->subject, subject);
    }

    const char* getName() const 
    {
        return this->name;
    }

    const char* getSubject() const 
    {
        return this->subject;
    }

    void print() const
    {
        std::cout << "My name is " << this->name << " and I am teaching " << this->subject << "." << std::endl;
    }

	void cleanUp()
    {
        std::cout << "Inside cleanUp" << std::endl;

        delete[] this->name;
        delete[] this->subject;
    }
};

int main ()
{
    Teacher teacher;
	teacher.initialize("Borislav Draganov", "DIS2");
    if (!teacher.getName())
    {
        return 1;
    }

    teacher.print();

    Teacher* dynamicallyAllocatedTeacher = new (std::nothrow) Teacher;
    if (!dynamicallyAllocatedTeacher)
    {
        std::cout << "Memory problem!" << std::endl;
        return 1;
    }

	dynamicallyAllocatedTeacher->initialize("Bogdan Alexandrov", "Geometry");
    if (!dynamicallyAllocatedTeacher->getName())
    {
        delete dynamicallyAllocatedTeacher;
        return 1;
    }

    dynamicallyAllocatedTeacher->print();

	dynamicallyAllocatedTeacher->cleanUp();
    delete dynamicallyAllocatedTeacher;
	
	teacher.cleanUp();
    return 0;
}
