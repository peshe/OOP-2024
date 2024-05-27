#include <string>
#include <thread>
#include <chrono>
#include <iomanip>
#include <sstream>

#pragma warning(disable:4996)

std::string getCurrentTimestamp() {
	auto now = std::time(nullptr);
	auto localTime = *std::localtime(&now);

	std::ostringstream oss;
	oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}