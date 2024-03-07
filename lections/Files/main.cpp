#include <iostream>
#include <fstream>
using namespace std;

#include "address.h"
#include "student.h"

void generateStudentFile()
{
    const int numStudents = 5;
    Student students[numStudents];

    for (int i = 0; i < numStudents; ++i) {
        students[i].name = nullptr;
        readStudent(students[i]);
    }

    fstream file("students.dat", ios::out | ios::binary | ios::trunc);
    if (!file) {
        cerr << "Problem with the file...";
    }
    else {
        for (int i = 0; i < numStudents; ++i) {
            if (!store(students[i], file))
                break;
        }
    }

    for (int i = 0; i < numStudents; ++i) {
        clearStudentData(students[i]);
    }
}

void printStudentsFromFile()
{
    Student s{};
    fstream file("students.dat", ios::in | ios::binary);

    while (load(s, file))
        printStudent(s);
    clearStudentData(s);
}

void toUpper(char* text)
{
    while (*text) {
        if (*text >= 'a' && *text <= 'z') {
            *text = *text - 'a' + 'A';
        }
        ++text;
    }
}

void changeNameOfAllInf()
{
    Student s;
    s.name = nullptr;
    fstream file("students.dat", ios::in | ios::out | ios::binary);
    
    if (!file) return;
    streampos begin = 0;
    while (load(s, file)) {
        if (s.program == Programme::INFORMATICS) {
            toUpper(s.name);
            streampos end = file.tellg();
            file.seekp(begin, ios::beg);
            store(s, file);
            file.seekg(end, ios::beg);
        }
        begin = file.tellg();
    }
    clearStudentData(s);
    file.close();
}

int main()
{
//    generateStudentFile();
//    printStudentsFromFile();
//    changeNameOfAllInf();
//    printStudentsFromFile();
  return 0;
}
