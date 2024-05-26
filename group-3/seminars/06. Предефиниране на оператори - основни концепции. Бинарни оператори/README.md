# Предефиниране на оператори - основни концепции. Бинарни оператори

# Обобщение
Кратко обобщение на темите, които разглеждаме по време на семинара.

### Как предефинираме оператори:
- Операторите могат да бъдат предефинирани като член-функции на класа или като външни функции.
- Член-функциите предефинират оператори за работа с обекти от своя клас.
- Външните функции позволяват предефинирането на оператори за взаимодействие между различни типове.

### Добри практики при предефиниране на оператори:
- **Предефиниране в комплект**: Ако предефинирате един оператор (като `==`), добра практика е да предефинирате и свързаните с него оператори (като `!=`).
- **Преизползване на оператори**: Използвайте вече предефинирани оператори за да имплементирате други. Например, `+` може да се реализира чрез `+=`.
- **Използване на `const`**: Методите, които не модифицират обекта, трябва да бъдат обявени като `const`. Това улеснява разбирането на кода и помага за избягване на грешки.
  
### Кои оператори да бъдат част от класа и кои не:
- **Модифициране на полетата**: Оператори, които трябва да променят състоянието на обекта (като `+=` и `-=`), обикновено се имплементират като член-функции.
- **Симетрия**: Оператори, които се очаква да имат симетрично поведение (като бинарният `+`), често са по-подходящи за реализация като външни функции, за да могат левият и десният операнд да бъдат обработени еднакво.

Запомнете, че целта на предефинирането на оператори е да направите вашите класове по-интуитивни и лесни за използване, не предефинирайте оператори ако няма смисъл или просто е "готино". Класовете ни моделират реалният свят, ако в него има смисъл да сравняваме, събираме и т.н. два обекта от дадени класове, тогава би било смислено да предефинираме тези оператори.

*Кодът от семинара:*

```c++
# define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <chrono>

class Point {
public:

    // Prefix increment operator.
    // When used in an expression, the increased value will be used: 
    // int x = 5; 
    // std::cout << ++x; ---> 6
    // std::cout << x; ---> 6
Point& operator++() {
		x++;
		y++;
		return *this; // Returns a reference to the current object to allow chaining. 
	}

	// Postfix increment operator.
    // When used in an expression, the old value will be used: 
    // int x = 5; 
    // std::cout << x++; ---> 5
    // std::cout << x; ---> 6
    // The int parameter is a dummy to differentiate from the prefix version of the operator.
Point operator++(int) {
    Point temp = Point(*this); // Make a copy of the current object.
    ++(*this); // Use the prefix increment to increment the current object.
    return temp; // Return the copy that holds the original values.
}
private:
	double x;
	double y;
};

class DateTime {
public:
	DateTime()
		: DateTime(1, 1, 1, 0, 0, 0) {}

	DateTime(int year, int month, int day, int hours, int minutes, int seconds)
		: year(year), month(month), day(day), hours(hours), minutes(minutes), seconds(seconds) {}

	DateTime(const char* formattedString) {
		int updateVariablesCount = sscanf(formattedString, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hours, &minutes, &seconds);
		const int expectedVariablesReadCount = 6;

		if (updateVariablesCount != expectedVariablesReadCount) {
			throw std::invalid_argument("Date time format is invalid. Please enter a date in the following format: YYYY-MM-DD HH:MM:SS");
		}
	}

	char* toString() {
		char* datetime = new char[21];
		sprintf(datetime, "%04d-%02d-%02d %02d:%02d:%02d", year, month, day, hours, minutes, seconds);

		return datetime;
	}

	friend std::ostream& operator<<(std::ostream& out, const  DateTime& datetime);

    
	bool operator==(const DateTime& other) const {
		return year == other.year
			&& month == other.month
			&& day == other.day
			&& hours == other.hours
			&& minutes == other.minutes
			&& seconds == other.seconds;
	}

	bool operator!=(const DateTime& other) const {
		return !(*this == other);
	}

	bool operator<(const DateTime& other) const {
		if (year != other.year) {
			return year < other.year;
		}

		if (month != other.month) {
			return month < other.month;
		}

		if (day != other.day) {
			return day < other.day;
		}

		if (hours != other.hours) {
			return hours < other.hours;
		}

		if (minutes != other.minutes) {
			return minutes < other.minutes;
		}

		return seconds < other.seconds;
	}

	bool operator>(const DateTime& other) const {
		return other < *this;
	}

	bool operator<=(const DateTime& other) const {
		return !(*this > other);
	}

	bool operator>=(const DateTime& other) const {
		return !(*this < other);
	}

    // operator+= is a member operator as it changes the fields. operator+ is outside the class and reuses it.
	DateTime& operator+=(int seconds) {
		int extraMinutes = seconds / 60;
		seconds = seconds % 60;

		this->seconds += seconds;
		if (this->seconds >= 60) {
			this->seconds -= 60;
			extraMinutes++;
		}

		int extraHours = extraMinutes / 60;
		minutes = extraMinutes % 60;
		this->minutes += minutes;
		if (this->minutes >= 60) {
			this->minutes -= 60;
			extraHours++;
		}

		int extraDays = extraHours / 24;
		hours = extraHours % 24;
		this->hours += hours;
		if (this->hours >= 24) {
			this->hours -= 24;
			extraDays++;
		}

		day += extraDays;
		while (true) {
			int daysInMonth = 31;

			if (month == 2) {
				if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
					daysInMonth = 29;
				}
				else {
					daysInMonth = 28;
				}
			}
			else if (month == 4 || month == 6 || month == 9 || month == 11) {
				daysInMonth = 30;
			}

			if (day > daysInMonth) {
				day -= daysInMonth;
				month++;
				if (month > 12) {
					month = 1;
					year++;
				}
			}
			else {
				break;
			}
		}

		return *this;
	}

    // With good implementation of operator+=, it's possible to implement operator-= like this. Of course this depends on the class and use case.
    // In the case of DateTime, this is incorrect as the implementation of operator+= doesn't handle negative values well. 
    // This is here only for completeness, it's incorrect.
	DateTime& operator-=(int seconds) {
		*this += -seconds;
	}

    // As the author of the class, I've made the decision to provide a minimum and maximum values for my DateTime class. 
    // Next steps would incude making sure all my constructors do not create DateTime object with values higher or lower.
    // One solution would be to use the maximum values in cases when they overflow or throw an exception.
	static DateTime min() {
		return DateTime(1, 1, 1, 0, 0, 0); // The minimum value for my DateTime class is January 1, year 1, 00:00:00 A.D.
	}

	static DateTime max() {
		return DateTime(9999, 12, 31, 23, 59, 59); // The maximum value is the last seconds of year 9999 in the Gregorian Calendar.
	}

    // static method that returns the current DateTime.
    // Not complete as it doesn't take into consideration timezones among other things.
    // Good as an example, do not use this at work.
	static DateTime now() {
		using namespace std::chrono;
		auto now = system_clock::now();
		auto now_c = system_clock::to_time_t(now);
		auto parts = localtime(&now_c);

		return DateTime(parts->tm_year + 1900, parts->tm_mon + 1, parts->tm_mday,
			parts->tm_hour, parts->tm_min, parts->tm_sec);
	}

private:
	int year;
	int month;
	int day;
	int hours;
	int minutes;
	int seconds;
};

DateTime operator+(DateTime first, int seconds) {
	return first += seconds;
}

// operator<< is declared as a friend to the DateTime class. Meaning it has access to the private fields of the class but it can (and should) be defined outside the class.
std::ostream& operator<<(std::ostream& out, const  DateTime& datetime)
{
	if (datetime.year < 10) out << "000";
	else if (datetime.year < 100) out << "00";
	else if (datetime.year < 1000) out << "0";

	out << datetime.year << "-"
		<< (datetime.month < 10 ? "0" : "") << datetime.month << "-"
		<< (datetime.day < 10 ? "0" : "") << datetime.day << " "
		<< (datetime.hours < 10 ? "0" : "") << datetime.hours << ":"
		<< (datetime.minutes < 10 ? "0" : "") << datetime.minutes << ":"
		<< (datetime.seconds < 10 ? "0" : "") << datetime.seconds;

	return out;
}

int main()
{
	DateTime date = DateTime::min();
	DateTime other(date);
	date += 3600;
	std::cout << date << std::endl;
	std::cout << other << std::endl;

	char* dateString = other.toString();
	std::cout << dateString << std::endl;

	DateTime dateFromString("1997-04-03 19:50:27");
	std::cout << dateFromString << std::endl;
	std::cout << date << std::endl;
	std::cout << other << std::endl;
	std::cout << DateTime::now() << std::endl;
	std::cout << DateTime::min() << std::endl;
	std::cout << DateTime::max() << std::endl;
	std::cout << "Is " << date << " equals to " << other << "? " << std::boolalpha << (date == other) << std::endl;
	std::cout << "Is " << date << " not equals to " << other << "? " << std::boolalpha << (date != other) << std::endl;
	std::cout << "Is " << date << " greater than " << other << "? " << std::boolalpha << (date > other) << std::endl;
	std::cout << "Is " << date << " greater or equals to " << other << "? " << std::boolalpha << (date >= other) << std::endl;
	std::cout << "Is " << date << " less than " << other << "? " << std::boolalpha << (date < other) << std::endl;
	std::cout << "Is " << date << " less or equals to" << other << "? " << std::boolalpha << (date <= other) << std::endl;

	delete[] dateString;
}

```