#ifndef ENGINE_H
#define ENGINE_H

#include <algorithm>

#include "Menu.h"

class Engine {
public:
	static Engine& getInstance();

	void run();

private:
	Engine();
	Engine(const Engine&) = delete;

	Engine& operator=(const Engine&) = delete;

private:
	Menu* m_menu;

	const std::string getMenuItemType() const;

	void printOperations() const;
	void getOperation(char&) const;
	void executeOperation(const char);
};

#endif // !ENGINE_H

