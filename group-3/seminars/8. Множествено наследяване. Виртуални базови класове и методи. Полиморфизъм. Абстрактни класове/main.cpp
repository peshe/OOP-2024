#include <iostream>
#include <fstream>

void clearConsoleInputStream() {
	using namespace std;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
{
	using namespace std;
	
	std::string filename;
	cout << "Please enter filename containing budget and employee information: ";
	cin >> filename;
	cout << endl;

	if (filename.empty() || filename.find(".txt") == string::npos) {
		cerr << "Filename '" << filename << "' is invalid. Please use a text file." << endl;

		return 1;
	}

	ifstream data;
	data.exceptions(ifstream::failbit | ifstream::badbit);

	try {
		data.open(filename);
	}
	catch (system_error& e) {
		cerr << "Failed to open file: " << e.code().message() << endl;

		return 1;
	}

	cout << "Welcome to the Salary Payment Report Application. Please select an option below." << endl;
	while (true) {
		int userChoice;
		cout << "1. Log additional working hours for employee." << endl;
		cout << "2. Generate Salary Report." << endl;
		cout << "3. Exit." << endl;
		
		cout << endl << "> ";
		cin >> userChoice;
		clearConsoleInputStream();

		switch (userChoice)
		{
		case 1: 
			cout << "> Case 1" << endl; 
			break;
		case 2: 
			cout << "> Case 2" << endl; 
			break;
		case 3: 
			cout << "> Case 3. Terminating" << endl; 
			return 0;

		default:
			cerr << "> Unrecognizable command. Please select a command from below." << endl;
		}
	}
	return 0;
}
