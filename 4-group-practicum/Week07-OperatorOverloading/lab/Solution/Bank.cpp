#include "Bank.h"

#include <cstring>
#include <cassert>


Bank::Bank(const char* name, const ConversionRate rates[CONVERSION_RATES_SIZE]) {
    allocateClientsMemory(INITIAL_CLIENTS_CAPACITY);

    setName(name);
    setConversionRates(rates);
}

Bank::Bank(const Bank& other) {
    copyDataFrom(other);
}

Bank& Bank::operator=(const Bank& other) {
    if (this != &other) {
        deleteData();
        copyDataFrom(other);
    }
    
    return *this;
}

Bank::~Bank() {
    deleteData();
}

void Bank::addClient(const Client& client) {
    if (nClientsSize >= nClientsCapacity) allocateClientsMemory(nClientsCapacity * CLIENTS_CAPACITY_MULTIPLIER);

    m_clients[nClientsSize++] = new Client(client);
}

bool Bank::removeClient(const char* identificationNumber) {
	int clientIndex{ getClientIndex(identificationNumber) };

    if (clientIndex == -1) {
        return false;
    }

	delete m_clients[clientIndex];
	m_clients[clientIndex] = m_clients[nClientsSize - 1];
	m_clients[--nClientsSize] = nullptr;

	return true;	
}

int Bank::getClientIndex(const char* identificationNumber) const {
    for (std::size_t index{ 0 }; index < nClientsSize; ++index) {
        if (strcmp(m_clients[index]->getIdentificationNumber(), identificationNumber) == 0) {
            return index;
        }
    }
    
    return -1;
}

bool Bank::deposit(const char* identificationNumber, const Money& toDeposit) {
    int clientIndex{ getClientIndex(identificationNumber) };

    if (clientIndex == -1) {
        return false;
    }

    return m_clients[clientIndex]->deposit(toDeposit);
}

bool Bank::withdraw(const char* identificationNumber, const Money& toWithdraw) {
    int clientIndex{ getClientIndex(identificationNumber) };

    if (clientIndex == -1) {
        return false;
    }

    return m_clients[clientIndex]->withdraw(toWithdraw);
}

bool Bank::transfer(const char* sourceClientIdentificationNumber, const char* destinationClientIdentifinationNumber, Money moneyToTransfer) {
    int sourceIndex{ getClientIndex(sourceClientIdentificationNumber) };

    if (sourceIndex == -1) {
        return false;
    }

    int destinationIndex{ getClientIndex(destinationClientIdentifinationNumber) };

    if (destinationIndex == -1) {
        return false;
    }

    Client* source{ m_clients[sourceIndex] };
    Client* destination{ m_clients[destinationIndex] };

    if (moneyToTransfer.currency() != source->getMoney().currency()) {
		const ConversionRate* conversionRate = findConversionRate(moneyToTransfer.currency(), source->getMoney().currency());
		
		if (conversionRate == nullptr) {
			return false;
		}
		
        moneyToTransfer.hardConvert(*conversionRate);
    }

    if (source->getMoney() < moneyToTransfer) {
        return false;
    }

    source->withdraw(moneyToTransfer);

    if (moneyToTransfer.currency() != destination->getMoney().currency()) {
		const ConversionRate* conversionRate = findConversionRate(moneyToTransfer.currency(), destination->getMoney().currency());
		
		if (conversionRate == nullptr) {
			return false;
		}
	
        moneyToTransfer.hardConvert(*conversionRate);
    }

    destination->deposit(moneyToTransfer);
    
    return true;
}

bool Bank::convertClientMoney(const char* identificationNumber, Currency newCurrency) {
    int clientIndex{ getClientIndex(identificationNumber) };

    if (clientIndex == -1) {
        return false;
    }

	const ConversionRate* conversionRate = findConversionRate(m_clients[clientIndex]->getMoney().currency(), newCurrency);

	if (conversionRate == nullptr) {
		return false;
	}

    m_clients[clientIndex]->convert(*conversionRate);
    
    return true;
}

void Bank::allocateClientsMemory(std::size_t newCapacity) {
    if (newCapacity <= nClientsCapacity) newCapacity = nClientsCapacity + 1;

    Client** blockOfMem = new Client*[newCapacity];

    for (std::size_t index{ 0 }; index < nClientsSize; ++index) {
        blockOfMem[index] = new Client(*m_clients[index]);
    }

    deleteClients();

    m_clients = blockOfMem;
    nClientsCapacity = newCapacity;
}

void Bank::copyDataFrom(const Bank& other) {
    setConversionRates(other.m_conversionRates);
    setName(other.m_name);

    m_clients = new (std::nothrow) Client*[other.nClientsCapacity];

    for (std::size_t index{ 0 }; index < other.nClientsSize; ++index) {
        m_clients[index] = new (std::nothrow) Client(*other.m_clients[index]);
    }

    nClientsCapacity = other.nClientsCapacity;
    nClientsSize = other.nClientsSize;
}

void Bank::deleteClients() {
    for (std::size_t index{ 0 }; index < nClientsSize; ++index) {
        delete m_clients[index];
        m_clients[index] = nullptr;
    }

    delete[] m_clients;
    m_clients = nullptr;
}

void Bank::deleteData()
{
    delete[] m_name;
    m_name = nullptr;

    deleteClients();
}

void Bank::setName(const char* name) {
    delete[] m_name;

    m_name = new (std::nothrow) char[strlen(name) + 1];

    if (!m_name) {
        std::cout << "Memory problem!" << std::endl;

        assert(false);
    }

    strcpy(m_name, name);
}

void Bank::setConversionRates(const ConversionRate conversionRates[CONVERSION_RATES_SIZE]) {
    for (std::size_t index{ 0 }; index < CONVERSION_RATES_SIZE; ++index) {
        m_conversionRates[index] = conversionRates[index];
    }
}

const ConversionRate* Bank::findConversionRate(Currency oldCurrency, Currency newCurrency) const {
	for (std::size_t index{ 0 }; index < CONVERSION_RATES_SIZE; ++index) {
		if (m_conversionRates[index].m_oldCurrency == oldCurrency && m_conversionRates[index].m_newCurrency == newCurrency) {
			return m_conversionRates + index;
		}
	}

	return nullptr;
}
