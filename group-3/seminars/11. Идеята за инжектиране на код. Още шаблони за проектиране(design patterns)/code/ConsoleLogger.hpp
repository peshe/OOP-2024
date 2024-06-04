#ifndef __CONSOLE_LOGGER_HEADER__
#define __CONSOLE_LOGGER_HEADER__
#include <iostream>
#include "ILogger.hpp"
#include "ConsoleLoggerConfig.hpp"
#include "utils.hpp"

class ConsoleLogger : public virtual ILogger {
public:

	ConsoleLogger(ConsoleLoggerConfig config) : config(config)
	{	}

	void LogDebug(const std::string& message) const override {
		Log(LogLevel::Debug, message);
	}

	void LogInfo(const std::string& message) const override {
		Log(LogLevel::Info, message);
	}

	void LogWarning(const std::string& message) const override {
		Log(LogLevel::Warning, message);
	}

	void LogError(const std::string& message) const override {
		Log(LogLevel::Error, message);
	}

	void LogCritical(const std::string& message) const override {
		Log(LogLevel::Critical, message);
	}

	void Log(LogLevel level, const std::string& message) const {
		if (level < this->config.minLogLevel) {
			return;
		}

		LogColor color = mapLogLevelToLogColor(level);

		std::cout << mapLogColorToConsoleColor(color);
		std::cout << mapLogLevelToTag(level);

		if (config.includeTimestamp) {
			std::cout << getCurrentTimestamp();
		}

		std::cout << " : " << message << mapLogColorToConsoleColor(LogColor::Default)<< std::endl;

	}

	ILogger* clone() const override {
		return new ConsoleLogger(*this);
	}

private:
	ConsoleLoggerConfig config;

	LogColor mapLogLevelToLogColor(LogLevel level) const {
		switch (level)
		{
		case LogLevel::Debug:
			return config.debugColor;
		case LogLevel::Info:
			return config.infoColor;
		case LogLevel::Warning:
			return config.warningColor;
		case LogLevel::Error:
			return config.errorColor;
		case LogLevel::Critical:
			return config.criticalColor;
		default:
			return LogColor::Default;
		}
	}
};

#endif