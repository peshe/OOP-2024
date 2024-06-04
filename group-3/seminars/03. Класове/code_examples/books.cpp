#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;


class Book {
private:
	char* title;
	char* author;
	int publishYear;

public:
	Book() : title(nullptr), author(nullptr), publishYear(0)
	{
	}

	Book(const char* title, const char* author, int publishYear) : title(nullptr), author(nullptr), publishYear(publishYear)
	{
		setTitle(title);
		setAuthor(author);
	}

	Book(const Book& other) : publishYear(other.publishYear) {
		setTitle(other.title);
		setAuthor(other.author);
	}

	Book& operator=(const Book& other) {
		if (this == &other) {
			return *this;
		}

		setTitle(other.title);
		setAuthor(other.author);
		setPublishYear(other.publishYear);

		return *this;
	}

	~Book() {
		delete[] title;
		delete[] author;
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

		delete[] this->title;

		size_t newTitleLength = strlen(newTitle) + 1;
		this->title = new char[newTitleLength];
		strcpy_s(this->title, newTitleLength, newTitle);
	}

	void setAuthor(const char* newAuthor) {
		if (newAuthor == nullptr || strcmp(newAuthor, "") == 0) {
			return;
		}

		delete[] this->author;

		size_t newAuthorLength = strlen(newAuthor) + 1;
		this->author = new char[newAuthorLength];
		strcpy_s(this->author, newAuthorLength, newAuthor);
	}

	void setPublishYear(int newPublishYear) {
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

// Example usage of the Book class. Leaving bookExamples, calls destructors of all objects.
void bookExamples() {
	// 1. Parameterized constructor.
	Book book = Book("Book title", "Book author", 2020);

	// 2. Getters usage example.
	cout << book.getAuthor() << endl << book.getTitle() << endl << book.getPublishYear() << endl;

	// 3. Default constructor.
	Book b;

	// 4. Setter usage example.
	b.setTitle("New title");

	// 5. Method usage example.
	b.printBook();
}

int main() {
	bookExamples();

	return 0;
}