#include "Beer.h"
#include <cstring>
#include <iostream>

Beer::Beer() {
    volume = 0;
    strcpy(brand, "-");
}

Beer::Beer(const char *brand, const unsigned &volume) {
    strcpy(this->brand, brand);
    this->volume = volume;
}

const char* Beer::getBrand() const {
    return brand;
}

unsigned Beer::getVolume() const {
    return volume;
}

void Beer::add(Beer &other, unsigned int moveVolume) {
    if (other.volume < moveVolume) {
        // Not the best way to show the error
        // For the next part we will write exceptions
        std::cerr << "Not enough volume to be moved";
        return;
    }
    other.volume -= moveVolume;
    volume += moveVolume;
    strcat(brand, "&");
    strcat(brand, other.getBrand());
}

bool Beer::check(const char* checkBrand) {
    if (!checkBrand) return false;
    return strstr(brand, checkBrand);
}

void Beer::setBrand(const char* brand) {
    if(!brand) {
        std::cerr << "No brand"; // again not the best variant
        return;
    }
    // what about the case the new brand is longer?
    strcpy((this->brand), brand);
}

void Beer::setVolume(const unsigned& volume) {
    this->volume = volume;
}