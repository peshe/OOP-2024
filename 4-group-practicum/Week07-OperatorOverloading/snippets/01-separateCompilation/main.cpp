#include "library.h"
#include <iostream>

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