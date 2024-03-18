#include <iostream>
#include <cstring>
#include <exception>

using std::cin;
using std::cout;
using std::endl;

char* deepCopyString(const char* source) {
	if (source == nullptr) {
		return nullptr;
	}

	size_t length = strlen(source) + 1;
	char* destination = new char[length];

	strcpy_s(destination, length, source);

	return destination;
}

class Book {
private:
	char* title;
	char* author;
	int publishYear;

	void safeDeleteTitle() {
		delete[] title;
		title = nullptr;
	}

	void safeDeleteAuthor() {
		delete[] author;
		author = nullptr;
	}

public:
	Book() : title(nullptr), author(nullptr), publishYear(0)
	{
	}

	Book(const char* title, const char* author, int publishYear) : title(nullptr), author(nullptr), publishYear(publishYear)
	{
		try {
			setTitle(title);
			setAuthor(author);
		}
		catch (...) {
			safeDeleteTitle();
			throw;
		}
	}

	Book(const Book& other) : publishYear(other.publishYear) {
		try {
			setTitle(other.title);
			setAuthor(other.author);
		}
		catch (...) {
			safeDeleteTitle();
			throw;
		}
	}

	Book& operator=(const Book& other) {
		if (this == &other) {
			return *this;
		}

		char* newTitle = nullptr;
		char* newAuthor = nullptr;

		try {
			if (other.title) {
				newTitle = deepCopyString(other.title);
			}

			if (other.author) {
				newAuthor = deepCopyString(other.author);
			}
		}
		catch (...) {
			delete[] newTitle;
			delete[] newAuthor;
			throw;
		}

		safeDeleteTitle();
		safeDeleteAuthor();

		this->title = newTitle;
		this->author = newAuthor;
		this->publishYear = other.publishYear;

		return *this;
	}

	~Book() {
		safeDeleteTitle();
		safeDeleteAuthor();
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
			return;
		}

		char* temporaryTitle = deepCopyString(newTitle);
		safeDeleteTitle();

		title = temporaryTitle;
	}

	void setAuthor(const char* newAuthor) {
		if (newAuthor == nullptr || strcmp(newAuthor, "") == 0) {
			return;
		}

		char* temporaryAuthor = deepCopyString(newAuthor);
		safeDeleteAuthor();

		author = temporaryAuthor;
	}

	void setPublishYear(int newPublishYear) {
		if (newPublishYear < 0 || newPublishYear > 2050) {
			return;
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
		// 1. Attempt to construct a Book object with the parameterized constructor.
		Book book("Book title", "Book author", 2020);

		// 2. Getters usage example.
		cout << book.getAuthor() << endl << book.getTitle() << endl << book.getPublishYear() << endl;

		// 3. Default constructor and setter usage.
		Book b;
		b.setTitle("New title");

		// 4. Method usage example.
		b.printBook();
	}
	catch (const std::exception& e) {
		// Handle standard exceptions
		cout << "An exception occurred: " << e.what() << endl;
	}
	catch (...) {
		// Handle all other exceptions
		cout << "An unknown exception occurred." << endl;
	}

	return 0;
}
