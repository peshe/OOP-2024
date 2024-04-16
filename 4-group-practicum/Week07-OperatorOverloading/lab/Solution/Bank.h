#pragma once

#include "Client.h"


constexpr std::size_t CONVERSION_RATES_SIZE{ 6 };
constexpr std::size_t INITIAL_CLIENTS_CAPACITY{ 4 };
constexpr std::size_t CLIENTS_CAPACITY_MULTIPLIER{ 2 };

class Bank {
public:
    Bank(const char* name, const ConversionRate rates[CONVERSION_RATES_SIZE]);

    Bank(const Bank& other);
	Bank& operator=(const Bank& other);
    ~Bank();

    void addClient(const Client& client);
	bool removeClient(const char* identificationNumber);
    int getClientIndex(const char* identificationNumber) const;

    bool deposit(const char* identificationNumber, const Money& toDeposit);
    bool withdraw(const char* identificationNumber, const Money& toWithdraw);
    bool transfer(const char* sourceClientIdentificationNumber, const char* destinationClientIdentifinationNumber, Money moneyToTransfer);
    bool convertClientMoney(const char* identificationNumber, Currency newCurrency);

private:
    void allocateClientsMemory(std::size_t newCapacity);

    void copyDataFrom(const Bank& other);
    
    void deleteClients();
    void deleteData();

    void setName(const char* name);
    void setConversionRates(const ConversionRate conversionRates[CONVERSION_RATES_SIZE]);

    const ConversionRate* findConversionRate(Currency oldCurrency, Currency newCurrency) const;

private:
    char* m_name{ nullptr };
    
    Client** m_clients{ nullptr };
    std::size_t nClientsSize{ 0 };
    std::size_t nClientsCapacity{ 0 };

    ConversionRate m_conversionRates[CONVERSION_RATES_SIZE];
};
