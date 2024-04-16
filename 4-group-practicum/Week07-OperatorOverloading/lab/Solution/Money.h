#pragma once

#include "Currency.h"
#include "ConversionRate.h"


class Money {
public:
    Money(double startingMoney, Currency currency);

    double money() const;
    Currency currency() const;

    Money softConvert(const ConversionRate& conversionRate) const;
    void hardConvert(const ConversionRate& conversionRate);

    Money operator+(double money) const;
    Money operator+(const Money& money) const;
    Money operator-(double money) const;
    Money operator-(const Money& money) const;

    Money& operator+=(double money);
    Money& operator+=(const Money& money);
    Money& operator-=(double money);
    Money& operator-=(const Money& money);

    Money operator-() const;

    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;
    bool operator<(const Money& other) const;
    bool operator<=(const Money& other) const;
    bool operator>(const Money& other) const;
    bool operator>=(const Money& other) const;

private:
    double m_money{ 0 };
    Currency m_currency{ Currency::BGN };
};
