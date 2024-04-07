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

private:
    // year - 6bits -> 63, month - 4bits -> 15, day - 5bits -> 31
    // Total: 15/16bits used.
    uint16_t time = 0;

};

#endif