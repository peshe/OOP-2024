#include <cstring>
#include "String.h"

const size_t String::DEFAULT_CAPACITY = 8;

String::String()
    : pData(nullptr)
    , size(0)
    , capacity(0)
{}

String::String(const String& other)
{
    copy(other);
}

String& String::operator=(const String& other)
{
    if (this != &other)
    {
        clear();
        copy(other);
    }

    return *this;
}

String::~String()
{
    clear();
}

String::String(const char* str) : String()
{
    if (!str)
        return;

    this->size = strlen(str);
    this->reserve(size + 1);
    strcpy(this->pData, str);
}

String::operator const char*() const
{
    return pData;
}

void String::copy(const String& other)
{
    this->size = other.size;
    this->capacity = other.capacity;

    if (other.pData)
    {
        this->pData = new char[other.capacity];
        for (size_t i = 0; i < other.size; i++)
            this->pData[i] = other.pData[i];
    }
}

void String::clear()
{
    delete[] this->pData;
    this->pData = nullptr;
}

void String::reserve(size_t newCapacity)
{
    if (newCapacity <= this->capacity)
        return;

    char* pNewData = new char[newCapacity];
    if (this->pData)
        strcpy(pNewData, this->pData);
    else
        pNewData[0] = '\0';

    delete[] this->pData;
    this->pData = pNewData;
    this->capacity = newCapacity;
}

std::ostream& operator<<(std::ostream& out, const String& str)
{
    if (str.pData)
        return out << str.pData;

    return out;
}
