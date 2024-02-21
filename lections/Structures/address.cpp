/******************************************************/
/* Примерен код към курса ООП, ФМИ (2024)
*  Пример за структури - структура адрес              */
/******************************************************/


#include <iostream>
#include "address.h"

using std::cin;
using std::cout;
using std::endl;

void readAddress(Address& address)
{
    cout << "Enter city: ";
    cin.getline(address.city, 32);

    if (!cin) { // последното четене не е било успешно
        cin.clear();
        cin.sync();
    }

    cout << "Enter ZIP code: ";
    cin >> address.ZIP;
    while (!cin) {
        cin.clear();
        cin.sync();
        cout << "You must enter positiv number! \n Enter ZIP code again";
        cin >> address.ZIP;
    }

    // Тук потока е в добро състояние
    cout << "Enter street: ";
    skipSpaces();
    cin.getline(address.street, 64);

    // тук не е ясно какво е състоянието, но кода ще го възстанови.
    do {
        if (!cin) {
            cin.clear();
            cin.sync();
        }
        cout << "Enter number: ";
        cin >> address.number;
    } while (!cin);

    // накрая го остявяме отново в добро състояние и премахваме всичко останало
    cin.sync();
}

void printAddress(const Address& addr)
{
    cout << "City: " << addr.city << endl;
    cout << "ZIP code: " << addr.ZIP << endl;
    cout << "Street and number: " << addr.number << ", " << addr.street << endl;
}

void skipSpaces()
{
    while (isspace(cin.get()))
        ;
    cin.unget();
}
