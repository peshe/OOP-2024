#pragma once

#include <iostream>

class Money
{
private:
    unsigned int levs;
    unsigned int stotinkas;

public:
    Money(const unsigned int levs, const unsigned int stotinkas);

    bool operator == (const Money& other) const;
    bool operator != (const Money& other) const;
    bool operator < (const Money& other) const;
    bool operator >= (const Money& other) const;

    Money& operator += (const Money& other);
    Money operator + (const Money& other) const;
    
    Money operator + (const unsigned int levs) const;

    Money& operator ++ ();
    Money operator ++ (int);

    friend std::istream& operator >> (std::istream& in,  Money& money);
    friend std::ostream& operator << (std::ostream& out, const Money& money);
};