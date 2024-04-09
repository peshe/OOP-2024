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
    if(!horsePower || horsePower > 3000) throw std::ios_base::failure("Value read from the stream was invalid");
    is >> seats;
    if(!seats || seats > 12) throw std::ios_base::failure("Value read from the stream was invalid");
    if(is.fail() || is.bad()) throw std::ios_base::failure("Error while reading values from the stream");
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

    *this = Car(other);

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

void Car::SetBrand(char const *brand){

    if(!brand) return;

    char *temp = new char[strlen(brand) + 1];

    delete[] this -> brand;
    this -> brand = temp;
    strcpy(this -> brand, brand);

}

void Car::SetDate(char const *date){
    this -> date = Date(date);
}

void Car::SetDate(Date date){
    this -> date = date;
}

void Car::SetHorsePower(uint16_t horsePower){

    if(!horsePower || horsePower > 3000) throw std::invalid_argument("Invalid value");
    totalHorsePower -= this -> horsePower - horsePower;
    this -> horsePower = horsePower;

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
    horsePower = other.horsePower;
    seats = other.seats;
    totalHorsePower += other.horsePower;

}

void Car::free(){

    totalHorsePower -= horsePower;
    delete[] brand;

}