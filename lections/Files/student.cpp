/******************************************************/
/* Примерен код към курса ООП, ФМИ (2024)
*  Пример за структури - структура студент            */
/******************************************************/

#include "student.h"
#include "helpers.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

// Декларации на помощни функции
static void readName(char*& name);
static Programme readProgramme();
static unsigned int readNumber(const char* name, unsigned max);
static bool readFlag(const char* name);
static const char* const programeToText(Programme prg);

void readStudent(Student& student)
{
    // Преди да четем нови данни - чистим старите
    clearStudentData(student);

    readName(student.name);
    readAddress(student.address);
    student.program = readProgramme();

    student.facNum = readNumber("faculty number", (1 << 17) - 1); // ограничение до макс. число в типа
    student.course = readNumber("course", 6);      // максимално 5-ти курс
    student.stream = readNumber("stream", 4);      // максимално 3-ти поток
    student.group = readNumber("group", 11);       // максимално 10-та група

    student.regular = readFlag("Is regular student?");
    student.interrupt = readFlag("Is the student interrupt?");
}

void printStudent(const Student& student)
{
    using std::cout;

    cout << "\n**************************************************************************\n";
    cout << "Information for student " << (student.name ? student.name : "") << "\n";
    cout << "Address: " << "\n";
    printAddress(student.address);
    cout << "Programme: " << programeToText(student.program) << "\n";
    cout << "FN: " << student.facNum << "\n";
    cout << "Course: " << student.course << "\n";
    cout << "Stream: " << student.stream << "\n";
    cout << "Group: " << student.group << "\n";
    cout << "The student is " << (student.regular ? "" : "not ") << "regular." << "\n";
    cout << "The student is " << (student.interrupt ? "" : "not ") << "interrupted." << "\n";
    cout << "**************************************************************************\n";
    cout.flush();
}

void clearStudentData(Student& student)
{
    delete[] student.name;
}

// Чете данни за името на студента. Грижи се за динамичната памет
static void readName(char*& name)
{
    char buffer[1024];

    std::cout << "Enter name for the student: ";
    do
        std::cin.getline(buffer, sizeof(buffer));
    while (!buffer[0]);

    if (!std::cin) {
        std::cin.clear();
        std::cin.sync();
    }

    name = new(std::nothrow) char[strlen(buffer) + 1];
    if (name) strcpy(name, buffer);
}


// Чете данни за специалност
static Programme readProgramme()
{
    using std::cin;

    Programme prg = Programme::UNKNOWN;
    std::cout << "Enter programme: ";

    cin >> (int&)prg;
    if (!cin)
        cin.clear();
    if (prg >= Programme::COUNT || prg < Programme::UNKNOWN) {
        std::cout << "Invalid value. The programme must be a number between " 
                  << (int)Programme::UNKNOWN << " and " << ((int)Programme::COUNT - 1) << std::endl;
    }
    return prg;
}

// Чете число без знак с ограничение. Подава се и помощен текст
static unsigned int readNumber(const char* name, unsigned max)
{
    using std::cin;
    unsigned val = max;

    do {
        std::cout << "Enter " << name << ": ";
        cin >> val;
        if (!cin) {
            cin.clear();
            cin.ignore();
        }
    } while (val >= max);

    cin.sync();
    return val;
}

// Чете булева стойност. Подава се подканващ въпрос.
static bool readFlag(const char* name)
{
    using std::cin;
    char ans;
    do {
        std::cout << name << "(y/n): ";
        cin >> ans;
    } while (ans != 'n' && ans != 'y' && ans != 'N' &&ans != 'Y');

    return ans == 'Y' || ans == 'y';
}

static const char* const programeToText(Programme prg)
{
    switch (prg)
    {
    case Programme::UNKNOWN:            return "Unknown program";
    case Programme::INFORMATICS:        return "Informatics";
    case Programme::COMPUTER_SCIENCSE:  return "Computer sciense";
    case Programme::MATH:               return "Math";
    case Programme::APPLIED_MATH:       return "Applied math (bow)";
    case Programme::STATICTICS:         return "Statistics";
    default:                            return "Bad programme value!";
    }

    // must never reach this line
    assert(false);
    return NULL;
}


/////////////////////////////
bool store(const Student& student, fstream& file)
{
    if (!file) return false;
    
    size_t len = strlen(student.name);
    file.write((char*)&len, sizeof(len));
    if (!file) return false;
    file.write(student.name, len);
    if (!file) return false;
    
    size_t size = sizeof(Student) - sizeof(void*);
    file.write((const char*)&student.address, size);
    return file.good();
}


bool load(Student& student, fstream& file)
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
            delete[] tmp.name;
            return false;
        }
    }
    tmp.name[size] = '\0';

    size_t offset = (size_t)&((Student*)nullptr)->address;
    assert(offset == sizeof(void*));

    file.read((char*)&tmp.address, sizeof(Student) - offset);
    if (file.good()) {
        delete[] student.name;
        student = tmp;
    }
    else {
        delete[] tmp.name;
    }
    return file.good();
}

