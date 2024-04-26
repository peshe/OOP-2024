#pragma once

#include <fstream>

class Time
{
private:
    static const unsigned int MAX_HOURS;
    static const unsigned int MAX_MINUTES;

    unsigned int hours;
    unsigned int minutes;

public:
    Time(unsigned int hours, unsigned int minutes);

    Time& operator += (const Time& other);
    Time operator + (const Time& other) const;

    Time operator + (unsigned int hours) const;
    friend Time operator + (unsigned int hours, const Time& time);

    Time& operator ++ ();
    Time operator ++ (int);

    bool operator < (const Time& other) const;

    friend std::ostream& operator << (std::ostream& out, const Time& time);
};