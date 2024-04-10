#include <utility>
#include <cstring>
#include <fstream>
#include <exception>
#include <iostream>
#include "Dealership.hpp"

double const Dealership::INVALID_PRICE = -1.0;

Dealership::Dealership(size_t const capacity){
    cars = new Pair[capacity];
    this -> capacity = capacity;
}

Dealership::Dealership(Dealership const &other){
    copy(other);
}

Dealership::Dealership(Dealership &&other) noexcept{
    move(std::move(other));
}

Dealership::~Dealership(){
    free();
}

Dealership &Dealership::operator =(Dealership const &other){

    if(this == &other) return *this;

    free();
    copy(other);

    return *this;

}

Dealership &Dealership::operator =(Dealership &&other) noexcept{

    if(this == &other) return *this;

    free();
    move(std::move(other));

    return *this;

}

size_t Dealership::Add(Car const &car, double const price){

    if(price < 0.0) throw std::invalid_argument("Price should not be negative");

    for(size_t i = 0; i < capacity; ++i)
        if(cars[i].price == INVALID_PRICE){

            cars[i] = Pair{car, price};
            return i;

        }

    return SIZE_MAX;

}

Car Dealership::Sell(size_t const index){

    if(index >= capacity) throw std::out_of_range("Index out of range");
    if(cars[index].price == INVALID_PRICE) throw std::domain_error("Parking spot is empty");

    ++totalSoldCars;
    totalEarnings += cars[index].price;
    cars[index].price = INVALID_PRICE;

    return cars[index].car;

}

void Dealership::SetPrice(size_t const index, double const price){

    if(index >= capacity) throw std::out_of_range("Index out of range");
    if(cars[index].price == INVALID_PRICE) throw std::domain_error("Parking spot is empty");
    if(price < 0.0) throw std::invalid_argument("Price should not be negative");

    cars[index].price = price;

}

void Dealership::SaveData(const char *fileName) const{

    std::ofstream ofs(fileName);

    if(!ofs.is_open()) throw std::ios_base::failure("Couldn't open file");

    for(size_t i = 0; i < capacity; ++i)
        if(cars[i].price != INVALID_PRICE)
            cars[i].car.Print(ofs);

    ofs.close();

}

void Dealership::PrintData(char const *brand) const{

    for(size_t i = 0; i < capacity; ++i)
        if(cars[i].price != INVALID_PRICE && !strcmp(cars[i].car.GetBrand(), brand))
            cars[i].car.Print(std::cout);

}

void Dealership::PrintData(double const price) const{

    for(size_t i = 0; i < capacity; ++i)
        if(cars[i].price != INVALID_PRICE && cars[i].price <= price)
            cars[i].car.Print(std::cout);

}

void Dealership::PrintData(uint32_t const year) const{

    for(size_t i = 0; i < capacity; ++i)
        if(cars[i].price != INVALID_PRICE && cars[i].car.GetDate().GetYear() > year)
            cars[i].car.Print(std::cout);

}

void Dealership::PrintStatistics() const{
    std::cout << "Total sold cars: " << totalSoldCars << " Total earnings: " << totalEarnings << '\n';
}

void Dealership::copy(Dealership const &other){

    cars = new Pair[other.capacity];
    for(size_t i = 0; i < other.capacity; ++i)
        cars[i] = other.cars[i];
    capacity = other.capacity;
    totalSoldCars = other.totalSoldCars;
    totalEarnings = other.totalEarnings;

}

void Dealership::move(Dealership &&other){

    capacity = other.capacity;
    cars = std::exchange(other.cars, nullptr);
    totalSoldCars = other.totalSoldCars;
    totalEarnings = other.totalEarnings;

}

void Dealership::free(){
    delete[] cars;
}