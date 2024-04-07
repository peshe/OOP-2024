#include "Date.hpp"
#include <exception>

const uint32_t DAY_BITS = 5;
const uint32_t MONTH_BITS = 4;
const uint32_t YEAR_BITS = 6;
const uint32_t YEAR_OFFSET = DAY_BITS + MONTH_BITS;
const uint32_t MONTH_OFFSET = DAY_BITS;

bool IsDigit(char const ch){
    return '0' <= ch && ch <= '9';
}

Date::Date(uint32_t year, uint32_t month, uint32_t day){

    if(year < 1970 || year > 2024) throw std::invalid_argument("Year is invalid");
    if(!month || month > 12) throw std::invalid_argument("Month is invalid");
    if(!day || day > 31) throw std::invalid_argument("Day is invalid");

    year -= 1970;
    time = year << YEAR_OFFSET | month << MONTH_OFFSET | day;

}

Date::Date(const char *formattedDate){

    uint32_t day = 0, month = 0, year = 0;
    size_t i = 0;

    for(; formattedDate[i] != '/'; ++i){

        if(formattedDate[i] == '\0' || !IsDigit(formattedDate[i])) throw std::invalid_argument("Invalidly formated date");
        day *= 10;
        day += formattedDate[i] - '0';

    }

    ++i;

    for(; formattedDate[i] != '/'; ++i){

        if(formattedDate[i] == '\0' || !IsDigit(formattedDate[i])) throw std::invalid_argument("Invalidly formated date");
        month *= 10;
        month += formattedDate[i] - '0';

    }

    ++i;

    for(; formattedDate[i] != '\0'; ++i){

        if(!IsDigit(formattedDate[i])) throw std::invalid_argument("Invalidly formated date");
        year *= 10;
        year += formattedDate[i] - '0';

    }

    if(year < 1970 || year > 2024) throw std::invalid_argument("Year is invalid");
    if(!month || month > 12) throw std::invalid_argument("Month is invalid");
    if(!day || day > 31) throw std::invalid_argument("Day is invalid");

    year -= 1970;
    time = year << YEAR_OFFSET | month << MONTH_OFFSET | day;

}

void Date::Print(std::ostream &os) const{

    const uint16_t day = GetDay();
    const uint16_t month = GetMonth();
    const uint16_t year = GetYear();

    if(day < 10) os << '0';
    os << day << '/';
    if(month < 10) os << '0';
    os << month << '/' << year;

}

bool Date::Before(Date const other) const{
    return time < other.time;
}

uint32_t Date::GetYear() const{
    return ((time >> YEAR_OFFSET) & ((1 << YEAR_BITS) - 1)) + 1970;
}

uint32_t Date::GetMonth() const{
    return ((time >> MONTH_OFFSET) & ((1 << MONTH_BITS) - 1));
}

uint32_t Date::GetDay() const{
    return (time & ((1 << DAY_BITS) - 1));
}