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

	// 1. In case where allocation fails, return nullptr, is that okay?
	try {
		size_t length = strlen(source) + 1;
		char* destination = new char[length];

		strcpy_s(destination, length, source);

		return destination;
	}
	catch (...) {
		return nullptr;
	}
}

// 2. Use "pass by reference", otherwise nullptr assigment is done to the copied parameter.
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
	}

	Book(const char* title, const char* author, int publishYear) : title(nullptr), author(nullptr)
	{
		// 3. For parameterized constructor include setPublishYear as it has validation?
		if (!setTitle(title) || !setAuthor(author) || !setPublishYear(publishYear)) {
			clear();
			// 4. Throw to indicate allocation fail? Do I pass message? A generic one?
			throw;
		}
	}

	Book(const Book& other) {
		// 5. For copy constructor, do I include setPublishYear? Since other is of type Book, any values to publishYear should be valid.
		if (!setTitle(other.title) || !setAuthor(other.author) || !setPublishYear(other.publishYear)) {
			clear();
			throw;
		}
	}

	Book& operator=(const Book& other) {
		if (this == &other) {
			return *this;
		}

		char* newTitle = nullptr;
		char* newAuthor = nullptr;

		newTitle = deepCopyString(other.title);
		newAuthor = deepCopyString(other.author);

		// 6. deepCopyString failed. Deallocate memory and throw.
		// But other.title or other.author can be nullptr, in that case it has not failed?
		// Do I check in pairs? if(!newTitle && other.title) and then safeDelete + throw?
		if (!newTitle || !newAuthor) {
			safeDeleteCharArray(newTitle);
			safeDeleteCharArray(newAuthor);
			
			throw;
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

	// Return bool if assigment was successful.
	bool setTitle(const char* newTitle) {
		if (newTitle == nullptr || strcmp(newTitle, "") == 0) {
			return false;
		}

		char* temporaryTitle = deepCopyString(newTitle);
		// 7. If temporaryTitle is nullptr, the deep copy failed, return false.
		if (temporaryTitle == nullptr) {
			return false;
		}

		safeDeleteCharArray(this->title);
		title = temporaryTitle;

		return true;
	}

	bool setAuthor(const char* newAuthor) {
		if (newAuthor == nullptr || strcmp(newAuthor, "") == 0) {
			return false;
		}

		char* temporaryAuthor = deepCopyString(newAuthor);
		if (temporaryAuthor == nullptr) {
			return false;
		}

		safeDeleteCharArray(this->author);
		author = temporaryAuthor;

		return true;
	}

	bool setPublishYear(int newPublishYear) {
		// 8. Add method-scoped constants as currently they're not used anywhere else. If they were, make them class-level constants.
		const int MIN_PUBLISH_YEAR = 0;
		const int MAX_PUBLISH_YEAR = 2050;
		if (newPublishYear < MIN_PUBLISH_YEAR || newPublishYear > MAX_PUBLISH_YEAR) {
			return false;
		}

		this->publishYear = newPublishYear;

		return true;
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
	catch (const std::exception& e) {
		cout << "An exception occurred: " << e.what() << endl;
	}
	catch (...) {
		cout << "An unknown exception occurred." << endl;
	}

	return 0;
}
