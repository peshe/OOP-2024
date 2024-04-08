#ifndef AUTO_SHOP_H
#define AUTO_SHOP_H

#include <cstddef>
#include <climits>
#include "Car.hpp"

class Dealership{

public:
    enum class SearchBy : uint8_t{

        BRAND,
        MAX_PRICE,
        CREATION_DATE

    };

    Dealership() = delete;
    Dealership(size_t const capacity);
    Dealership(Dealership const &other);
    Dealership(Dealership &&other) noexcept;
    ~Dealership() noexcept;

    Dealership &operator =(Dealership const &other);
    Dealership &operator =(Dealership &&other) noexcept;

    size_t Add(Car const &car, double const price);
    Car Sell(size_t const index);
    void SetPrice(size_t const index, double const price);

    void SaveData(const char *fileName) const;

    void PrintData(char const *brand) const;
    void PrintData(double const price) const;
    void PrintData(uint32_t const year) const;
    void PrintStatistics() const;

private:
    void copy(Dealership const &other);
    void move(Dealership &&other);
    void free();

    static double const INVALID_PRICE;

    struct Pair{
        Car car;
        double price = INVALID_PRICE;
    };

    Pair *cars = nullptr;
    size_t capacity = 1, totalSoldCars = 0;
    double totalEarnings = 0.f;

};

#endif