#include <iostream>
#include <fstream>
#include <cstring>

const std::size_t MAX_WORD_LENGHT = 100;
const std::size_t MAX_WORDS_COUNT = 1000;

void replace(const char* fileName, const char* find, const char* replace)
{
    char words[MAX_WORD_LENGHT][MAX_WORDS_COUNT];

    std::ifstream in(fileName);
    if (!in.is_open())
    {
        std::cout << "Problem while opening the file" << std::endl;
        return;
    }

    std::size_t wordCount = 0;
    while (!in.eof())
    {
        in >> words[wordCount++];
    }

    in.close();

    std::ofstream out(fileName);
    if (!out.is_open())
    {
        std::cout << "Problem while opening the file" << std::endl;
        return;
    }

    for (std::size_t i = 0; i < wordCount; ++i)
    {
        if (strcmp(words[i], find) == 0)
        {
            out << replace << " ";
        }
        else
        {
            out << words[i] << " ";
        }

        if (words[i][strlen(words[i]) - 1] == '.')
        {
            out << '\n';
        }
    }

    out.close();
}

int main ()
{
    replace("princesa.txt", "princesa", "strandzhanka");

    return 0;
}