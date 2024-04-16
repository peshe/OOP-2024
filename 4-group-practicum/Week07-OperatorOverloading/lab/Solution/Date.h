#pragma once

#include <cstdint>


class Date {
public:
    Date(std::uint8_t day, std::uint8_t month, std::uint16_t year);

    std::uint8_t day() const;
    std::uint8_t month() const;
    std::uint16_t year() const;

    bool operator==(const Date& rhs) const;
    bool operator<(const Date& rhs) const;

private:
    std::uint8_t m_day{ 0 };
    std::uint8_t m_month{ 0 };
    std::uint16_t m_year{ 0 };
};
