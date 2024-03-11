#include <iostream>
#include <fstream>

int main ()
{
    // always add the `binary` flag to work with binary files
    std::ofstream binaryFileOut("numbers.bin", std::ios::binary);

    if (!binaryFileOut.is_open())
    {
        std::cout << "Problem while opening the file" << std::endl;
        return 1;
    }

    // Two ways to set the 'put' pointer to the beginning of the file:
    binaryFileOut.seekp(0, std::ios::beg); // setting the `put` pointer to 0 positions from the beginning of the file
    binaryFileOut.seekp(0); // setting the `put` pointer to position 0

    // writing the numbers from 1 to 5 to a binary file
    for (int i = 0; i < 5; ++i)
    {
        int number = i + 1;

        // casting to 'const char*' (can be done with C-style cast, but this one is better)
        // sizeof - gets the size of a data type or a variables (in bytes)
        binaryFileOut.write(reinterpret_cast<const char*>(&number), sizeof(number));
        // 1 char = 1 byte => array of char = array of bytes
        // 1 int = 2 or 4 bytes (array of bytes)
    }

    binaryFileOut.close();


    std::ifstream binaryFileIn("numbers.bin", std::ios::binary);

    if (!binaryFileIn.is_open())
    {
        std::cout << "Problem while opening the file" << std::endl;
        return 1;
    }

    binaryFileIn.seekg(0, std::ios::end); // setting the 'get' pointer at the end of the file
    std::size_t endOfFile = binaryFileIn.tellg(); // saving the position of the end of the file

    binaryFileIn.seekg(0, std::ios::beg); // moving back to the beginning of the file

    while (binaryFileIn.tellg() < endOfFile) // reading until reaching the end of the file
    {
        int number;

        // casting to 'char*' (can be done with C-style cast, but this one is better)
        binaryFileIn.read(reinterpret_cast<char*>(&number), sizeof(number));
        std::cout << number << " ";
    }
    std::cout << std::endl;

    binaryFileIn.close();

    return 0;
}