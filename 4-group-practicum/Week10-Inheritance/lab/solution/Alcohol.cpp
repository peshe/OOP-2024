#include "Alcohol.h"

Alcohol::Alcohol(std::string_view name, const int quantity, std::string_view description, const double price, const ServingType servingType, const double alcoholPercentage)
			: Drink(name, quantity, description, price, servingType), m_alcoholPercentage(alcoholPercentage) {
}

const double Alcohol::getAlcoholPercentage() const {
	return m_alcoholPercentage;
}

std::string Alcohol::getInfo() const {
	std::string info = Drink::getInfo();

	info.replace(0, 5, "Alcohol");

	info += "Alcohol Percentage: " + std::to_string(m_alcoholPercentage) + '\n';

	return info;
}

MenuItem* Alcohol::clone() const {
	return new Alcohol(m_name, m_quantity, m_description, m_price, m_servingType, m_alcoholPercentage);
}
