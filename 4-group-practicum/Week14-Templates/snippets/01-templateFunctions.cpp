#include <iostream>
#include <string>

bool isSmaller(int a, int b)
{
    std::cout << "Int function is called" << std::endl;
    return a < b;
}

bool isSmaller(char a, char b)
{
    std::cout << "Char function is called" << std::endl;
    return a < b;
}

bool isSmaller(double a, double b)
{
    std::cout << "Double function is called" << std::endl;
    return a < b;
}

bool isSmaller(const std::string& a, const std::string& b)
{
    std::cout << "String function is called" << std::endl;
    return a < b;
}

template <typename T>
bool isSmaller(T a, T b)
{
    std::cout << "Template function is called" << std::endl;
    return a < b;
}

int main ()
{
    isSmaller(1, 5);
    isSmaller(1.0, 5.0);
    isSmaller('1', '5');
    isSmaller("1", "5");

    std::cout << "------------" << std::endl;

    isSmaller<int>(1, 5);
    isSmaller<double>(1.0, 5.0);
    isSmaller<char>('1', '5');
    isSmaller<std::string>("1", "5");

    std::cout << "------------" << std::endl;

    isSmaller("1", "5");
    // note that "1" and "5" are recognized as "const char*", 
    // but there isn't an explicit function for it, so the template one is called

    return 0;
}