#ifndef __LOG_COLOR_HEADER__
#define __LOG_COLOR_HEADER__
#include <string>

enum class LogColor {
	Default = 0,
	LightYellow = 1,
	Orange = 2,
	Red = 3,
	DarkRed = 4,
	LightBlue = 5,
	LightGreen = 6
};

std::string mapLogColorToConsoleColor(LogColor color) {
	switch (color) {
	case LogColor::LightYellow: return "\033[93m";
	case LogColor::Orange: return "\033[91m";
	case LogColor::Red: return "\033[31m";
	case LogColor::DarkRed: return "\033[91m";  // Bright red
	case LogColor::LightBlue: return "\033[94m";
	case LogColor::LightGreen: return "\033[92m";
	default: return "\033[0m";  // Default color
	}
}

#endif