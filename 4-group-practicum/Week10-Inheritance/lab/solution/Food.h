#ifndef FOOD_H
#define FOOD_H

#include "MenuItem.h"

class Food : public MenuItem {
public:
	Food(std::string_view name, const int quantity, std::string_view description, const double price, const bool isBig, const bool isVegan);

	std::string getInfo() const override;

	MenuItem* clone() const override;

private:
	bool isBig;
	bool isVegan;
};

#endif // !FOOD_H
