#include <iostream>
#include <fstream>

const std::size_t MAX_WORD_SIZE = 100;

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

    // Reading the file word by word

    char tempWord[MAX_WORD_SIZE];
    while (!dadJokes.eof()) // reading until end of file
    {
        dadJokes >> tempWord;
        std::cout << tempWord << std::endl;
    }

    dadJokes.close();

    return 0;
}