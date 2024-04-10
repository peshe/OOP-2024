#include <iostream>
#include <string>

class Book
{
private:
    static int counter;
    unsigned int id;

public:
    Book()
    {
        this->id = counter++;
        std::cout << "I am book #" << this->id << std::endl;
    }
};

int Book::counter = 1000;

Book globalBook;

int main ()
{
    Book stackBook;
    static Book staticBook;

    Book* dynamicBook = new Book;

    delete dynamicBook;
    
    return 0;
}