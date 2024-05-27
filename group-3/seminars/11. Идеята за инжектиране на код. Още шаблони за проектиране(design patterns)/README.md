# 11. Идеята за инжектиране на код. Още шаблони за проектиране(design patterns)

Следват поредица от задачи и техните решения, които са свързани и вариация на различни случай за код, който изпълнява плащания. Логиката зад плащането не е важна и е скрита зад функция, която "смята дълго време". Идеята е, че този процес е дълъг и има нужда от информация за своето стартиране и край с цел подобряване на неочаквани грешки (например връзката с приложението, което изпълнява плащания е прекъсната).

Целта е да разгледаме дадени имплементанции и ограниченията и проблемите, които те имат и да видим и въведем идеята за инжектиране на код и как тя ни помага.

## 1. Начало: PaymentProcessor 
Създай клас `PaymentProcessor`, който има метод `ProcessPayment`. Методът трябва да показва съобщения в конзолата при стартиране, приключване и при неочаквани грешки.

```c++
#include <iostream>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>

// Imitates heavy computation that randomly fails and sleeps for 2 seconds.
// The goal is to imitate the complex process of payment.
int pay() {
    // Waits 2 seconds before continuing execution of the code.
    std::this_thread::sleep_for(std::chrono::seconds(2));

    int result = std::rand();
    if (result % 2 == 0) {
        throw std::runtime_error("Connection to payment service was lost.");
    }

    return result;
}

class PaymentProcessor {
public:
    void processPayment() {
        try {
            std::cout << "Starting payment processing..." << std::endl;
            int result = pay();
            std::cout << "Payment processed successfully! Result: " << result << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Payment processing failed: " << e.what() << std::endl;
        }
    }
};

int main() {
    std::srand(std::time(0));

    PaymentProcessor processor;
    processor.ProcessPayment();

    return 0;
}

```

## 2. Добавяне на клас Logger
Имплементирай клас `Logger`, който има методи `void Log(const std::string& message)` и `void LogError(const std::string& message)`, който показва съобщението на конзолата. Добавете поле от тип `Logger` в `PaymentProcessor` и го използвайте вместо `std::cout` и `std::cerr`. Изпълнете 10 плащания в `main()`.

```c++
#include <iostream>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>

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

class Logger {
public:
	void Log(const std::string& message) {
		std::cout << "[inf] : " << message << std::endl;
	}

	void LogError(const std::string& message) {
		std::cout << "[err] : " << message << std::endl;

	}

};

class PaymentProcessor {
public:
	void processPayment() {
		try {
			logger.Log("Starting payment processing...");
			int result = pay();
			logger.Log("Payment processed successfully! Result: " + std::to_string(result));
		}
		catch (const std::exception& e) {
			std::string err = e.what();
			logger.LogError("Payment processing failed: " + err);
		}
	}

private:
	Logger logger;
};

int main() {
	std::srand(std::time(0));

	PaymentProcessor processor;
	for (int i = 0; i < 10; i++)
	{
		processor.processPayment();
		std::cout << std::endl;
	}

	return 0;
}
```

## 3. Конфигуриране на Logger

Добавете възможност за конфигуриране на `Logger` чрез неговия конструктор. Да се дава възможност за логване на текущата дата и час при всяко съобщение, както и за променяне на цвета, с който се пише на конзолата. За `cout` възможните цветове да са зелен, син и бял, а за `cerr` червен и бял.

```c++
#include <iostream>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>

#pragma warning(disable:4996)

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

enum class LogColor {
	Default = 0,
	Green = 1,
	Blue = 2
};

enum class LogErrorColor {
	Default = 0,
	Red = 1
};

class Logger {
public:
	Logger(bool addTimestamp = false,
		LogColor logColor = LogColor::Default,
		LogErrorColor errorColor = LogErrorColor::Default)
		: addTimestamp(addTimestamp), logColor(logColor), errorColor(errorColor)
	{

	}

	void Log(const std::string& message) {
		std::cout << getLogColor(this->logColor);

		if (addTimestamp) {
			std::cout << "[inf] " << getCurrentTimestamp() << " : " << message << std::endl;
		}
		else {
			std::cout << "[inf] : " << message << std::endl;
		}

		// Revert console color to white.
		std::cout << "\033[0m";
	}

	void LogError(const std::string& message) {
		std::cerr << getErrorColor(this->errorColor);

		if (addTimestamp) {
			std::cerr << "[err] " << getCurrentTimestamp() << " : " << message << std::endl;
		}
		else {
			std::cerr << "[err] : " << message << std::endl;
		}

		// Revert console color to white.
		std::cerr << "\033[0m";
	}

private:
	bool addTimestamp;
	LogColor logColor;
	LogErrorColor errorColor;

	std::string getCurrentTimestamp() {
		auto now = std::time(nullptr);
		auto localTime = *std::localtime(&now);

		std::ostringstream oss;
		oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}

	std::string getLogColor(LogColor color) {
		switch (color)
		{
		case LogColor::Green:
			return "\033[92m";
		case LogColor::Blue:
			return "\033[94m";
		default:
			return "\033[0m";
		}
	}

	std::string getErrorColor(LogErrorColor color) {
		switch (color)
		{
		case LogErrorColor::Red:
			return "\033[91m";
		default:
			return "\033[0m";
		}
	}
};

class PaymentProcessor {
public:
	void processPayment() {
		try {
			logger.Log("Starting payment processing...");
			int result = pay();
			logger.Log("Payment processed successfully! Result: " + std::to_string(result));
		}
		catch (const std::exception& e) {
			std::string err = e.what();
			logger.LogError("Payment processing failed: " + err);
		}
	}

private:
	Logger logger;
};

int main() {
	std::srand(std::time(0));

	PaymentProcessor processor;
	for (int i = 0; i < 10; i++)
	{
		processor.processPayment();
		std::cout << std::endl;
	}

	return 0;
}
```

### Проблеми с текущия код
Макар че имаме логър, който може да бъде конфигуриран, не можем да конфигурираме полето `logger` на `PaymentProcessor` по никакъв начин. Можем да направим default constructor за `PaymentProcessor`, който да извиква конструктора на `Logger`, но това също не е достатъчно добро, защото `PaymentProcessor` ще започне да отговаря за 2 неща - плащанията и логъра.

**(Violation 1)** - Класовете `Logger` и `PaymentProcessor` са прекалено свързани(coupling). Промени по `Logger` изискват промени по имплементацията на `PaymentProcessor`. 

### Решение
Искаме да можем да подаваме конфигурация за логъра така че, когато има друга конфигурация, да не трябва да променяме имплементацията на `PaymentProcessor`. Това става с добре познатия ни `constructor`.

```c++
#include <iostream>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>

#pragma warning(disable:4996)

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

enum class LogColor {
	Default = 0,
	Green = 1,
	Blue = 2
};

enum class LogErrorColor {
	Default = 0,
	Red = 1
};

class Logger {
public:
	Logger(bool addTimestamp = false,
		LogColor logColor = LogColor::Default,
		LogErrorColor errorColor = LogErrorColor::Default)
		: addTimestamp(addTimestamp), logColor(logColor), errorColor(errorColor)
	{

	}

	void Log(const std::string& message) {
		std::cout << getLogColor(this->logColor);

		if (addTimestamp) {
			std::cout << "[inf] " << getCurrentTimestamp() << " : " << message << std::endl;
		}
		else {
			std::cout << "[inf] : " << message << std::endl;
		}

		// Revert console color to white.
		std::cout << "\033[0m";
	}

	void LogError(const std::string& message) {
		std::cerr << getErrorColor(this->errorColor);

		if (addTimestamp) {
			std::cerr << "[err] " << getCurrentTimestamp() << " : " << message << std::endl;
		}
		else {
			std::cerr << "[err] : " << message << std::endl;
		}

		// Revert console color to white.
		std::cerr << "\033[0m";
	}

private:
	bool addTimestamp;
	LogColor logColor;
	LogErrorColor errorColor;

	std::string getCurrentTimestamp() {
		auto now = std::time(nullptr);
		auto localTime = *std::localtime(&now);

		std::ostringstream oss;
		oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}

	std::string getLogColor(LogColor color) {
		switch (color)
		{
		case LogColor::Green:
			return "\033[92m";
		case LogColor::Blue:
			return "\033[94m";
		default:
			return "\033[0m";
		}
	}

	std::string getErrorColor(LogErrorColor color) {
		switch (color)
		{
		case LogErrorColor::Red:
			return "\033[91m";
		default:
			return "\033[0m";
		}
	}
};

class PaymentProcessor {
public:

	PaymentProcessor(Logger logger) : logger(logger)  // <-----
	{

	}
	void processPayment() {
		try {
			logger.Log("Starting payment processing...");
			int result = pay();
			logger.Log("Payment processed successfully! Result: " + std::to_string(result));
		}
		catch (const std::exception& e) {
			std::string err = e.what();
			logger.LogError("Payment processing failed: " + err);
		}
	}

private:
	Logger logger;
};

int main() {
	std::srand(std::time(0));

    Logger logger = Logger(true, LogColor::Green, LogErrorColor::Red); // <-----
	PaymentProcessor processor(logger);  // <-----
	for (int i = 0; i < 10; i++)
	{
		processor.processPayment();
		std::cout << std::endl;
	}

	return 0;
}
```

С текущата имплементация, всякакви промени по конфигурацията на логъра се случва извън класа `PaymentProcessor`, Независимо дали, добавяме, махаме или променяме стойности, нови конфигурации и т.н.
`PaymentProcessor` не се променя по никакъв начин. Това е знак за по-добър дизайн на класовете ни и връзките между тях.

## 4. Промяна: FileLogger
Имплементирайте нов клас `FileLogger`, който позволява логване във файл. Когато съобщение бъде логнато, то трябва да бъде записвано във файл `logs.txt`. Новият логър да поддържа същата функционалност като предишния `Logger` без цветовете. Използвайте `FileLogger` вместо `Logger` в `PaymentProcessor`.

```c++
#include <iostream>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>
#include <fstream>

#pragma warning(disable:4996)

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

enum class LogColor {
	Default = 0,
	Green = 1,
	Blue = 2
};

enum class LogErrorColor {
	Default = 0,
	Red = 1
};

class Logger {
public:
	Logger(bool addTimestamp = false,
		LogColor logColor = LogColor::Default,
		LogErrorColor errorColor = LogErrorColor::Default)
		: addTimestamp(addTimestamp), logColor(logColor), errorColor(errorColor)
	{

	}

	void Log(const std::string& message) {
		std::cout << getLogColor(this->logColor);

		if (addTimestamp) {
			std::cout << "[inf] " << getCurrentTimestamp() << " : " << message << std::endl;
		}
		else {
			std::cout << "[inf] : " << message << std::endl;
		}

		// Revert console color to white.
		std::cout << "\033[0m";
	}

	void LogError(const std::string& message) {
		std::cerr << getErrorColor(this->errorColor);

		if (addTimestamp) {
			std::cerr << "[err] " << getCurrentTimestamp() << " : " << message << std::endl;
		}
		else {
			std::cerr << "[err] : " << message << std::endl;
		}

		// Revert console color to white.
		std::cerr << "\033[0m";
	}

private:
	bool addTimestamp;
	LogColor logColor;
	LogErrorColor errorColor;

	std::string getCurrentTimestamp() {
		auto now = std::time(nullptr);
		auto localTime = *std::localtime(&now);

		std::ostringstream oss;
		oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}

	std::string getLogColor(LogColor color) {
		switch (color)
		{
		case LogColor::Green:
			return "\033[92m";
		case LogColor::Blue:
			return "\033[94m";
		default:
			return "\033[0m";
		}
	}

	std::string getErrorColor(LogErrorColor color) {
		switch (color)
		{
		case LogErrorColor::Red:
			return "\033[91m";
		default:
			return "\033[0m";
		}
	}
};


class FileLogger { // <----
public:
	FileLogger(bool addTimestamp = false)
		: addTimestamp(addTimestamp)
	{

	}

	void Log(const std::string& message) {
		std::ofstream out("logs.txt", std::ios::app);
		if (!out) {
			return;
		}

		try {
			if (addTimestamp) {
				out << "[inf] " << getCurrentTimestamp() << " : " << message << std::endl;
			}
			else {
				out << "[inf] : " << message << std::endl;
			}
		}
		catch (...) {
			out.close();
		}

		out.close();
	}

	void LogError(const std::string& message) {
		std::ofstream out("logs.txt", std::ios::app);
		if (!out) {
			return;
		}

		try {
			if (addTimestamp) {
				out << "[err] " << getCurrentTimestamp() << " : " << message << std::endl;
			}
			else {
				out << "[err] : " << message << std::endl;
			}
		}
		catch (...) {
			out.close();
		}

		out.close();
	}
private:
	bool addTimestamp;

	std::string getCurrentTimestamp() {
		auto now = std::time(nullptr);
		auto localTime = *std::localtime(&now);

		std::ostringstream oss;
		oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}
};

class PaymentProcessor {
public:
	PaymentProcessor(FileLogger logger) : logger(logger) // <----
	{

	}

	void processPayment() {
		try {
			logger.Log("Starting payment processing...");
			int result = pay();
			logger.Log("Payment processed successfully! Result: " + std::to_string(result));
		}
		catch (const std::exception& e) {
			std::string err = e.what();
			logger.LogError("Payment processing failed: " + err);
		}
	}

private:
	FileLogger logger;
};

int main() {
	std::srand(std::time(0));

	PaymentProcessor processor(FileLogger(true)); // <----
	for (int i = 0; i < 10; i++)
	{
		processor.processPayment();
		std::cout << std::endl;
	}

	return 0;
}
```

### Проблеми с текущата имплементация
В предишната задача стигнахме до заключението, че промяната на логъра, не трябва да принуждава `PaymentProcessor` по някакъв начин да си променя имплементацията. Това нарушава принципът на `Single responsibility`, който гласи че **всеки клас трябва да прави 1 нещо и да го прави добре**. 

Сега срещаме същият проблем, но на друго ниво. Досега промени по самият клас `Logger` не ни принуждаваха да променяме `PaymentProcessor`, но сега след като въведохме напълно друг клас за логване във файл, отново сме принудени да променим `PaymentProcessor`, макар че той не би трябвало да се интересува от това дали логваме в конзолата или във файл. Стигаме до същият проблем както преди но на друго ниво.

В случая тази промяна е цялостната смяна на `Logger`. 

**(Violation 1)** - Класовете `Logger` и `PaymentProcessor` са прекалено свързани(coupling). Промени по `Logger` изискват промени по имплементацията на `PaymentProcessor`. 

**NEW (Violation 2)** - Класовете `FileLogger` и `PaymentProcessor` са прекалено свързани(coupling). Смяна на `FileLogger` с друга имплементация води до промени по `PaymentProcessor`.


Нека помислим откакво имаме нужда и какво трябва можем да правим в `PaymentProcessor`, което е свързано с логване. Всъщност единственото нещо, което ни интересува като автори на класа е да можем да логваме информация и да логваме грешки. Нищо друго не ни интересува, дали логваме в конзолата или във файл, дали има час и дата или не, какъв е цвета и т.н. Важно е да можем да логнем дадено съобщение, което ние сме преценили, че трябва да се запази по някакъв начин. 

Преди бяхме свързани с `Logger` и неговата конзолна имплементация. Сега сме свързани с `FileLogger` и неговата имплементация за писане във файл.

### Решение
Да нямаме знания и достъп до никаква имплементация, а по-скоро само и единствено до интерфейс - `LogInfo` и `LogError`.

Това можем да постигнем ако използваме абстрактен базов клас и чисто виртуални методи.

```c++
class ILogger {
public:
	virtual void LogInfo(const std::string& message) const = 0;
	virtual void LogError(const std::string& message) const = 0;
};

...

class PaymentProcessor {
public:
	PaymentProcessor(ILogger* logger) : logger(logger) // <----
	{

	}

    void processPayment() {
	try {
		logger->Log("Starting payment processing..."); // <----
		int result = pay();
		logger->Log("Payment processed successfully! Result: " + std::to_string(result));
	}
	catch (const std::exception& e) {
		std::string err = e.what();
		logger->LogError("Payment processing failed: " + err);
	}
}
private:
	ILogger* logger; // <----
}
```

Вече можем да използваме наследяване при логърите и да използваме абстрактния базов клас в `PaymentProcessor`.

Целият код изглежда така:

```c++
#include <iostream>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>
#include <fstream>

#pragma warning(disable:4996)

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

enum class LogColor {
	Default = 0,
	Green = 1,
	Blue = 2
};

enum class LogErrorColor {
	Default = 0,
	Red = 1
};

class ILogger {
public:
	virtual void Log(const std::string& message) const = 0;
	virtual void LogError(const std::string& message) const = 0;
};

class Logger : public ILogger {
public:
	Logger(bool addTimestamp = false,
		LogColor logColor = LogColor::Default,
		LogErrorColor errorColor = LogErrorColor::Default)
		: addTimestamp(addTimestamp), logColor(logColor), errorColor(errorColor)
	{

	}

	void Log(const std::string& message) const override {
		std::cout << getLogColor(this->logColor);

		if (addTimestamp) {
			std::cout << "[inf] " << getCurrentTimestamp() << " : " << message << std::endl;
		}
		else {
			std::cout << "[inf] : " << message << std::endl;
		}

		// Revert console color to white.
		std::cout << "\033[0m";
	}

	void LogError(const std::string& message) const override {
		std::cerr << getErrorColor(this->errorColor);

		if (addTimestamp) {
			std::cerr << "[err] " << getCurrentTimestamp() << " : " << message << std::endl;
		}
		else {
			std::cerr << "[err] : " << message << std::endl;
		}

		// Revert console color to white.
		std::cerr << "\033[0m";
	}

private:
	bool addTimestamp;
	LogColor logColor;
	LogErrorColor errorColor;

	std::string getCurrentTimestamp() const {
		auto now = std::time(nullptr);
		auto localTime = *std::localtime(&now);

		std::ostringstream oss;
		oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}

	std::string getLogColor(LogColor color) const {
		switch (color)
		{
		case LogColor::Green:
			return "\033[92m";
		case LogColor::Blue:
			return "\033[94m";
		default:
			return "\033[0m";
		}
	}

	std::string getErrorColor(LogErrorColor color) const {
		switch (color)
		{
		case LogErrorColor::Red:
			return "\033[91m";
		default:
			return "\033[0m";
		}
	}
};


class FileLogger : public ILogger { // <----
public:
	FileLogger(bool addTimestamp = false)
		: addTimestamp(addTimestamp)
	{

	}

	void Log(const std::string& message) const override {
		std::ofstream out("logs.txt", std::ios::app);
		if (!out) {
			return;
		}

		try {
			if (addTimestamp) {
				out << "[inf] " << getCurrentTimestamp() << " : " << message << std::endl;
			}
			else {
				out << "[inf] : " << message << std::endl;
			}
		}
		catch (...) {
			out.close();
		}

		out.close();
	}

	void LogError(const std::string& message) const override {
		std::ofstream out("logs.txt", std::ios::app);
		if (!out) {
			return;
		}

		try {
			if (addTimestamp) {
				out << "[err] " << getCurrentTimestamp() << " : " << message << std::endl;
			}
			else {
				out << "[err] : " << message << std::endl;
			}
		}
		catch (...) {
			out.close();
		}

		out.close();
	}
private:
	bool addTimestamp;

	std::string getCurrentTimestamp() const {
		auto now = std::time(nullptr);
		auto localTime = *std::localtime(&now);

		std::ostringstream oss;
		oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}
};

class PaymentProcessor {
public:
	PaymentProcessor(ILogger* logger) : logger(logger) // <----
	{

	}

	void processPayment() {
		try {
			logger->Log("Starting payment processing...");
			int result = pay();
			logger->Log("Payment processed successfully! Result: " + std::to_string(result));
		}
		catch (const std::exception& e) {
			std::string err = e.what();
			logger->LogError("Payment processing failed: " + err);
		}
	}

private:
	ILogger* logger;
};

int main() {
	std::srand(std::time(0));

	PaymentProcessor processor1(new Logger(true)); // <----
	PaymentProcessor processor2(new FileLogger(true)); // <----
	for (int i = 0; i < 10; i++)
	{
		processor1.processPayment();
		std::cout << std::endl;
	}

	for (int i = 0; i < 10; i++)
	{
		processor2.processPayment();
		std::cout << std::endl;
	}

	std::cout << "Processing finished." << std::endl;

	return 0;
}
```

Обърнете внимание на изпълнението в `main()`, Вече можем да създаваме `PaymentProcessor` с различни имплементации(в случая `Logger` и `FileLogger`), които изпълняват условията поставени от абстрактният базов клас `ILogger`.

#### Нови проблеми и решения
Решихме проблемите, които предишната ни имплементация имаше. Текущата въвежда повече сложност, както и нуждата от голяма четворка за `PaymentProcessor`, тъй като вече имаме указател като поле. Това означава, 
че също имаме полиморфизъм, тоест имаме нужда от виртуален деструктор на абстрактния базов клас. А за да копираме успешно класовете които го наследяват, имаме нужда от `clone`, тъй като нямаме информация от базовия клас, кой от наследяващите класове е текущия тип. 

Така изглежда подобрения код:

```c++
#include <iostream>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>
#include <fstream>

#pragma warning(disable:4996)

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

enum class LogColor {
	Default = 0,
	Green = 1,
	Blue = 2
};

enum class LogErrorColor {
	Default = 0,
	Red = 1
};

class ILogger {
public:
	virtual void Log(const std::string& message) const = 0;
	virtual void LogError(const std::string& message) const = 0;

	virtual ILogger* clone() const = 0;  // <----
	virtual ~ILogger() = default;  // <----
};

class Logger : public ILogger {
public:
	Logger(bool addTimestamp = false,
		LogColor logColor = LogColor::Default,
		LogErrorColor errorColor = LogErrorColor::Default)
		: addTimestamp(addTimestamp), logColor(logColor), errorColor(errorColor)
	{

	}

	ILogger* clone() const override {  // <----
		return new Logger(*this);
	}

	void Log(const std::string& message) const override {
		std::cout << getLogColor(this->logColor);

		if (addTimestamp) {
			std::cout << "[inf] " << getCurrentTimestamp() << " : " << message << std::endl;
		}
		else {
			std::cout << "[inf] : " << message << std::endl;
		}

		// Revert console color to white.
		std::cout << "\033[0m";
	}

	void LogError(const std::string& message) const override {
		std::cerr << getErrorColor(this->errorColor);

		if (addTimestamp) {
			std::cerr << "[err] " << getCurrentTimestamp() << " : " << message << std::endl;
		}
		else {
			std::cerr << "[err] : " << message << std::endl;
		}

		// Revert console color to white.
		std::cerr << "\033[0m";
	}

private:
	bool addTimestamp;
	LogColor logColor;
	LogErrorColor errorColor;

	std::string getCurrentTimestamp() const {
		auto now = std::time(nullptr);
		auto localTime = *std::localtime(&now);

		std::ostringstream oss;
		oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}

	std::string getLogColor(LogColor color) const {
		switch (color)
		{
		case LogColor::Green:
			return "\033[92m";
		case LogColor::Blue:
			return "\033[94m";
		default:
			return "\033[0m";
		}
	}

	std::string getErrorColor(LogErrorColor color) const {
		switch (color)
		{
		case LogErrorColor::Red:
			return "\033[91m";
		default:
			return "\033[0m";
		}
	}
};


class FileLogger : public ILogger { // <----
public:
	FileLogger(bool addTimestamp = false)
		: addTimestamp(addTimestamp)
	{

	}

	ILogger* clone() const override {  // <----
		return new FileLogger(*this);
	}

	void Log(const std::string& message) const override {
		std::ofstream out("logs.txt", std::ios::app);
		if (!out) {
			return;
		}

		try {
			if (addTimestamp) {
				out << "[inf] " << getCurrentTimestamp() << " : " << message << std::endl;
			}
			else {
				out << "[inf] : " << message << std::endl;
			}
		}
		catch (...) {
			out.close();
		}

		out.close();
	}

	void LogError(const std::string& message) const override {
		std::ofstream out("logs.txt", std::ios::app);
		if (!out) {
			return;
		}

		try {
			if (addTimestamp) {
				out << "[err] " << getCurrentTimestamp() << " : " << message << std::endl;
			}
			else {
				out << "[err] : " << message << std::endl;
			}
		}
		catch (...) {
			out.close();
		}

		out.close();
	}
private:
	bool addTimestamp;

	std::string getCurrentTimestamp() const {
		auto now = std::time(nullptr);
		auto localTime = *std::localtime(&now);

		std::ostringstream oss;
		oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}
};

class PaymentProcessor {
public:
	PaymentProcessor(ILogger* logger) : logger(logger) // <----
	{
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
		try {
			logger->Log("Starting payment processing...");
			int result = pay();
			logger->Log("Payment processed successfully! Result: " + std::to_string(result));
		}
		catch (const std::exception& e) {
			std::string err = e.what();
			logger->LogError("Payment processing failed: " + err);
		}
	}

private:
	ILogger* logger;
};

int main() {
	std::srand(std::time(0));

	PaymentProcessor processor1(new Logger(true)); // <----
	PaymentProcessor processor2(new FileLogger(true)); // <----
	for (int i = 0; i < 10; i++)
	{
		processor1.processPayment();
		std::cout << std::endl;
	}

	for (int i = 0; i < 10; i++)
	{
		processor2.processPayment();
		std::cout << std::endl;
	}

	std::cout << "Processing finished." << std::endl;

	return 0;
}
```

## 5. ComplexLogger
Добавете 5 нови функции, които изпълняват плащане. Две от тях да използва конзолния логър, Други две от тях да използва файловия логър, а последната да използва нов клас `ComplexLogger`, който логва едновременно както и във файл-а, така и в конзолата.

Целта на задачата е:
1. Да се види следващото ниво на абстракция, досега разделяхме имплементациите на класовете, нека се опитаме да разделим и създаване им
2. Да се упражни множествено наследяване

```c++

#include <iostream>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>
#include <fstream>

#pragma warning(disable:4996)

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

enum class LogColor {
	Default = 0,
	Green = 1,
	Blue = 2
};

enum class LogErrorColor {
	Default = 0,
	Red = 1
};

class ILogger {
public:
	virtual void Log(const std::string& message) const = 0;
	virtual void LogError(const std::string& message) const = 0;

	virtual ILogger* clone() const = 0;
	virtual ~ILogger() = default;
};

class ConsoleLogger : public virtual ILogger {
public:
	ConsoleLogger(bool addTimestamp = false,
		LogColor logColor = LogColor::Default,
		LogErrorColor errorColor = LogErrorColor::Default)
		: addTimestamp(addTimestamp), logColor(logColor), errorColor(errorColor)
	{

	}

	ILogger* clone() const override {
		return new ConsoleLogger(*this);
	}

	void Log(const std::string& message) const override {
		std::cout << getLogColor(this->logColor);

		if (addTimestamp) {
			std::cout << "[inf] " << getCurrentTimestamp() << " : " << message << std::endl;
		}
		else {
			std::cout << "[inf] : " << message << std::endl;
		}

		// Revert console color to white.
		std::cout << "\033[0m";
	}

	void LogError(const std::string& message) const override {
		std::cerr << getErrorColor(this->errorColor);

		if (addTimestamp) {
			std::cerr << "[err] " << getCurrentTimestamp() << " : " << message << std::endl;
		}
		else {
			std::cerr << "[err] : " << message << std::endl;
		}

		// Revert console color to white.
		std::cerr << "\033[0m";
	}

private:
	bool addTimestamp;
	LogColor logColor;
	LogErrorColor errorColor;

	std::string getCurrentTimestamp() const {
		auto now = std::time(nullptr);
		auto localTime = *std::localtime(&now);

		std::ostringstream oss;
		oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}

	std::string getLogColor(LogColor color) const {
		switch (color)
		{
		case LogColor::Green:
			return "\033[92m";
		case LogColor::Blue:
			return "\033[94m";
		default:
			return "\033[0m";
		}
	}

	std::string getErrorColor(LogErrorColor color) const {
		switch (color)
		{
		case LogErrorColor::Red:
			return "\033[91m";
		default:
			return "\033[0m";
		}
	}
};


class FileLogger : public virtual ILogger { 
public:
	FileLogger(bool addTimestamp = false)
		: addTimestamp(addTimestamp)
	{

	}

	ILogger* clone() const override {
		return new FileLogger(*this);
	}

	void Log(const std::string& message) const override {
		std::ofstream out("logs.txt", std::ios::app);
		if (!out) {
			return;
		}

		try {
			if (addTimestamp) {
				out << "[inf] " << getCurrentTimestamp() << " : " << message << std::endl;
			}
			else {
				out << "[inf] : " << message << std::endl;
			}
		}
		catch (...) {
			out.close();
		}

		out.close();
	}

	void LogError(const std::string& message) const override {
		std::ofstream out("logs.txt", std::ios::app);
		if (!out) {
			return;
		}

		try {
			if (addTimestamp) {
				out << "[err] " << getCurrentTimestamp() << " : " << message << std::endl;
			}
			else {
				out << "[err] : " << message << std::endl;
			}
		}
		catch (...) {
			out.close();
		}

		out.close();
	}
private:
	bool addTimestamp;

	std::string getCurrentTimestamp() const {
		auto now = std::time(nullptr);
		auto localTime = *std::localtime(&now);

		std::ostringstream oss;
		oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}
};

class ComplexLogger : public FileLogger, public ConsoleLogger {
public:
	ComplexLogger(bool addTimestamp = false,
		LogColor logColor = LogColor::Default,
		LogErrorColor errorColor = LogErrorColor::Default) :
		ConsoleLogger(addTimestamp, logColor, errorColor), FileLogger(addTimestamp)
	{
	}

	void Log(const std::string& message) const override {
		FileLogger::Log(message);
		ConsoleLogger::Log(message);
	}

	void LogError(const std::string& message) const override {
		FileLogger::LogError(message);
		ConsoleLogger::LogError(message);
	}

	ILogger* clone() const override {
		return new ComplexLogger(*this);
	}
};

class PaymentProcessor {
public:
	PaymentProcessor(ILogger* logger) : logger(logger) 
	{
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
		try {
			logger->Log("Starting payment processing...");
			int result = pay();
			logger->Log("Payment processed successfully! Result: " + std::to_string(result));
		}
		catch (const std::exception& e) {
			std::string err = e.what();
			logger->LogError("Payment processing failed: " + err);
		}
	}

private:
	ILogger* logger;
};

void process1(int repeats) {
	PaymentProcessor processor(new ConsoleLogger(true, LogColor::Green, LogErrorColor::Red));

	for (int i = 0; i < repeats; i++)
	{
		processor.processPayment();
		std::cout << std::endl;
	}
}

void process2(int repeats) {
	PaymentProcessor processor(new ConsoleLogger(true, LogColor::Blue, LogErrorColor::Default));

	for (int i = 0; i < repeats; i++)
	{
		processor.processPayment();
		std::cout << std::endl;
	}
}


void process3(int repeats) {
	PaymentProcessor processor(new FileLogger());

	for (int i = 0; i < repeats; i++)
	{
		processor.processPayment();
		std::cout <<"Process payment logged in file." << std::endl;
	}
}


void process4(int repeats) {
	PaymentProcessor processor(new FileLogger(true));

	for (int i = 0; i < repeats; i++)
	{
		processor.processPayment();
		std::cout << "Process payment logged in file." << std::endl;
	}
}

void process5(int repeats) {
	PaymentProcessor processor(new ComplexLogger(true, LogColor::Green, LogErrorColor::Red));

	for (int i = 0; i < repeats; i++)
	{
		processor.processPayment();
		std::cout << std::endl;
	}
}

int main() {
	std::srand(std::time(0));

	int repeat = 4;
	process1(repeat);
	process2(repeat);
	process3(repeat);
	process4(repeat);
	process5(repeat);

	std::cout << "Processing finished." << std::endl;

	return 0;
}
```

Можем да видим как използваме множествено наследяване за `ComplexLogger`.

### Потенциални проблеми
Целта на различните `processN` методи е да покажат, че може на много места да използваме логъри, и то различни, реално се случва да инициализираме дадени данни на десетки или стотици места в нашия код, когато проектите са по-големи. В тези случай бихме изкали да имаме начин за централно създаване и променяне на конфигурацията за подразбиране.

Всеки един от наследяващите класове има свой конструктор, в случая тези конструктори имат стойности по подразбиране за параметрите, но какво ако в нашата система искаме стойностите по подразбиране да са други?

Можем да използваме `factory pattern`, за да създаваме различни логъри:

```c++

enum class LoggerType {
	Console = 0,
	File = 1,
	Complex = 2
};

class LoggerFactory {
public:
	static ILogger* createLogger(LoggerType type) {
		switch (type)
		{
		case LoggerType::Console:
			return new ConsoleLogger(true, LogColor::Green, LogErrorColor::Red);
		case LoggerType::File:
			return new FileLogger(true);
		case LoggerType::Complex:
			return new ComplexLogger(true, LogColor::Green, LogErrorColor::Red);
		default:
			return nullptr;
		}
	}
};
```

Целият код:

```c++
#include <iostream>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>
#include <fstream>

#pragma warning(disable:4996)

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

enum class LogColor {
	Default = 0,
	Green = 1,
	Blue = 2
};

enum class LogErrorColor {
	Default = 0,
	Red = 1
};

class ILogger {
public:
	virtual void Log(const std::string& message) const = 0;
	virtual void LogError(const std::string& message) const = 0;

	virtual ILogger* clone() const = 0;
	virtual ~ILogger() = default;
};

class ConsoleLogger : public virtual ILogger {
public:
	ConsoleLogger(bool addTimestamp = false,
		LogColor logColor = LogColor::Default,
		LogErrorColor errorColor = LogErrorColor::Default)
		: addTimestamp(addTimestamp), logColor(logColor), errorColor(errorColor)
	{

	}

	ILogger* clone() const override {
		return new ConsoleLogger(*this);
	}

	void Log(const std::string& message) const override {
		std::cout << getLogColor(this->logColor);

		if (addTimestamp) {
			std::cout << "[inf] " << getCurrentTimestamp() << " : " << message << std::endl;
		}
		else {
			std::cout << "[inf] : " << message << std::endl;
		}

		// Revert console color to white.
		std::cout << "\033[0m";
	}

	void LogError(const std::string& message) const override {
		std::cerr << getErrorColor(this->errorColor);

		if (addTimestamp) {
			std::cerr << "[err] " << getCurrentTimestamp() << " : " << message << std::endl;
		}
		else {
			std::cerr << "[err] : " << message << std::endl;
		}

		// Revert console color to white.
		std::cerr << "\033[0m";
	}

private:
	bool addTimestamp;
	LogColor logColor;
	LogErrorColor errorColor;

	std::string getCurrentTimestamp() const {
		auto now = std::time(nullptr);
		auto localTime = *std::localtime(&now);

		std::ostringstream oss;
		oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}

	std::string getLogColor(LogColor color) const {
		switch (color)
		{
		case LogColor::Green:
			return "\033[92m";
		case LogColor::Blue:
			return "\033[94m";
		default:
			return "\033[0m";
		}
	}

	std::string getErrorColor(LogErrorColor color) const {
		switch (color)
		{
		case LogErrorColor::Red:
			return "\033[91m";
		default:
			return "\033[0m";
		}
	}
};


class FileLogger : public virtual ILogger {
public:
	FileLogger(bool addTimestamp = false)
		: addTimestamp(addTimestamp)
	{

	}

	ILogger* clone() const override {
		return new FileLogger(*this);
	}

	void Log(const std::string& message) const override {
		std::ofstream out("logs.txt", std::ios::app);
		if (!out) {
			return;
		}

		try {
			if (addTimestamp) {
				out << "[inf] " << getCurrentTimestamp() << " : " << message << std::endl;
			}
			else {
				out << "[inf] : " << message << std::endl;
			}
		}
		catch (...) {
			out.close();
		}

		out.close();
	}

	void LogError(const std::string& message) const override {
		std::ofstream out("logs.txt", std::ios::app);
		if (!out) {
			return;
		}

		try {
			if (addTimestamp) {
				out << "[err] " << getCurrentTimestamp() << " : " << message << std::endl;
			}
			else {
				out << "[err] : " << message << std::endl;
			}
		}
		catch (...) {
			out.close();
		}

		out.close();
	}
private:
	bool addTimestamp;

	std::string getCurrentTimestamp() const {
		auto now = std::time(nullptr);
		auto localTime = *std::localtime(&now);

		std::ostringstream oss;
		oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}
};

class ComplexLogger : public  FileLogger, public  ConsoleLogger {
public:
	ComplexLogger(bool addTimestamp = false,
		LogColor logColor = LogColor::Default,
		LogErrorColor errorColor = LogErrorColor::Default) :
		ConsoleLogger(addTimestamp, logColor, errorColor), FileLogger(addTimestamp)
	{
	}

	void Log(const std::string& message) const override {
		FileLogger::Log(message);
		ConsoleLogger::Log(message);
	}

	void LogError(const std::string& message) const override {
		FileLogger::LogError(message);
		ConsoleLogger::LogError(message);
	}

	ILogger* clone() const override {
		return new ComplexLogger(*this);
	}
};

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
		try {
			logger->Log("Starting payment processing...");
			int result = pay();
			logger->Log("Payment processed successfully! Result: " + std::to_string(result));
		}
		catch (const std::exception& e) {
			std::string err = e.what();
			logger->LogError("Payment processing failed: " + err);
		}
	}

private:
	ILogger* logger;
};


enum class LoggerType {
	Console = 0,
	File = 1,
	Complex = 2
};

class LoggerFactory {
public:
	static ILogger* createLogger(
		LoggerType type = LoggerType::Console,
		bool addTimestamp = true,
		LogColor logColor = LogColor::Green,
		LogErrorColor errorColor = LogErrorColor::Red) {
		switch (type)
		{
		case LoggerType::Console:
			return new ConsoleLogger(addTimestamp, logColor, errorColor);
		case LoggerType::File:
			return new FileLogger(addTimestamp);
		case LoggerType::Complex:
			return new ComplexLogger(addTimestamp, logColor, errorColor);
		default:
			return nullptr;
		}
	}
};


void process1(int repeats) {
	PaymentProcessor processor(new ConsoleLogger(true, LogColor::Green, LogErrorColor::Red));

	for (int i = 0; i < repeats; i++)
	{
		processor.processPayment();
		std::cout << std::endl;
	}
}

void process2(int repeats) {
	PaymentProcessor processor(LoggerFactory::createLogger());

	for (int i = 0; i < repeats; i++)
	{
		processor.processPayment();
		std::cout << std::endl;
	}
}


void process3(int repeats) {
	PaymentProcessor processor(LoggerFactory::createLogger(LoggerType::File, false));

	for (int i = 0; i < repeats; i++)
	{
		processor.processPayment();
		std::cout << "Process payment logged in file." << std::endl;
	}
}


void process4(int repeats) {
	PaymentProcessor processor(LoggerFactory::createLogger(LoggerType::File));

	for (int i = 0; i < repeats; i++)
	{
		processor.processPayment();
		std::cout << "Process payment logged in file." << std::endl;
	}
}

void process5(int repeats) {
	PaymentProcessor processor(LoggerFactory::createLogger(LoggerType::Complex, true, LogColor::Blue, LogErrorColor::Red));

	for (int i = 0; i < repeats; i++)
	{
		processor.processPayment();
		std::cout << std::endl;
	}
}

int main() {
	std::srand(std::time(0));

	int repeat = 4;
	process1(repeat);
	process2(repeat);
	process3(repeat);
	process4(repeat);
	process5(repeat);

	std::cout << "Processing finished." << std::endl;

	return 0;
}
```

Логиката за създаване на логери вече е преместена във фабриката за логери. Този вид фабрика (с тези параметри) има смисъл само когато конструкторите на всички класове се припокриват, както е в текущия случай. Ако имаме логер, който изисква параметри, напълно различни от текущите, ще са необходими други подходи. LoggerFactory е наистина полезна, когато не знаем типа на обекта, който ще създаваме по време на компилация, а по-скоро го знаем по време на изпълнение, например когато потребителят го предоставя, когато го четем от файл и т.н.

Все пак, този пример показва как сега можем да променим стойността по подразбиране за логера в цялото приложение на едно място - метода `createLogger`.


---

# Финална версия (applied best practices)
TODO: Upload separated in files and add explanations