/******************************************************/
/* Примерен код към курса ООП, ФМИ (2024)             */
/* Първи примери за ООП.                              */
/* Класове, капсулация, жизнен цикъл. Добри практики. */
/******************************************************/

#pragma once

#ifndef _ADDRESS_HEADER_INCLUDED_
#define _ADDRESS_HEADER_INCLUDED_

#include <iostream>

namespace fmi::oop {     // requires C++17.

using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;

class Address
{
public:
    // Конструктори и деструктори
    // Подразбиращ се
    Address();
    // Параметричен
    Address(const char* city, const char* street, unsigned num, unsigned zip);
    // Копиращ - забележете използването на default - C++ 11
    Address(const Address& rhs) = default;

    //деструктор
    ~Address() = default;

    // Функции за достъп до полетата
    // град
    void setCity(const char* city);
    const char* getCity() const { return city; }

    // улица
    void setStreet(const char* street);
    const char* getStreet() const { return street; }

    // номер
    void setNumber(unsigned num);
    unsigned gedNumber() const { return number; }

    // пощенски код
    void setZip(unsigned zip);
    unsigned gedZip() const { return ZIP; }

    // Помощни функции (вход и изход)
    // Извежда подаден адрес на стандартния изход
    void print() const;
    // Чете данни за адрес от стандартния вход
    void read();

private:
    // Функции за четене / запис във файлове - текстови и двоични
    bool readFromStream(istream& input);
    bool readFromBinary(ifstream& input);
    bool printToStream(ostream& output) const;
    bool writeToBinary(ofstream& output) const;

private:
    char city[32];
    char street[64];
    unsigned short number;
    unsigned long ZIP;
};

} // fmi::oop

#endif //_ADDRESS_HEADER_INCLUDED_
