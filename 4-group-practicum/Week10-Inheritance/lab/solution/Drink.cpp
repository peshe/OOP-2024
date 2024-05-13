#include "Drink.h"

Drink::Drink(std::string_view name, const int quantity, std::string_view description, const double price, const ServingType servingType)
		: MenuItem(name, quantity, description, price), m_servingType(servingType) {
}

std::string Drink::getInfo() const {
	std::string info = MenuItem::getInfo();
	
	info.replace(0, 9, "Drink");

	const std::string servingType = m_servingType == ServingType::GLASS ? "Glass" : (m_servingType == ServingType::JUG ? "Jug" : "Bottle");

	info += "Serving type: " + servingType + '\n';

	return info;
}

MenuItem* Drink::clone() const {
	return new Drink(m_name, m_quantity, m_description, m_price, m_servingType);
}
