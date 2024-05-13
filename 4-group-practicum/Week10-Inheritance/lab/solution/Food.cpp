#include "Food.h"

Food::Food(std::string_view name, const int quantity, std::string_view description, const double price, const bool isBig, const bool isVegan)
		: MenuItem(name, quantity, description, price),
		  isBig(isBig), isVegan(isVegan) {
}

std::string Food::getInfo() const {
	std::string info = MenuItem::getInfo();

	info.replace(0, 9, "Food");

	const std::string size = isBig ? "Big" : "Small";
	const std::string vegan = isVegan ? "True" : "False";

	info += "Size: " + size + '\n';
	info += "Is vegan: " + vegan + '\n';

	return info;
}

MenuItem* Food::clone() const {
	return new Food(m_name, m_quantity, m_description, m_price, isBig, isVegan);
}
