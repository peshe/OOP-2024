/******************************************************/
/* Примерен код към курса ООП, ФМИ (2024)
*  Пример за структури - структура представяща студент
* Съдържа: 
*   - изброен тип; 
*   - полета с динамично заделена памет;
*   - вложена структура;
*   - битови полета.
* Има функции за вход и изход                         */
/******************************************************/

#pragma once

#ifndef _STUDENT_HEADER_INCLUDED_
#define _STUDENT_HEADER_INCLUDED_

#include "address.h"

/* Избоен тип за специалност */
enum Programme
{
    PROGRAME_UNKNOWN,      // невалидна / неизвестна специалност
    INFORMATICS,           // информатика
    COMPUTER_SCIENCSE,     // компютърни науки
    MATH,                  // математика
    APPLIED_MATH,          // приложна математика
    STATICTICS,            // статистика

    PROGRAME_COUNT         // маркер за край на валидните стойности
};

/* Структура описваща студент */
struct Student
{
    char* name;                  // име - динамично заделен низ
    Address address;             // адрес - вложена структура
    Programme program;           // специалност - изброен тип
    // следват няколко атрибута разположени в битови полета
    unsigned int facNum    : 17; // факултетен номер
    unsigned int course    : 3;  // в кой курс е в момента
    unsigned int group     : 4;  // група
    unsigned int stream    : 2;  // поток
    unsigned int regular   : 1;  // редовно или задочно обучение
    unsigned int interrupt : 1;  // дали е прекъсвал
    unsigned int           : 4;  // подравняване
};

// Чете данните за студент от стандартния вход.
// Очаква валиден студент (т.е. с валиедн указател за име)
void readStudent(Student& student);

// Извежда данните за подаден студент на стандартния изход
void printStudent(const Student& student);

// Изичства паметта, заделена за студента.
void clearStudentData(Student& student);

#endif //_STUDENT_HEADER_INCLUDED_
