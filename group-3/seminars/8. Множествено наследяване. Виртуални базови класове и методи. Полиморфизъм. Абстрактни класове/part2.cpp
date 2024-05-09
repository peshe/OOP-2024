#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <string>

class Employee {
public:
	Employee(std::ifstream& input) {
		if (!input) {
			// or invalid_argument???
			throw std::runtime_error("Invalid input stream provided.");
		}

		std::getline(input, name);
		if (input.fail()) {
			throw std::runtime_error("Failed to read the name from the input stream.");
		}

		input >> hourlyRateInEuro;
		if (input.fail()) {
			throw std::runtime_error("Failed to read a valid hourly rate from the input stream.");
		}

		input >> hoursWorkedSinceLastPayment;
		if (input.fail()) {
			throw std::runtime_error("Failed to read the hours worked from the input stream.");
		}

		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (name.empty() || name.find_first_not_of(' ') == std::string::npos) {
			throw std::invalid_argument("Name is empty or whitespace.");
		}

		if (hourlyRateInEuro < 0) {
			throw std::invalid_argument("Hourly Rate is negative");
		}

		if (hoursWorkedSinceLastPayment < 0) {
			throw std::invalid_argument("Hours Worked since last payment is negative");
		}
	}
private:
	std::string name;
	double hourlyRateInEuro;
	int hoursWorkedSinceLastPayment;
};

class Company {
public:
	Company() = default;
	Company(double budget, std::vector<Employee> employees) :budget(budget), employees(employees) {
	}
private:
	double budget;
	std::vector<Employee> employees;
};

class Application {
public:
	void run() {
		using namespace std;
		readCompanyDataFromFile();

		cout << endl << "Welcome to the Salary Payment Report Application. Please select an option below." << endl;
		while (true) {
			int userChoice;
			cout << "================================================================================" << endl;
			cout << "1. Log additional working hours for employee." << endl;
			cout << "2. Generate Salary Report." << endl;
			cout << "3. Exit." << endl;

			cout << endl << "> ";
			cin >> userChoice;
			clearConsoleInputStream(cin);

			switch (userChoice)
			{
			case 1:
				cout << "> '1. Log working hours for employee' selected..." << endl;
				logWorkingHoursForEmployee();
				break;
			case 2:
				cout << "> '2. Generate Salary Report' selected..." << endl;
				generateSalaryReport();
				break;
			case 3:
				cout << "> '3. Exit' selected..." << endl;
				cout << "> Terminating... Have a great day!" << endl;
				return;

			default:
				cerr << "> Unrecognizable command. Please select a command from below." << endl;
			}
		}
	}
private:
	Company company;

	void logWorkingHoursForEmployee() {

	}

	void generateSalaryReport() {

	}

	void readCompanyDataFromFile() {
		using namespace std;

		std::string filename;
		cout << "Please enter filename containing budget and employee information: ";
		cin >> filename;

		if (filename.empty() || filename.find(".txt") == string::npos) {
			cerr << "> Filename '" << filename << "' is empty or invalid. Please use a text file (.txt extension is missing)" << endl;

			throw runtime_error("Invalid file name");
		}

		ifstream data(filename);

		if (!data) {
			throw std::runtime_error("Couldn't open file " + filename);
		}

		readCompanyDataFromStream(data);
		std::cout << "> File was read successfully! " << std::endl;
	}

	void readCompanyDataFromStream(std::ifstream& input) {
		double budget;
		input >> budget;
		if (!input) {
			throw std::runtime_error("Couldn't read budget");
		}
		clearConsoleInputStream(input);

		if (budget < 0) {
			throw std::runtime_error("Budget is less than zero. Please provide a file with positive budget");
		}

		std::vector<Employee> employees;
		while (input) {
			try {
				Employee e(input);
				employees.push_back(e);
				//clearConsoleInputStream(input);
			}
			catch (const std::invalid_argument& e) {
				input.close();
				std::string errMsg = e.what();
				throw std::runtime_error("Loading employees failed due to invalid data. " + errMsg);
			}
			catch (const std::runtime_error& e) {
				input.close();
				std::string errMsg = e.what();
				throw std::runtime_error("Loading employees failed due to file format. " + errMsg);
			}
		}

		company = Company(budget, employees);
	}

	void clearConsoleInputStream(std::istream& stream) {
		stream.clear();
		stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};

int main()
{
	try {
		Application app;
		app.run();
	}
	catch (std::runtime_error& e) {
		std::cerr << "> Encountered unresolvable error. " << e.what() << std::endl;
		std::cerr << "> Terminating application..." << std::endl;
	}

	return 0;
}
