#ifndef MENUITEM_H
#define MENUITEM_H

#include <iostream>
#include <string>
#include <string_view>

class MenuItem {
public:
	MenuItem(std::string_view name, const int quantity, std::string_view description, const double price);

	const double getPrice() const;

	virtual std::string getInfo() const;

	virtual MenuItem* clone() const;

protected:
	std::string m_name;
	int m_quantity;
	std::string m_description;
	double m_price;
};

#endif // !MENUITEM_H
