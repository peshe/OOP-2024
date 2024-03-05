#include <iostream>
#include <cstring>
#include <fstream>

const std::size_t MAX_SIZE = 1024;

char* readAndAllocate(std::ifstream& in);

int main ()
{
    std::ifstream file("alabala.txt");

    if (!file)
    {
        std::cout << "Problem while opening the file" << std::endl;
        return 1;
    }

    char* str = readAndAllocate(file);
    if (!str)
    {
        std::cout << "Problem while allocating memory" << std::endl;
        file.close();
        return 1;
    }

    std::cout << str << std::endl;

    file.close();
    delete[] str;

    return 0;
}

char* readAndAllocate(std::ifstream& in)
{
    char temp[MAX_SIZE];

    in.getline(temp, MAX_SIZE);

    char* result = new (std::nothrow) char[strlen(temp) + 1];
    if (!result)
    {
        return nullptr;
    }

    strcpy(result, temp);

    return result;
}