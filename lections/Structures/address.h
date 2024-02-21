/******************************************************/
/* Примерен код към курса ООП, ФМИ (2024)
* Пример за структури - структура представяща адрес
* съставен от няколко полета без динамични ресурси.
* Функции за четене и извеждане на стандартния изход  */
/******************************************************/

#pragma once

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

void skipSpaces();

#endif //_ADDRESS_HEADER_INCLUDED_
