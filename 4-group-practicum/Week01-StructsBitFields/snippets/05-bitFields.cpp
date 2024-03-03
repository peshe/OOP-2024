#include <iostream>

struct Date
{
    unsigned int day: 5; // 2^5 --> 32
    unsigned int month: 4; // 2^4 --> 16
    unsigned int year: 11; // 2^11 --> 2048
};

struct FlagSet
{
    bool read: 1;
    bool write: 1;
    bool execute: 1;
};

int main ()
{
    std::cout << sizeof(Date) << std::endl;

    Date date{11, 6, 2001};

    std::cout << date.day << " " << date.month << " " << date.year << std::endl;

    Date wrongDate{35, 21, 3500};
    std::cout << wrongDate.day << " " << wrongDate.month << " " << wrongDate.year << std::endl;

    std::cout << sizeof(FlagSet) << std::endl;

    FlagSet flags{1, 0, 1};
    std::cout << flags.read << flags.write << flags.execute << std::endl;

    return 0;
}