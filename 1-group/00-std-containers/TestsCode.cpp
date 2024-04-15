#include <iostream>
#include <vector>
#include <string>
#include "String.h"
#include "Vector.h"

int main()
{
    // --- String tests ---
    String n;

    String str = "What is this sorcery?";

    std::cout << static_cast<const char*>(str) << '\n';
    std::cout << str.operator const char *() << '\n';
    std::cout << str;

    // str += ' ';
    // str += "Magic!";

    // char chA = str[2];

    // std::cout << "str[2]: " << chA << std::endl;
    // std::cout << "Whole str: " << str << std::endl;
    // std::cout << "3*str: " << (3*str) << std::endl;

    // String fromStream;
    // std::cout << "Enter a word: ";
    // std::cin >> fromStream;

    // String line;
    // line.getline(std::cin);

    // --- Vector tests ---
    Vector vec;

    for (int i = 0; i < 10; i++)
        vec.push_back(i);
    
    std::cout << vec[4] << '\n';

    //vec.print(std::cout);

    return 0;
}

void printVec(const Vector& vec)
{
    for (size_t i = 0; i < vec.getSize(); i++)
    {
        std::cout << vec[i] << ' ';
    } 
}
