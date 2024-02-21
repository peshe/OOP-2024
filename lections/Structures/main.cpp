#include <iostream>
using std::cout;
using std::endl;

#include "address.h"
#include "student.h"

// Извежда всички студенти от дадена специалност.
// Получава масив от студенти сред които търси.
// Демонстрира работа със указатели към структури
void printAllFromProgramme(Programme prg, Student* students, int cnt)
{
    for (Student* iter = students; iter < students + cnt; ++iter) {
        if (iter->program == prg)
            printStudent(*iter);
    }
}

int main()
{
	//Address a;
	//readAddress(a);
	//printAddress(a);
    
    const int numStudents = 3;

	Student students[numStudents];
    for (int i = 0; i < numStudents; ++i) {
        students[i].name = nullptr;
        readStudent(students[i]);
    }

    for (int i = 0; i < numStudents; ++i) {
        printStudent(students[i]);
    }

    for (int i = (int)PROGRAME_UNKNOWN; i < (int)PROGRAME_COUNT; ++i) {
        cout << "\n\n";
        printAllFromProgramme((Programme)i, students, numStudents);
    }

    for (int i = 0; i < numStudents; ++i) {
        clearStudentData(students[i]);
    }

    return 0;
}
