#pragma once

#include <cstddef>

#include "Date.h"
#include "Money.h"

constexpr std::size_t IDENTIFICATION_NUMBER_CAPACITY{ 10 };


class Client {
public:
    Client(const char* name, const char* identificationNumber, const Date& birthday, const Money& money);

    Client(const Client& other);
	Client& operator=(const Client& other);
    ~Client();

    const char* getName() const;
    const char* getIdentificationNumber() const;
    const Date& getBirthDay() const;
    const Money& getMoney() const;

    bool deposit(const Money& toDeposit);
    bool withdraw(const Money& toWithdraw);
    void convert(const ConvertionRate& convertionRate);

private:
    void copyDataFrom(const Client& other);
    void deleteData();

    void setName(const char* name);
    void setIdentificationNumber(const char* identificationNumber);

private:
    char* m_name{ nullptr };
    char m_identificationNumber[IDENTIFICATION_NUMBER_CAPACITY];
    Date m_birthDay{ 1, 1, 1 };
    Money m_money{};
};
