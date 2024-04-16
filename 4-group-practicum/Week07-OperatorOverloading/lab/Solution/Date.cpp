#include "Date.h"

#include <cassert>


Date::Date(std::uint8_t day, std::uint8_t month, std::uint16_t year) {
    assert(day > 0 && day <= 31);
    assert(month > 0 && month <= 12);
    assert(year > 0);

    m_day = day;
    m_month = month;
    m_year = year;
}

std::uint8_t Date::day() const {
    return m_day;
}

std::uint8_t Date::month() const {
    return m_month;
}

std::uint16_t Date::year() const {
    return m_year;
}

bool Date::operator==(const Date& rhs) const {
    return m_year == rhs.m_year &&
           m_month == rhs.m_month &&
           m_day == rhs.m_day;
}

bool Date::operator<(const Date& rhs) const {
    return m_year < rhs.m_year ||
           m_year == rhs.m_year && m_month < rhs.m_month ||
           m_year == rhs.m_year && m_month == rhs.m_month && m_day < rhs.m_day;
}
