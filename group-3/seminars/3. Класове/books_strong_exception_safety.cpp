#include <iostream>
#include <cstring>
#include <exception>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

char* deepCopyString(const char* source) {
	if (source == nullptr) {
		return nullptr;
	}

	// 1. Update: use nothrow and return nullptr if allocation fails.
	size_t length = strlen(source) + 1;
	char* destination = new(std::nothrow) char[length];
	if (!destination) {
		return nullptr;
	}

	strcpy_s(destination, length, source);

	return destination;
}

void safeDeleteCharArray(char*& charArray) {
	delete[] charArray;
	charArray = nullptr;
}

class Book {
private:
	char* title;
	char* author;
	int publishYear;

	void clear() {
		safeDeleteCharArray(this->title);
		safeDeleteCharArray(this->author);
	}

public:
	Book() : title(nullptr), author(nullptr), publishYear(0)
	{
		// 2. nullptr is now invalid value for the fields of my book class, including the default constructor.
		// By default set the following values below. Throw from setters and clear in construction situations.
		try {
			setTitle("No title set.");
			setAuthor("No author set.");
		}
		catch (std::bad_alloc& e) {
			clear();
			throw;
		}
	}

	Book(const char* title, const char* author, int publishYear) : title(nullptr), author(nullptr), publishYear(0)
	{
		try {
			setTitle(title);
			setAuthor(author);

			// 3. As the previous operations might fail, isn't it better to initialize publishYear to 0 using initializer list in the constructor?
			// Or this doesn't matter as the object we're trying to create is destroyed as it's invalid.
			setPublishYear(publishYear);
		}
		catch (std::bad_alloc& e) {
			clear();
			throw;
		}
	}

	Book(const Book& other) {
		try {
			setTitle(other.title);
			setAuthor(other.author);

			// 4. Move the setting of publish year last, removed from init list as if allocation operations fail, we don't want partial update.
			setPublishYear(other.publishYear);
		}
		catch (std::bad_alloc& e) {
			clear();
			throw;
		}
	}

	Book& operator=(const Book& other) {
		if (this == &other) {
			return *this;
		}

		char* newTitle = deepCopyString(other.title);
		char* newAuthor = deepCopyString(other.author);

		// 5. Valid code title and author now cannot be nullptr, there's no constructor that allows it.
		if (!newTitle || !newAuthor) {
			safeDeleteCharArray(newTitle);
			safeDeleteCharArray(newAuthor);

			throw std::bad_alloc();
		}

		clear();

		this->title = newTitle;
		this->author = newAuthor;
		this->publishYear = other.publishYear;

		return *this;
	}

	~Book() {
		clear();
	}

	const char* getAuthor() const {
		return author;
	}

	const char* getTitle() const {
		return title;
	}

	int getPublishYear() const {
		return publishYear;
	}

	void setTitle(const char* newTitle) {
		if (newTitle == nullptr || strcmp(newTitle, "") == 0) {
			// 6. Update: throw invalid argument exception for all validation related errors.
			throw std::invalid_argument("Title cannot be null or empty.");
		}

		char* temporaryTitle = deepCopyString(newTitle);
		if (temporaryTitle == nullptr) {
			// 7. Update: throw bad_alloc exception for all allocation fails.
			throw std::bad_alloc();
		}

		safeDeleteCharArray(this->title);
		title = temporaryTitle;
	}

	void setAuthor(const char* newAuthor) {
		if (newAuthor == nullptr || strcmp(newAuthor, "") == 0) {
			throw std::invalid_argument("Author cannot be null or empty.");
		}

		char* temporaryAuthor = deepCopyString(newAuthor);
		if (temporaryAuthor == nullptr) {
			throw std::bad_alloc();
		}

		safeDeleteCharArray(this->author);
		author = temporaryAuthor;
	}

	void setPublishYear(int newPublishYear) {
		const int MIN_PUBLISH_YEAR = 0;
		const int MAX_PUBLISH_YEAR = 2050;
		if (newPublishYear < MIN_PUBLISH_YEAR || newPublishYear > MAX_PUBLISH_YEAR) {
			throw std::invalid_argument("Publish year should be between 0 and 2050");
		}

		this->publishYear = newPublishYear;
	}

	void printBook() const
	{
		if (title != nullptr) {
			cout << title << endl;
		}
		else {
			cout << "No title set." << endl;
		}

		if (author != nullptr) {
			cout << author << endl;
		}
		else {
			cout << "No author set." << endl;
		}

		cout << publishYear << endl;
	}
};

int main() {
	try {
		Book book("Book title", "Book author", 2020);

		cout << book.getAuthor() << endl << book.getTitle() << endl << book.getPublishYear() << endl;

		Book b;
		b.setTitle("New title");

		b.printBook();

		b = book;
	}
	// 7. Handle invalid arguments exceptions.
	catch (const std::invalid_argument& e) {
		cerr << "Invalid argument. " << e.what() << endl;
	}
	// 8. Handle bad allocation exceptions.
	catch (const std::bad_alloc& e) {
		cerr << "Dynamic memory allocation failed. " << e.what() << endl;
	}
	// 9. Handle generic exceptions.
	catch (const std::exception& e) {
		cerr << "An exception occurred: " << e.what() << endl;
	}
	catch (...) {
		cerr << "An unknown exception occurred." << endl;
	}

	return 0;
}
