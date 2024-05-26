#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <string>

const double EPSILON = 0.001;

class Person {
public:

	Person(std::ifstream& input)
	{
		std::getline(input, name);
		if (!input) {
			throw std::runtime_error("Coudln't read name of an employee.");
		}

		std::getline(input, summary);
		if (!input) {
			throw std::runtime_error("Coudln't read summary of an employee.");
		}
	}

	virtual void generateSalaryReport() const {
		using namespace std;
		cout << "Name: " << name << endl;
		cout << "Summary: " << summary << endl;
	}

	virtual double calculateSalary() const = 0;
	virtual ~Person() = default;

protected:
	std::string name;
	std::string summary;
};

class Contractor :public virtual Person {
public:
	Contractor(std::ifstream& input) : Person(input)
	{
		input >> hourlyRateInEuro;
		if (!input) {
			throw std::runtime_error("Couldn't read hourly rate of a contractor.");
		}

		input >> hoursWorkedSinceLastPayment;
		if (!input) {
			throw std::runtime_error("Couldn't read hours worked of a contractor.");
		}

		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	double calculateSalary() const override {
		return hoursWorkedSinceLastPayment * hourlyRateInEuro;
	}

	void generateSalaryReport() const {
		using namespace std;
		Person::generateSalaryReport();
		cout << "Hourly rate: $" << hourlyRateInEuro << endl;
		cout << "Hours worked: $" << hoursWorkedSinceLastPayment << endl;
		cout << "Salary paid: $" << calculateSalary() << endl;
		cout << "=========================================" << endl;
	}
protected:
	double hourlyRateInEuro;
	int hoursWorkedSinceLastPayment;
};

class Employee :public virtual Person {
public:
	Employee(std::ifstream& input) : Person(input)
	{
		input >> monthlySalaryInEuro;
		if (!input) {
			throw std::runtime_error("Couldn't read monthly salary of an employee.");
		}

		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (monthlySalaryInEuro < 0) {
			throw std::invalid_argument("Monthly salary is a negative value. Please provide a positive value");
		}
	}

	double calculateSalary() const override {
		return monthlySalaryInEuro;
	}

	void generateSalaryReport() const {
		using namespace std;
		Person::generateSalaryReport();
		cout << "Monthly salary: $" << monthlySalaryInEuro << endl;
		cout << "Salary paid: $" << monthlySalaryInEuro << endl;
		cout << "=========================================" << endl;
	}
protected:
	double monthlySalaryInEuro;
};

class HybridEmployee : public virtual Employee, public virtual Contractor {
public:

	void generateSalaryReport() const override {
		using namespace std;
		Person::generateSalaryReport();
		cout << "Monthly salary: $" << monthlySalaryInEuro << endl;
		cout << "Hourly rate: $" << hourlyRateInEuro << endl;
		cout << "Hours worked: $" << hoursWorkedSinceLastPayment << endl;

		cout << "Salary paid: $" << calculateSalary() << endl;
		cout << "=========================================" << endl;
	}

	double calculateSalary() const override {
		return Employee::calculateSalary() + Contractor::calculateSalary();
	}

	HybridEmployee(std::ifstream& input) :Person(input), Employee(input), Contractor(input)
	{

	}
};

class Company {
public:
	Company() = default;
	Company(double budget, std::vector<Person*> employees) : budget(budget), employees(employees)
	{
		//  todo: validation
	}
	void generateSalaryReport() {
		double monthlySalariesAmountInEuro = 0;

		for (const Person* personPtr : employees) {
			monthlySalariesAmountInEuro += (*personPtr).calculateSalary();
		}

		if (budget - monthlySalariesAmountInEuro < 0) {
			std::cout << "Total budget: $" << budget << ". Salary amount: $" << monthlySalariesAmountInEuro << ". $"
				<< monthlySalariesAmountInEuro - budget << " needed to pay salaries." << std::endl;
		}
		else {
			std::cout << "Total budget: $" << budget << ". Salary amount: $" << monthlySalariesAmountInEuro << ". $"
				<< budget - monthlySalariesAmountInEuro << " left in the treasury." << std::endl;
		}

		std::cout << std::endl;
		for (const Person* personPtr : employees) {
			(*personPtr).generateSalaryReport();
			std::cout << std::endl;
		}

	}
private:
	double budget;
	std::vector<Person*> employees;
};

class PersonFactory {
public:
	static Person* createPerson(std::ifstream& input) {
		char personType;
		input >> personType;
		if (personType == 'E') {
			return new Employee(input);
		}
		else if (personType == 'C') {
			return new Contractor(input);
		}
		else if (personType == 'H') {
			return new HybridEmployee(input);
		}

		return nullptr;
	}
};

class Application {
public:

	void run() {
		using namespace std;

		std::string filename;
		cout << "Please enter filename containing budget and employee information: ";
		cin >> filename;
		cout << endl;

		if (filename.empty() || filename.find(".txt") == string::npos) {
			throw runtime_error("Filename '" + filename + "' is invalid. Please use a text file.");
		}

		ifstream data(filename);

		if (!data) {
			throw runtime_error("Couldn't open file");
		}

		double budget;
		std::vector<Person*> employees;
		data >> budget;
		if (budget < 0) {
			throw runtime_error("Budget cannot be negative");
		}
		data.ignore();
		while (data) {
			try {
				Person* person = PersonFactory::createPerson(data);

				if (!person) {
					throw runtime_error("Could'nt create person");
				}
				employees.push_back(person);


			}
			catch (const std::invalid_argument& e) {
				data.close();
				std::string err = e.what();
				throw std::runtime_error("Couldn't read employee data from file. " + err);
			}
			catch (const std::runtime_error& e) {
				data.close();
				std::string err = e.what();
				throw std::runtime_error("Couldn't read employee data from file. " + err);
			}
		}

		company = Company(budget, employees);
		showMenu();
	}
private:
	Company company;

	void showMenu() {
		using namespace std;

		cout << "Welcome to the Salary Payment Report Application. Please select an option below." << endl;
		while (true) {
			int userChoice;
			cout << "1. Log additional working hours for employee." << endl;
			cout << "2. Generate Salary Report." << endl;
			cout << "3. Exit." << endl;

			cout << endl << "> ";
			cin >> userChoice;
			cin.ignore();

			switch (userChoice)
			{
			case 1:
				cout << "> Case 1" << endl;
				break;
			case 2:
				cout << "> Generating salary report..." << endl;
				generateSalaryReport();
				break;
			case 3:
				cout << "> Case 3. Terminating" << endl;
				return;

			default:
				cerr << "> Unrecognizable command. Please select a command from below." << endl;
			}
		}
	}

	void generateSalaryReport() {
		company.generateSalaryReport();
	}
};

void clearConsoleInputStream() {
	using namespace std;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
{
	try {
		Application app;
		app.run();
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Critical error occurred. " << e.what() << std::endl;
		std::cerr << "Terminating application..." << std::endl;

		return 1;
	}
	catch (const std::exception& e) {

	}

	return 0;
}
