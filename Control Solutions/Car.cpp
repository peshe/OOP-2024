#include <cstring>
#include <utility>
#include "Car.hpp"

uint64_t Car::totalHorsePower = 0;

Date ReadDate(std::istream &is){

    size_t const BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    is >> buffer;

    return Date(buffer);

}

Car::Trunk ReadTrunkType(std::istream &is){

    if(is.bad() || is.fail()) throw std::ios_base::failure("Input stream error");

    size_t const BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    is >> buffer;

    if(!strcmp(buffer, "Sedan")) return Car::Trunk::SEDAN;
    else if(!strcmp(buffer, "Kombi")) return Car::Trunk::KOMBI;
    else if(!strcmp(buffer, "Hatchback")) return Car::Trunk::HATCHBACK;

    return Car::Trunk::SEDAN;

}

Car::Car(std::istream &is): trunkType(ReadTrunkType(is)), date(ReadDate(is)){

    
    size_t const BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    is >> buffer;

    brand = new char[strlen(buffer) + 1];
    strcpy(brand, buffer);

    is >> horsePower;
    is >> seats;
    totalHorsePower += horsePower;

}

Car::Car(Car const &other): trunkType(other.trunkType){
    copy(other);
}

Car::Car(Car &&other) noexcept : trunkType(other.trunkType){
    move(std::move(other));
}

Car::~Car(){
    free();
}

Car &Car::operator =(Car const &other){

    if(this == &other) return *this;

    free();
    copy(other);

    return *this;

}

Car &Car::operator =(Car &&other) noexcept{

    if(this == &other) return *this;

    free();
    move(std::move(other));

    return *this;

}

void Car::Print(std::ostream &os) const{

    switch (trunkType){

        case Trunk::SEDAN:
            os << "Sedan ";
            break;
        case Trunk::KOMBI:
            os << "Kombi ";
            break;
        case Trunk::HATCHBACK:
            os << "Hatch back ";
            break;

    }

    date.Print(os);

    os << ' ' << brand << ' ' << horsePower << ' ' << seats << '\n';

}

char const *Car::GetBrand() const{
    return brand;
}

Date Car::GetDate() const{
    return date;
}

uint64_t Car::GetTotalHorsePower(){
    return totalHorsePower;
}

void Car::copy(Car const &other){

    brand = new char[strlen(other.brand) + 1];
    strcpy(brand, other.brand);
    date = other.date;
    horsePower = other.horsePower;
    seats = other.seats;
    totalHorsePower += other.horsePower;

}

void Car::move(Car &&other){

    brand = std::exchange(other.brand, nullptr);
    date = std::exchange(other.date, Date());
    horsePower = std::exchange(other.horsePower, 0);
    seats = std::exchange(other.seats, 0);
    totalHorsePower += other.horsePower;

}

void Car::free(){

    totalHorsePower -= horsePower;
    delete[] brand;

}