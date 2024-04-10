#include <iostream>
#include <string>

class MyCString
{
public:
    static std::size_t strlen(const char* str)
    {
        std::size_t length = 0;

        while(str[length])
        {
            ++length;
        }

        return length;
    }
    static void stcpy(char* destination, const char* source)
    {
        std::size_t pos = 0;

        while (source[pos])
        {
            destination[pos] = source[pos];
            ++pos;
        }
        destination[pos] = '\0';
    }

    static int strcmp(const char* str1, const char* str2)
    {
        while (*str1 && *str2 && *str1 == *str2)
        {
            ++str1;
            ++str2;
        }

        return *str1 - *str2;
    }
};

int main ()
{
    std::cout << MyCString::strlen("Pesho") << std::endl;

    char temp[1024];
    MyCString::stcpy(temp, "Alo, da");
    std::cout << temp << std::endl;

    std::cout << MyCString::strcmp("Lyubo", "Lyubo") << std::endl;
    std::cout << MyCString::strcmp("Pesho", "Lyubo") << std::endl;
    std::cout << MyCString::strcmp("Lyubo", "Pesho") << std::endl;

    return 0;
}