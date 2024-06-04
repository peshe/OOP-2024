#include <iostream>
#include "PaymentProcessor.hpp"
#include "ConsoleLoggerConfig.hpp"
#include "ConsoleLogger.hpp"

#pragma warning(disable:4996)

int main() {
	std::srand(std::time(0));

	int repeat = 4;

	// Initialize an object using an initializer list
	ConsoleLoggerConfig loggerConfig = {
	   true,                   // includeTimestamp
	   LogColor::LightGreen,   // debugColor
	   LogColor::LightBlue,    // infoColor
	   LogColor::LightYellow,  // warningColor
	   LogColor::Orange,       // errorColor
	   LogColor::Red,          // criticalColor
	   LogLevel::Debug       // minLogLevel
	};

	ILogger* detailedLogger = new ConsoleLogger(loggerConfig);
	PaymentProcessor processor(detailedLogger);

	for (int i = 0; i < 10; i++)
	{
		processor.processPayment();
	}

	std::cout << "Processing finished." << std::endl;

	return 0;
}