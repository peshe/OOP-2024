/******************************************************/
/* Примерен код към курса ООП, ФМИ (2024)             *
* Пример за структури - структура представяща адрес   *
* съставен от няколко статични полета.                *
* Функции за четене и извеждане на стандартния изход  *
* Също вход и изход от текстови и двоични файлове     */
/******************************************************/


#ifndef _ADDRESS_HEADER_INCLUDED_
#define _ADDRESS_HEADER_INCLUDED_

struct Address
{
    char city[32];
    char street[64];
    unsigned short number;
    unsigned long ZIP;
};

// Извежда подаден адрес на стандартния изход
void printAddress(const Address& address);

// Чете данни за адрес от стандартния вход
void readAddress(Address& address);

#include <iostream>
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;

// Функции за четене / запис във файлове - текстови и двоични
bool readAddressFromStream(Address& address, istream& input);
bool readFromBinary(Address& address, ifstream& input);
bool printAddressToStream(const Address& address, ostream& output);
bool writeToBinary(const Address& address, ofstream& output);


#endif //_ADDRESS_HEADER_INCLUDED_
