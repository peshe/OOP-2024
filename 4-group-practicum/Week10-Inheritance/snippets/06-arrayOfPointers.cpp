#include <iostream>
#include <string>

class FMIPerson
{
private:
    std::string name;
    int age;

public:
    FMIPerson(const std::string& name, int age) : name(name), age(age) {}

    virtual void whoAmI() const
    {
        std::cout << "My name is " << this->name << " and I am " << this->age << " years old." << std::endl;
    }

    virtual ~FMIPerson() = default;
};

class Lecturer : public FMIPerson
{
private:
    std::string subject;
    int yearsOfExperience;

public:
    Lecturer(const std::string& name, int age, const std::string& subject, int yearsOfExperience)
        : FMIPerson(name, age), subject(subject), yearsOfExperience(yearsOfExperience) {}

    virtual void whoAmI() const
    {
        FMIPerson::whoAmI();
        std::cout << "I am a lecturer in FMI, I teach " << this->subject << " and I have "
        << this->yearsOfExperience << " years of experience" << std::endl;
    }

    virtual ~Lecturer() = default;
};

class Assistant : public FMIPerson
{
private:
    std::string subject;
    bool isPartTime;

public:
    Assistant(const std::string& name, int age, const std::string& subject, bool isPartTime)
        : FMIPerson(name, age), subject(subject), isPartTime(isPartTime) {}

    virtual void whoAmI() const
    {
        FMIPerson::whoAmI();
        std::string assistant = (this->isPartTime) ? "part-time" : "full-time";
        std::cout << "I am a " << assistant << " assistant in FMI and I teach " 
        << this->subject << std::endl;
    }

    virtual ~Assistant() = default;
};

class Student : public FMIPerson
{
private:
    std::string major;
    int year;
    int group;

public:
    Student(const std::string& name, int age, const std::string& major, int year, int group)
        : FMIPerson(name, age), major(major), year(year), group(group) {}

    virtual void whoAmI() const
    {
        FMIPerson::whoAmI();
        std::cout << "I am a " << this->year << "-year student in FMI, I study " 
        << this->major << " and I am group " << this->group << std::endl;
    }

    virtual ~Student() = default;
};

class FMI
{
private:
    static const std::size_t INITIAL_CAPACITY = 2;
    static const std::size_t INCREASE_STEP = 2;

    FMIPerson** fmi;
    std::size_t size;
    std::size_t capacity;

    void resize()
    {
        FMIPerson** newFMI = new FMIPerson*[this->capacity * FMI::INCREASE_STEP];
        for (std::size_t i = 0; i < this->size; ++i)
        {
            newFMI[i] = this->fmi[i];
        }

        delete[] this->fmi;
        this->fmi = newFMI;
        this->capacity *= FMI::INCREASE_STEP;
    }

    void add(FMIPerson* person)
    {
        if (this->size == this->capacity)
        {
            this->resize();
        }

        this->fmi[this->size++] = person;
    }

public:
    FMI() : fmi(new FMIPerson*[FMI::INITIAL_CAPACITY]), size(0), capacity(FMI::INITIAL_CAPACITY) {}
    FMI(const FMI& other) = delete;
    FMI& operator = (const FMI& other) = delete;
    ~FMI()
    {
        for (std::size_t i = 0; i < this->size; ++i)
        {
            delete this->fmi[i];
        }
        delete[] this->fmi;
    }

    void addFMIPerson(const std::string& name, int age)
    {
        this->add(new FMIPerson(name, age));
    }    

    void addLecturer(const std::string& name, int age, const std::string& subject, int yearsOfExperience)
    {
        this->add(new Lecturer(name, age, subject, yearsOfExperience));
    }

    void addAssistant(const std::string& name, int age, const std::string& subject, bool isPartTime)
    {
        this->add(new Assistant(name, age, subject, isPartTime));
    }

    void addStudent(const std::string& name, int age, const std::string& major, int year, int group)
    {
        this->add(new Student(name, age, major, year, group));
    }

    void printFMI() const
    {
        for (std::size_t i = 0; i < this->size; ++i)
        {
            this->fmi[i]->whoAmI();
            std::cout << "-------------------" << std::endl;
        }
    }
};

int main ()
{
    FMI fmi;

    fmi.addFMIPerson("Chicho Gosho", 50);
    fmi.addLecturer("Evgeniya Velikova", 50, "Algebra", 30);
    fmi.addAssistant("Deyan Djundrekov", 27, "Algebra", false);
    fmi.addStudent("Sonya Nikolova", 20, "KN", 2, 4);
    fmi.addStudent("Stanislav Popgeorgiev", 19, "KN", 1, 4);
    fmi.addAssistant("Peter Kolev", 20, "OOP-Practicum", true);
    fmi.addLecturer("Borislav Draganov", 40, "DIS", 20);
    fmi.addFMIPerson("Lelya Ginche", 62);

    fmi.printFMI();

    return 0;
}