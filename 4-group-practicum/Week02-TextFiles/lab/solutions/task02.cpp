#include <iostream>
#include <fstream>

const std::size_t MAX_LINE_SIZE = 1024;

int main (int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Wrong number of arguments" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file.is_open())
    {
        std::cout << "Problem while opening the file!" << std::endl;
        return 1;
    }

    std::size_t counter = 0;
    char ch;
    while (!file.eof())
    {
        file.get(ch);
        ++counter;
    }

    file.close();

    std::cout << "The size of the file is " << counter << " bytes" << std::endl;

    return 0;
}