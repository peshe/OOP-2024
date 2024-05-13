#include "MenuItem.h"

MenuItem::MenuItem(std::string_view name, const int quantity, std::string_view description, const double price)
			: m_name(name), m_quantity(quantity), m_description(description), m_price(price) {
}

const double MenuItem::getPrice() const {
	return m_price;
}

std::string MenuItem::getInfo() const {
	std::string info = "Menu Item:\n";

	info += "Name: " + m_name + '\n';
	info += "Quantity: " + std::to_string(m_quantity) + '\n';
	info += "Description: " + m_description + '\n';
	info += "Price: " + std::to_string(m_price) + '\n';

	return info;
}

MenuItem* MenuItem::clone() const {
	return new MenuItem(m_name, m_quantity, m_description, m_price);
}
