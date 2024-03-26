#include <iostream>
#include <cstring>
#include <cassert>

const std::size_t MAX_BOOK_NAME_SIZE = 128;

const std::size_t INITIAL_CAPACITY = 2;
const std::size_t INCREASE_STEP = 2;

class Book
{
private:
    char name[MAX_BOOK_NAME_SIZE];
    int yearOfPublication;

public:
    Book(): Book("", 0) {}

    Book(const char* name, const int yearOfPublication)
        : yearOfPublication(yearOfPublication)
    {
        assert(name != nullptr);

        strcpy(this->name, name);
    }

    const char* getName() const
    {
        return this->name;
    }

    void print() const
    {
        assert(this->name != nullptr);

        std::cout << this->name << ", " << this->yearOfPublication << std::endl;
    }
};

class Library
{
private:
    Book* books;
    std::size_t size;
    std::size_t capacity;

    void deallocate()
    {
        delete[] this->books;
    }

    void copy(const Library& other)
    {
        this->books = new (std::nothrow) Book[other.capacity];
        if (!this->books)
        {
            std::cout << "Memory problem" << std::endl;
            return;
        }

        for (std::size_t i = 0; i < other.size; ++i)
        {
            this->books[i] = other.books[i];
        }

        this->size = other.size;
        this->capacity = other.capacity;
    }

    void resize()
    {
        Book* newBooks = new (std::nothrow) Book[this->capacity * INCREASE_STEP];
        if (!newBooks)
        {
            std::cout << "Memory problem!" << std::endl;
            return;
        }

        for (std::size_t i = 0; i < this->size; ++i)
        {
            newBooks[i] = this->books[i];
        }

        delete[] this->books;
        this->books = newBooks;
        this->capacity *= INCREASE_STEP;
    }

public:
    Library()
    {
        this->books = new (std::nothrow) Book[INITIAL_CAPACITY];
        if (!this->books)
        {
            std::cout << "Memory problem" << std::endl;
            return;
        }

        this->capacity = INITIAL_CAPACITY;
        this->size = 0;
    }

    Library(const Library& other)
    {
        this->copy(other);
    }

    Library& operator = (const Library& other)
    {
        if (this != &other)
        {
            this->deallocate();
            this->copy(other);
        }

        return *this;
    }

    ~Library()
    {
        this->deallocate();
    }

    void addBook(const Book& toAdd)
    {
        if (this->size == this->capacity)
        {
            this->resize();
        }

        this->books[this->size] = toAdd;
        ++this->size;
    }

    bool removeBook(const char* name)
    {
        assert(name != nullptr);

        for (std::size_t i = 0; i < this->size; ++i)
        {
            if (strcmp(name, this->books[i].getName()) == 0)
            {
                this->books[i] = this->books[this->size - 1];
                --this->size;
                return true;
            }
        }

        return false;
    }

    void printInfo()
    {
        std::cout << "SIZE: " << this->size << std::endl;
        std::cout << "CAPACITY: " << this->capacity << std::endl;
        for (std::size_t i = 0; i < this->size; ++i)
        {
            this->books[i].print();
        }
    }
};

int main ()
{
    Library library;

    library.addBook(Book("Harry Potter", 2001));
    library.addBook(Book("Pod igoto", 1893));
    library.addBook(Book("The Little Prince", 1943));
    library.addBook(Book("The Shining", 1977));
    library.addBook(Book("The Great Gatsby", 1925));

    library.printInfo();

    std::cout << std::boolalpha << library.removeBook("Moby-Dick") << std::endl;
    std::cout << std::boolalpha << library.removeBook("Pod igoto") << std::endl;

    library.printInfo();

    return 0;
}