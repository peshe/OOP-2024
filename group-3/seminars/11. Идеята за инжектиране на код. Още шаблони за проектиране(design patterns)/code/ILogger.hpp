#ifndef __ILOGGER_HEADER__
#define __ILOGGER_HEADER__
#include <string>
#include "LogLevel.hpp"

// Abstract class. For "client" classes, that use it, provides all the pure virtual methods as interface.
// For classes that inherit it, enforces overriding of all pure virtual methods.
class ILogger {
public:
	// Different levels of logging, starting from the least to most important.
	virtual void LogDebug(const std::string& message) const = 0;
	virtual void LogInfo(const std::string& message) const = 0;
	virtual void LogWarning(const std::string& message) const = 0;
	virtual void LogError(const std::string& message) const = 0;
	virtual void LogCritical(const std::string& message) const = 0;

	// Used to create copies of the classes that inherit it. 
	// Used in the copy constructor and operator= of classes that use it through ILogger* polymorphic field.
	virtual ILogger* clone() const = 0;
	virtual ~ILogger() = default;

	std::string mapLogLevelToTag(LogLevel level) const {
		switch (level)
		{
		case LogLevel::Debug:
			return "[dbg] ";
		case LogLevel::Info:
			return "[inf] ";
		case LogLevel::Warning:
			return "[wrn] ";
		case LogLevel::Error:
			return "[err] ";
		case LogLevel::Critical:
			return "[crt] ";
		default:
			return "[???] ";
		}
	}
};

#endif