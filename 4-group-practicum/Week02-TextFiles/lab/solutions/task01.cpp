#include <iostream>
#include <fstream>

const std::size_t MAX_LINE_SIZE = 1024;

int main ()
{
    std::ifstream file("task01.cpp");

    if (!file.is_open())
    {
        std::cout << "Problem while opening the file!" << std::endl;
        return 1;
    }

    char buffer[MAX_LINE_SIZE];
    while (!file.eof())
    {
        file.getline(buffer, MAX_LINE_SIZE);

        std::cout << buffer << std::endl;
    }

    file.close();

    return 0;
}