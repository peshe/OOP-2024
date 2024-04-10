#ifndef DATE_H
#define DATE_H

#include <cstdint>
#include <ostream>

class Date{

public:
    Date() = default;
    Date(uint32_t year, uint32_t month, uint32_t day);
    Date(const char *formattedDate);

    void Print(std::ostream &os) const;
    bool Before(Date const other) const;

    uint32_t GetYear() const;
    uint32_t GetMonth() const;
    uint32_t GetDay() const;

    void SetDay(uint32_t day);
    void SetMonth(uint32_t month);
    void SetYear(uint32_t year);

private:
    // year - 6bits -> 63, month - 4bits -> 15, day - 5bits -> 31
    // Total: 15/16bits used.
    uint16_t time = 0;

    static uint16_t const DAYS_IN_MONTHS[12];

};

#endif