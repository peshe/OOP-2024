#ifndef __CONSOLE_LOGGER_CONFIG__
#define __CONSOLE_LOGGER_CONFIG__
#include "LogColor.hpp"
#include "LogLevel.hpp"

struct ConsoleLoggerConfig {
	bool includeTimestamp;

	LogColor debugColor;
	LogColor infoColor;
	LogColor warningColor;
	LogColor errorColor;
	LogColor criticalColor;

	// For example, if equals to LogLevel::Warning, print warning and above. Ignore Debug and Info.
	// Primarily used to have either extremely detailed logs or very sparse logs, for example only errors and critical errors.
	LogLevel minLogLevel;
};

#endif