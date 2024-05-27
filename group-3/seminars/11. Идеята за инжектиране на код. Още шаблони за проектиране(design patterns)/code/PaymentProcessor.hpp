#ifndef __PAYMENT_PROCESSOR_HEADER__
#define __PAYMENT_PROCESSOR_HEADER__
#include "ILogger.hpp"
#include <stdexcept>
#include <thread>

class PaymentProcessor {
public:
	PaymentProcessor(ILogger* logger) : logger(logger)
	{
		if (logger == nullptr) {
			throw std::invalid_argument("Logger is null");
		}
	}

	PaymentProcessor(const PaymentProcessor& other)
	{
		this->logger = other.logger ? other.logger->clone() : nullptr;
	}

	PaymentProcessor& operator=(const PaymentProcessor& other) {
		if (this != &other) {
			ILogger* newLogger = other.logger ? other.logger->clone() : nullptr;

			delete logger;
			logger = newLogger;
		}

		return *this;
	}

	~PaymentProcessor() {
		delete logger;
	}

	void processPayment() {
		// Examples of more than one log levels used. If we want we can set minLogLevel in the config and ignore debug messages.
		logger->LogDebug("Payment processor initiates processPayment().");

		try {
			logger->LogInfo("Starting payment processing...");
			int result = pay();
			logger->LogInfo("Payment processed successfully! Result: " + std::to_string(result));
		}
		catch (const std::exception& e) {
			std::string err = e.what();
			logger->LogError("Payment processing failed. " + err);
		}

		logger->LogDebug("Payment processor ends processPayment().");
	}

private:
	ILogger* logger;

	// Imitates heavy computation that randomly fails and sleeps for 2 seconds.
// The goal is to imitate the complex process of payment.
	int pay() {
		// Waits 2 seconds before continuing execution of the code.
		std::this_thread::sleep_for(std::chrono::seconds(1));

		int result = std::rand();
		if (result % 2 == 0) {
			throw std::runtime_error("Connection to payment service was lost.");
		}

		return result;
	}
};


#endif