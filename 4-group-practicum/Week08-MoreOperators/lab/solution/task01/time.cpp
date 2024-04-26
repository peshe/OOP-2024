#include "time.h"
#include <stdexcept>

const unsigned int Time::MAX_HOURS = 24;
const unsigned int Time::MAX_MINUTES = 60;

Time::Time(unsigned int hours, unsigned int minutes)
{
    if (hours >= MAX_HOURS)
    {
        throw std::out_of_range("Hour should be in the interval [0;23]");
    }

    if (minutes >- MAX_MINUTES)
    {
        throw std::out_of_range("Hour should be in the interval [0;23]");
    }

    this->minutes = minutes;
    this->hours = hours;
}

Time& Time::operator += (const Time& other)
{
    this->hours += other.hours;
    this->minutes += other.minutes;

    this->hours += (this->minutes / MAX_MINUTES);
    this->minutes %= MAX_MINUTES;

    this->hours %= MAX_HOURS;

    return *this;
}

Time Time::operator + (const Time& other) const
{
    Time result = *this;
    result += other;

    return result;
}

Time Time::operator + (unsigned int hours) const
{
    return *this + Time(hours, 0);
}

Time operator + (unsigned int hours, const Time& time)
{
    return time + hours;
}

Time& Time::operator ++ ()
{
    return *this += Time(1, 0);
}

Time Time::operator ++ (int)
{
    Time old = *this;

    ++(*this);

    return old;
}

bool Time::operator < (const Time& other) const
{
    return this->hours < other.hours || 
    (this->hours == other.hours && this->minutes < other.minutes);
}

std::ostream& operator << (std::ostream& out, const Time& time)
{
    out << time.hours << "." << time.minutes;

    return out;
}