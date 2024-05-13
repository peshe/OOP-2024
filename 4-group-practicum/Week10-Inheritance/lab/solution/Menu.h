#ifndef MENU_H
#define MENU_H

#include <iostream>

#include "MenuItem.h"
#include "Food.h"
#include "Alcohol.h"
#include "Drink.h"

class Menu {
public:
	static Menu& getInstance();

	~Menu();

	void addItem(std::string_view type);

	void printCheapestMenuItem() const;

	unsigned getNumberOfAlcoholFreeDrinks() const;

	void getDrinkWithTheHighestAlcoholPercentage() const;

	void print() const;

private:
	Menu();
	Menu(const Menu& menu) = delete;

	Menu& operator=(const Menu& other) = delete;

private:
	MenuItem** m_data;
	size_t m_size;
	size_t m_capacity;

	void deleteData();
	void allocMem(size_t newCapacity);

	bool empty() const;

	void addItemToMenu(MenuItem* item);

	void getItemParams(std::string& name, int& quantity, std::string& description, double& price) const;
	void createItem();

	void getFoodParams(std::string& name, int& quantity, std::string& description, double& price, bool& isBig, bool& isVegan) const;
	void createFood();

	void getDrinkParams(std::string& name, int& quantity, std::string& description, double& price, ServingType& servingType) const;
	void createDrink();

	void getAlcoholParams(std::string& name, int& quantity, std::string& description, double& price, ServingType& servingType, double& alcoholPercentage) const;
	void createAlcohol();
};

#endif // !MENU_H
