#include "Engine.h"

Engine& Engine::getInstance() {
	static Engine engine;

	return engine;
}

Engine::Engine() {
	m_menu = &Menu::getInstance();
}

void Engine::run() {
	char operation;

	do {
		printOperations();
		getOperation(operation);
		executeOperation(operation);
	} while (operation != '6');
}

const std::string Engine::getMenuItemType() const {
	std::string type;

	do {
		std::cout << "Enter Item Type (item | food | drink | alcohol): ";
		std::cin.ignore();
		std::getline(std::cin, type);

		std::transform(type.begin(), type.end(), type.begin(), [](unsigned char c) { return tolower(c); });
	} while (type != "item" && type != "food" && type != "drink" && type != "alcohol");

		return type;
}

void Engine::printOperations() const {
	std::cout << "1) Add Menu Item" << std::endl;
	std::cout << "2) Print Menu" << std::endl;
	std::cout << "3) Print The Cheapest Menu Item" << std::endl;
	std::cout << "4) Get Number of Alcohol Free Drinks" << std::endl;
	std::cout << "5) Get The Drink With The Highest Alcohol Percantage" << std::endl;
	std::cout << "6) Exit" << std::endl;
}

void Engine::getOperation(char& operation) const {
	std::cin >> operation;
}

void Engine::executeOperation(const char operation) {
	if (operation == '1') m_menu->addItem(getMenuItemType());
	else if (operation == '2') m_menu->print();
	else if (operation == '3') m_menu->printCheapestMenuItem();
	else if (operation == '4') std::cout << m_menu->getNumberOfAlcoholFreeDrinks() << std::endl;
	else if (operation == '5') m_menu->getDrinkWithTheHighestAlcoholPercentage();
	else if (operation != '6') std::cout << "Invalid Operation" << std::endl;
}


