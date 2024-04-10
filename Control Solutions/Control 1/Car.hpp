#ifndef CAR_H
#define CAR_H

#include <istream>
#include "Date.hpp"

class Car{

public:
    enum class Trunk : uint16_t{
        SEDAN,
        KOMBI,
        HATCHBACK
    };

    Car() = default;
    Car(std::istream &is);
    Car(Car const &other);
    Car(Car &&other) noexcept;
    ~Car() noexcept;

    Car &operator =(Car const &other);
    Car &operator =(Car &&other) noexcept;

    void Print(std::ostream &os) const;
    char const *GetBrand() const;
    Date GetDate() const;

    void SetBrand(char const *brand);
    void SetDate(char const *date);
    void SetDate(Date date);
    void SetHorsePower(uint16_t horsePower);

    static uint64_t GetTotalHorsePower();

private:
    void copy(Car const &other);
    void move(Car &&other);
    void free();

    Trunk const trunkType = Trunk::SEDAN;
    uint16_t horsePower = 0, seats = 0;
    Date date;
    char *brand = nullptr;

    static uint64_t totalHorsePower;

};

#endif