#include "Client.h"

#include <cstring>
#include <cassert>


Client::Client(const char* name, const char* identificationNumber, const Date& birthday, const Money& money)
: m_birthDay(birthday), m_money(money) {
    setIdentificationNumber(identificationNumber);
    setName(name);
}

Client::Client(const Client &other) {
    copyDataFrom(other);
}

Client& Client::operator=(const Client& other) {
    if (this != &other) {
        deleteData();
        copyDataFrom(other);
    }

    return *this;
}

Client::~Client() {
    deleteData();
}

const char* Client::getName() const {
    return m_name;
}

const char* Client::getIdentificationNumber() const {
    return m_identificationNumber;
}

const Date &Client::getBirthDay() const {
    return m_birthDay;
}

const Money& Client::getMoney() const {
    return m_money;
}

bool Client::deposit(const Money& toDeposit) {
    m_money += toDeposit;
    
    return true;
}

bool Client::withdraw(const Money& toWithdraw) {
    if (m_money < toWithdraw) {
        return false;
    }

    m_money -= toWithdraw;
    
    return true;
}

void Client::convert(const ConversionRate& conversionRate) {
    m_money.hardConvert(conversionRate);
}

void Client::copyDataFrom(const Client& other) {
    setName(other.m_name);
    setIdentificationNumber(other.m_identificationNumber);
    m_birthDay = other.m_birthDay;
    m_money = other.m_money;
}

void Client::deleteData() {
    delete[] m_name;
    m_name = nullptr;
}

void Client::setName(const char* name) {
    delete[] m_name;
    m_name = new (std::nothrow) char[strlen(name) + 1];

    if (!m_name) {
        std::cout << "Memory problem!" << std::endl;

        assert(false);
    }

    strcpy(m_name, name);
}

void Client::setIdentificationNumber(const char* identificationNumber) {
    strcpy(m_identificationNumber, identificationNumber);
}
