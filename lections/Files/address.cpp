/******************************************************/
/* Примерен код към курса ООП, ФМИ (2024)
*  Пример за структури - структура адрес              */
/******************************************************/


#include <iostream>
#include <fstream>
#include <cassert>
#include <limits>

#include "address.h"
#include "helpers.h"

void readAddress(Address& address)
{
    using std::cin;
    using std::cout;

    cout << "Enter city: ";
    cin.getline(address.city, sizeof(address.city));

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
    std::cout << "City: " << addr.city << "\n";
    std::cout << "ZIP code: " << addr.ZIP << "\n";
    std::cout << "Street and number: " << addr.number << ", " << addr.street << std::endl;
}


//////////////////////////////////////
bool readAddressFromStream(Address& address, istream& input)
{
    Address addr;
    constexpr std::streamsize max_size = std::numeric_limits<std::streamsize>::max();

    input.getline(addr.city, sizeof(addr.city), ',');
    input >> addr.ZIP;
    if (!input) {
        std::cerr << "Problem reading ZIP.\n";
        input.clear();
    }
    input.ignore(max_size, ','); // Има и по-добър начин, но е малко по-засукан...

    input >> addr.number;
    if (!input) {
        std::cerr << "Problem reading street number.\n";
        input.clear();
    }
    input.ignore(max_size, '"');
    
    input.getline(addr.street, sizeof(addr.street), '"');

    if (!input) {
        std::cerr << "Problem reading the address!\n";
        return false;
    }
    else {
        address = addr;
        return true;
    }
}


bool readFromBinary(Address& address, ifstream& input)
{
    Address addr;
    assert(input.good());
    input.read((char*)&addr, sizeof(addr));
    bool result = input.good() && input.gcount() == sizeof(addr);
    if (result) address = addr;
    return result;
}


bool printAddressToStream(const Address& address, ostream& output)
{
    assert(output.good());
    output << address.city << ','
           << address.ZIP << ','
           << address.number << ','
           << '"' << address.street << '"'
           << std::endl;
    return output.good();
}


bool writeToBinary(const Address& address, ofstream& output)
{
    assert(output.good());
    output.write((char*)&address, sizeof(address));
    return output.good();
}
