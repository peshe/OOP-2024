/******************************************************/
/* Примерен код към курса ООП, ФМИ (2024)
/******************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

#include "student.h"

using namespace std;

namespace fmi::oop { //Requires C++ 17

namespace _helpers
{
    // Декларации на помощни функции
    static void readName(char*& name);
    static Subject readSubject();
    static unsigned int readNumber(const char* name, unsigned max);
    static bool readFlag(const char* name);
    static const char* const subjectToText(Subject prg);
}


Student::Student() 
    : name(nullptr)
//  , address()
    , subject(Subject::UNKNOWN)
    , facNum(0)
    , course(1)
    , group(1)
    , stream(1)
    , status(0)
{
#ifdef _DEBUG
    cout << " >>>>>> Called default ctor for Student \n";
#endif
}


Student::Student(const Student& rhs)
    : name(nullptr)
    , address(rhs.address)
    , subject(rhs.subject)
    , facNum(rhs.facNum)
    , course(rhs.course)
    , group(rhs.group)
    , stream(rhs.stream)
    , status(rhs.status)
{
    setName(rhs.getName());

#ifdef _DEBUG
    cout << " >>>>>> Called copy ctor for Student \n";
#endif
}


Student::Student(const char* name, const Address& address,
    Subject prg, unsigned fn, unsigned grp, bool regular)
    : name(nullptr)
    , address(address)
    , status(regular ? RegularFlag : 0)
    , course(1)
{
    setGroup(grp);
    setName(name);
    setSubject(prg);
    if (checkFN(fn)) {
        setFN(fn);
    }
    else {    // при невалидни данни в конструктора
        clearData();                // зачистваме каквото сме заделили
        throw "Bad fac num!";       // и хвърляме изключение
    }

#ifdef _DEBUG
    cout << " >>>>>> Called argument ctor for Student \n";
#endif
}


Student::~Student()
{
    clearData();

#ifdef _DEBUG
    cout << " <<<<<< Called dtor for Student \n";
#endif
}


bool Student::isRegular() const
{
    return status & RegularFlag;
}


bool Student::isInterrupted() const
{
    return 0 != (status & InterruptFlag);
}


void Student::setName(const char* name)
{
    if (nullptr == name) {
        throw "Invalid name! Students must have name!";
    }

    delete[] this->name;
    this->name = strcpy(new char[strlen(name) + 1], name);
}


void Student::setAddress(const Address& addres)
{
    this->address = address;
}


void Student::setFN(unsigned fn)
{
    if (!checkFN(fn)) {
        throw "This FN is invalid for students Subject!";
    }
    facNum = fn;
}


void Student::setGroup(unsigned group)
{
    this->group = group;
    stream = (group <= 5) ? 1 : 2;
}


void Student::setInterrupted(bool interrupt)
{
    if (interrupt) {
        status |= InterruptFlag;
    }
    else {
        status &= ~InterruptFlag;
    }
}


void Student::goToNextCourse()
{
    if (course < 5) ++course;
}


void Student::print() const
{
    using namespace _helpers;

    cout << "\n**************************************************************************\n";
    cout << "Information for student " << getName() << endl;
    cout << "Address: " << endl;
    getAddress().print();
    cout << "Subject: " << subjectToText(getSubject()) << endl;
    cout << "FN: " << getFN() << endl;
    cout << "Course: " << getCourse() << endl;
    cout << "Stream: " << getStream() << endl;
    cout << "Group: " << getGroup() << endl;
    cout << "The student is " << (isRegular() ? "" : "not ") << "regular." << endl;
    cout << "The student is " << (isInterrupted() ? "" : "not ") << "interrupted." << endl;
    cout << "**************************************************************************\n";
}


bool Student::store(fstream& file) const
{
    if (!file) return false;
    
    size_t len = strlen(getName());
    file.write((char*)&len, sizeof(len));
    if (!file) return false;
    file.write(getName(), len);
    if (!file) return false;
    
    size_t size = sizeof(Student) - sizeof(void*);
    file.write((char*)&address, size);
    return file.good();
}


bool Student::load(fstream& file)
{
    if (!file) return false;
    size_t size;
    file.read((char*)&size, sizeof(size));
    if (!file) return false;

    Student tmp{};
    if (!(tmp.name = new(std::nothrow) char[size + 1]))
        return false;

    std::streamsize readBytes = 0;
    while (readBytes < size) {
        file.read(tmp.name + readBytes, size - readBytes);
        std::streamsize read = file.gcount();
        readBytes += read;
        if (!file || read == 0) {
            return false;
        }
    }
    tmp.name[size] = '\0';

    size_t offset = (size_t)&((Student*)nullptr)->address;
    assert(offset == sizeof(void*));

    file.read((char*)&tmp.address, sizeof(Student) - offset);
    if (file.good()) {      // Така не е добре, но следващият път.
        *this = tmp;
        tmp.name = nullptr;
    }
    return file.good();
}


void Student::clearData()
{
    delete[] name;
}


bool Student::checkFN(unsigned fn)
{
    assert(subject < Subject::COUNT);

    switch (subject) {
    case Subject::UNKNOWN:               return true;
    case Subject::INFORMATICS:           return 4 == fn / 10000;
    case Subject::COMPUTER_SCIENCSE:     return 8 == fn / 10000;
    case Subject::MATH:                  return 1 == fn / 10000;
    case Subject::APPLIED_MATH:          return 3 == fn / 10000;
    case Subject::STATICTICS:            return 0 == fn / 10000;
    default: return false;
    }
}


namespace _helpers
{
    // Чете данни за името на студента. Грижи се за динамичната памет
    static void readName(char*& name)
    {
    
        char buffer[1024];

        cout << "Enter name for the student: ";
        do
            std::cin.getline(buffer, sizeof(buffer));
        while (!buffer[0]);

        if (!cin) {
            cin.clear();
            cin.sync();
        }

        name = new char[strlen(buffer) + 1];
        strcpy(name, buffer);
    }


    // Чете данни за специалност
    static Subject readSubject()
    {
        Subject prg = Subject::UNKNOWN;
        cout << "Enter Subject: ";

        cin >> (int&)prg;
        if (!cin) {
            cin.clear();
        }
        if (prg >= Subject::COUNT || prg < Subject::UNKNOWN) {
            cout << "Invalid value. The Subject must be a number between " << (int)Subject::UNKNOWN
                << " and " << ((int)Subject::COUNT - 1) << endl;
        }
        return prg;
    }


    // Чете число без знак с ограничение. Подава се и помощен текст
    static unsigned int readNumber(const char* name, unsigned max)
    {
        unsigned val = max;

        do {
            cout << "Enter " << name << ": ";
            cin >> val;
            if (!cin) {
                cin.clear();
                cin.ignore();
            }
        } while (val >= max);

        cin.sync();         // Премахваме остатъците в потока
        return val;
    }


    // Чете булева стойност. Подава се подканващ въпрос.
    static bool readFlag(const char* name)
    {
        char ans;
        do {
            cout << name << "(y/n): ";
            cin >> ans;
        } while (ans != 'n' && ans != 'y' && ans != 'N' &&ans != 'Y');
        cin.sync();
        return ans == 'y' || ans == 'Y';
    }


    static const char* const subjectToText(Subject prg)
    {
        switch (prg) {
        case Subject::UNKNOWN:            return "Unknown subject";
        case Subject::INFORMATICS:        return "Informatics";
        case Subject::COMPUTER_SCIENCSE:  return "Computer sciense";
        case Subject::MATH:               return "Math";
        case Subject::APPLIED_MATH:       return "Applied math (bow)";
        case Subject::STATICTICS:         return "Statistics";
        default:                          return "Bad Subject value!";
        }

        // must never reach this line
        assert(false);
        return nullptr;
    }

} // _helpers

} // oop::fmi
