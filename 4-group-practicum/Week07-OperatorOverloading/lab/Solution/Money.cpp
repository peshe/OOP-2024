#include "Money.h"

#include <cassert>


Money::Money(double startingMoney, Currency currency)
    : m_money(startingMoney), m_currency(currency) {}

double Money::money() const {
    return m_money;
}

Currency Money::currency() const {
    return m_currency;
}

Money Money::softConvert(const ConversionRate& conversionRate) const {
	Money result = *this;
	result.hardConvert(conversionRate);
	return result;
}

void Money::hardConvert(const ConversionRate& conversionRate) {
    assert(m_currency == conversionRate.m_oldCurrency);

    m_money *= conversionRate.m_excangeRate;
    m_currency = conversionRate.m_newCurrency;
}

Money Money::operator+(double money) const {
    return Money(m_money + money, m_currency);
}

Money Money::operator+(const Money& money) const {
    assert(m_currency == money.m_currency);
    
    return Money(m_money + money.m_money, m_currency);
}

Money Money::operator-(double money) const {
    return (*this) + (-money);
}

Money Money::operator-(const Money& money) const {
    return (*this) + (-money);
}

Money& Money::operator+=(double money) {
    m_money += money;

    return *this;
}

Money& Money::operator+=(const Money& money) {
    assert(m_currency == money.m_currency);

    m_money += money.m_money;

    return *this;
}

Money& Money::operator-=(double money) {
    *this += -money;
    
    return (*this);
}

Money &Money::operator-=(const Money& money) {
    *this += -money;

    return (*this);
}

Money Money::operator-() const {
    return Money(-m_money, m_currency);
}

bool Money::operator==(const Money& other) const {
	assert(m_currency == money.m_currency);
    return m_money == other.m_money;
}

bool Money::operator!=(const Money& other) const {
    return !(*this == other);
}

bool Money::operator<(const Money& other) const {
	assert(m_currency == money.m_currency);
    return m_money < other.m_money;
}

bool Money::operator<=(const Money& other) const {
    return (*this < other) ||
           (*this == other);
}

bool Money::operator>(const Money& other) const {
    return other < *this;
}

bool Money::operator>=(const Money& other) const {
    return other <= *this;
}
