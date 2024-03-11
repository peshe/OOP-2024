#include <iostream>
#include <fstream>
#include <cstring>

const std::size_t MAX_BUFFER_SIZE = 256;

struct DictionaryPair
{
    char* first;
    char* second;
};

void deallocate(DictionaryPair* pairs, std::size_t size);

DictionaryPair* loadDictionary(const char* file, std::size_t& size);

std::size_t minFrom(const DictionaryPair* dictionary, std::size_t index, std::size_t from, std::size_t to);

void sort(DictionaryPair* dictionary, std::size_t size, std::size_t index);

bool saveDictionary(const DictionaryPair* dictionary, std::size_t size, const char* file);

int main (int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Wrong number of arguments!" << std::endl;
        return 1;
    }

    std::size_t size;
    DictionaryPair* dictionary = loadDictionary(argv[1], size);
    if (!dictionary)
    {
        return 1;
    }

    sort(dictionary, size, 0);
    if (!saveDictionary(dictionary, size, "sortedDictionary1.txt"))
    {
        delete[] dictionary;
        return 1;
    }

    sort(dictionary, size, 1);
    if (!saveDictionary(dictionary, size, "sortedDictionary2.txt"))
    {
        delete[] dictionary;
        return 1;
    }

    deallocate(dictionary, size);

    return 0;
}

void deallocate(DictionaryPair* pairs, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i)
    {
        delete[] pairs[i].first;
        delete[] pairs[i].second;
    }
    delete[] pairs;
}

DictionaryPair* loadDictionary(const char* file, std::size_t& size)
{
    std::ifstream dictionary(file);
    if (!dictionary)
    {
        std::cout << "Problm while opening " << file << " for reading" << std::endl;
        return nullptr;
    }

    DictionaryPair* pairs = nullptr;
    dictionary >> size;

    if (dictionary.good())
    {
        pairs = new (std::nothrow) DictionaryPair[size];
        if (!pairs)
        {
            std::cout << "Memory problem!" << std::endl;
            dictionary.close();
            return nullptr;
        }
    }
    else
    {
        std::cout << "Stream is not good!" << std::endl;
        size = 0;
        dictionary.close();
        return nullptr;
    }

    char buffer[MAX_BUFFER_SIZE];
    for (std::size_t i = 0; i < size; ++i)
    {
        dictionary >> buffer;
        pairs[i].first = new (std::nothrow) char[strlen(buffer) + 1];
        if (!pairs[i].first)
        {
            std::cout << "Memory prblem!" << std::endl;
            deallocate(pairs, i);
            dictionary.close();
            return nullptr;
        }
        strcpy(pairs[i].first, buffer);

        dictionary >> buffer;
        pairs[i].second = new (std::nothrow) char[strlen(buffer) + 1];
        if (!pairs[i].second)
        {
            std::cout << "Memory prblem!" << std::endl;
            delete[] pairs[i].first;
            deallocate(pairs, i);
            dictionary.close();
            return nullptr;
        }
        strcpy(pairs[i].second, buffer);
    }

    dictionary.close();

    return pairs;
}

std::size_t minFrom(const DictionaryPair* dictionary, std::size_t index, std::size_t from, std::size_t to)
{
    std::size_t min = from;

    for (std::size_t i = from + 1; i < to; ++i)
    {
        char* minStr = (index == 0) ? dictionary[min].first : dictionary[min].second;
        char* currentStr = (index == 0) ? dictionary[i].first : dictionary[i].second;
        
        if (strcmp(minStr, currentStr) > 0)
        {
            min = i;
        }
    }

    return min;
}

void sort(DictionaryPair* dictionary, std::size_t size, std::size_t index)
{
    for (std::size_t i = 0; i < size; ++i)
    {
        std::size_t min = minFrom(dictionary, index, i, size);
        std::swap(dictionary[i], dictionary[min]);
    }
}

bool saveDictionary(const DictionaryPair* dictionary, std::size_t size, const char* file)
{
    std::ofstream out(file);
    if (!file)
    {
        std::cout << "Problem while opening " << file << " for writing" << std::endl;
        return false;
    }

    for (std::size_t i = 0; i < size; ++i)
    {
        out << dictionary[i].first << " " << dictionary[i].second << std::endl;
    }

    out.close();

    return true;
}