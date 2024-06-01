#include <iostream>
#include <string>
#include <stdexcept>

class BookNotFoundException : public std::exception
{
private:
    std::string message;

public:
    BookNotFoundException(const std::string& message) 
        : message(message) {}

    const char* what() const noexcept override final
    {
        return this->message.c_str();
    }
};

int main ()
{
    try
    {
        throw BookNotFoundException("mnogo tajno");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}