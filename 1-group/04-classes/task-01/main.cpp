#include <iostream>
#include "Beer.h"

int main() {

    Beer first("Heineken", 500);
    Beer second("Zagorka", 750);
    Beer third("Becks", 750);
    Beer foo;
    first.add(second, 350);
    std::cout << first.getBrand() << " " << first.getVolume() << std::endl;
    std::cout << second.getBrand() << " " << second.getVolume() << std::endl;
    std::cout << third.check(second.getBrand()) << std::endl;
    std::cout << first.check(second.getBrand()) << std::endl;
    std::cout << foo.getBrand() << " " << foo.getVolume() << std::endl;
    foo.setBrand("Ariana");
    foo.setVolume(330);
    std::cout << foo.getBrand() << " " << foo.getVolume() << std::endl;
}
