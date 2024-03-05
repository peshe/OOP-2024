#include <iostream>
#include <fstream>

const std::size_t MAX_SIZE = 1024;

int main(int argc, char** argv) // the 'main' function has arguments, argc - arguments count, argv - the arguments
{
    std::cout << "The number of command arguments is: " << argc << std::endl;
    for (int i = 0; i < argc; ++i)
    {
        std::cout << "Argument #" << i + 1 << ": " << argv[i] << std::endl;
    }

    std::cout << std::endl;

    if (argc == 2)
    {
        std::ifstream secondArgument(argv[1]);

        if (!secondArgument.is_open())
        {
            std::cout << "Problem while opening the file" << std::endl;
            return 1;
        }

        char tempLine[MAX_SIZE];
        while (!secondArgument.eof())
        {
            secondArgument.getline(tempLine, MAX_SIZE);
            std::cout << tempLine << std::endl;
        }
    }
    else
    {
        std::cout << "Wrong number of arguments" << std::endl;
    }

    return 0;
}