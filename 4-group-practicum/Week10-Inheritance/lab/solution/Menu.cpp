#include "Menu.h"

Menu& Menu::getInstance() {
	static Menu menu;

	return menu;
}

Menu::~Menu() {
	deleteData();
}

void Menu::addItem(std::string_view type) {
	if (type == "item") createItem();
	else if (type == "food") createFood();
	else if (type == "drink") createDrink();
	else if (type == "alcohol") createAlcohol();
}

Menu::Menu() : m_data(nullptr), m_size(0), m_capacity(0) {
	allocMem(2);
}

void Menu::deleteData() {
	for (size_t index = 0; index < m_size; ++index) {
		delete m_data[index];

		m_data[index] = nullptr;
	}

	delete[] m_data;
	m_data = nullptr;
}

void Menu::allocMem(size_t newCapacity) {
	if (newCapacity <= m_size) newCapacity = m_size + 1;
	
	MenuItem** blockOfMem = new MenuItem*[newCapacity];

	for (size_t index = 0; index < m_size; ++index)
		blockOfMem[index] = m_data[index]->clone();

	deleteData();
	m_data = blockOfMem;
	m_capacity = newCapacity;
}

bool Menu::empty() const {
	return m_size == 0;
}

void Menu::addItemToMenu(MenuItem* item) {
	if (m_size == m_capacity) allocMem(m_capacity * 2);

	m_data[m_size++] = item;
}

void Menu::getItemParams(std::string& name, int& quantity, std::string& description, double& price) const {
	std::cout << "Enter Name: ";
	std::getline(std::cin, name);

	std::cout << "Enter Quantity: ";
	std::cin >> quantity;

	std::cout << "Enter Small Description: ";
	std::cin.ignore();
	std::getline(std::cin, description);

	std::cout << "Enter Price: ";
	std::cin >> price;
}

void Menu::createItem() {
	std::string name;
	int quantity;
	std::string description;
	double price;

	getItemParams(name, quantity, description, price);

	addItemToMenu(new MenuItem(name, quantity, description, price));
}

void Menu::getFoodParams(std::string& name, int& quantity, std::string& description, double& price, bool& isBig, bool& isVegan) const {
	getItemParams(name, quantity, description, price);

	std::string size = "";

	do {
		std::cout << "Size (big | small): ";
		std::cin.ignore();
		std::getline(std::cin, size);
	} while (size != "big" && size != "small");

	isBig = size == "big";

	std::string vegan = "";

	do {
		std::cout << "Is vegan (yes | no): ";
		std::getline(std::cin, vegan);

		std::cout << vegan << std::endl;
	} while (vegan != "yes" && vegan != "no");

	isVegan = vegan == "yes";
}

void Menu::createFood() {
	std::string name;
	int quantity;
	std::string description;
	double price;
	bool isBig;
	bool isVegan;

	getFoodParams(name, quantity, description, price, isBig, isVegan);

	addItemToMenu(new Food(name, quantity, description, price, isBig, isVegan));
}

void Menu::getDrinkParams(std::string& name, int& quantity, std::string& description, double& price, ServingType& servingType) const {
	getItemParams(name, quantity, description, price);

	std::string servingTypeStr;

	do {
		std::cout << "Enter serving type (glass | jug | bottle): ";

		std::cin.ignore();
		std::getline(std::cin, servingTypeStr);
	} while (servingTypeStr != "glass" && servingTypeStr != "jug" && servingTypeStr != "bottle");

	servingType = servingTypeStr == "glass" ? ServingType::GLASS : (servingTypeStr == "jug" ? ServingType::JUG : ServingType::BOTTLE);
}

void Menu::createDrink() {
	std::string name;
	int quantity;
	std::string description;
	double price;
	ServingType servingType;

	getDrinkParams(name, quantity, description, price, servingType);

	addItemToMenu(new Drink(name, quantity, description, price, servingType));
}

void Menu::getAlcoholParams(std::string& name, int& quantity, std::string& description, double& price, ServingType& servingType, double& alcoholPercentage) const {
	getDrinkParams(name, quantity, description, price, servingType);

	std::cout << "Enter Alcohol Percentage: ";
	std::cin >> alcoholPercentage;
}

void Menu::createAlcohol() {
	std::string name;
	int quantity;
	std::string description;
	double price;
	ServingType servingType;
	double alcoholPercentage;

	getAlcoholParams(name, quantity, description, price, servingType, alcoholPercentage);

	addItemToMenu(new Alcohol(name, quantity, description, price, servingType, alcoholPercentage));
}

void Menu::printCheapestMenuItem() const {
	if (empty()) {
		std::cout << "Menu is empty!" << std::endl;

		return;
	}

	MenuItem* cheapest = m_data[0];

	for (size_t index = 0; index < m_size; ++index)
		if (cheapest->getPrice() > m_data[index]->getPrice())
			cheapest = m_data[index];

	std::cout << cheapest->getInfo();
}

unsigned Menu::getNumberOfAlcoholFreeDrinks() const {
	if (empty()) return 0;

	unsigned numberOfAlcoholFreeDrinks = 0;

	for (size_t index = 0; index < m_size; ++index)
		if (dynamic_cast<Drink*>(m_data[index]) != nullptr &&
			dynamic_cast<Alcohol*>(m_data[index]) == nullptr)
			++numberOfAlcoholFreeDrinks;
	
	return numberOfAlcoholFreeDrinks;
}

void Menu::getDrinkWithTheHighestAlcoholPercentage() const {
	if (empty()) {
		std::cout << "Menu is empty!" << std::endl;

		return;
	}

	Alcohol* drinkWithTheHighestAlcoholPercentage = nullptr;

	for (size_t index = 0; index < m_size; ++index) {
		Alcohol* drink = dynamic_cast<Alcohol*>(m_data[index]);

		if (drink != nullptr &&
			(drinkWithTheHighestAlcoholPercentage == nullptr ||
				drink->getAlcoholPercentage() > drinkWithTheHighestAlcoholPercentage->getAlcoholPercentage()))
			drinkWithTheHighestAlcoholPercentage = drink;
	}

	if (drinkWithTheHighestAlcoholPercentage != nullptr)
		std::cout << drinkWithTheHighestAlcoholPercentage->getInfo();
	else std::cout << "No drinks with alcohol in them" << std::endl;
}

void Menu::print() const {
	if (empty()) {
		std::cout << "Menu is empty!" << std::endl;

		return;
	}

	std::cout << "Menu:" << std::endl;

	for (size_t index = 0; index < m_size; ++index)
		std::cout << m_data[index]->getInfo() << std::endl;
}
