#include <iostream>
#include <fstream>

const std::size_t MAX_SIZE = 1024;

int main ()
{
    // i - intput
    // f - file
    // stream
    std::ifstream dadJokes("dadJokes.txt"); 

    if (!dadJokes.is_open()) // always check if the opening is successfull
    {
        std::cout << "Problem while opening the file" << std::endl;
        return 1;
    }

    // Reading the file line by line

    char tempLine[MAX_SIZE];
    while (!dadJokes.eof()) // reading until end of file
    {
        dadJokes.getline(tempLine, MAX_SIZE);
        std::cout << tempLine << std::endl;
    }

    dadJokes.close();

    return 0;
}