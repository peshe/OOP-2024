#include <iostream>
#include <cstring>
#include "CellString.h"

CellString::CellString() : CellBase(CellType::STRING), str(nullptr)
{
}

CellString::CellString(const char *value) : CellString()
{
    Set(value);
}

CellString::CellString(const CellString &other) : CellBase(other)
{
    Copy(other);
}

CellString& CellString::operator=(const CellString& other)
{
    if (this != &other)
    {
        Clear();
        Copy(other);
    }
    return *this;
}

CellString::~CellString()
{
    Clear();
}

CellBase* CellString::Clone() const
{
    return new CellString(*this);
}

void CellString::Print() const
{
    if (str)
        std::cout << "String: " << str << "\n";
    else
        std::cout << "String: <empty>\n";
}

void CellString::Set(const char *value)
{
    delete[] str;
    str = nullptr;
    if (!value)
        return;

    str = new char[strlen(value) + 1];
    strcpy(str, value);
}

void CellString::Copy(const CellString& other)
{
    if (!other.str)
    {
        str = nullptr;
        return;
    }

    str = new char[strlen(other.str) + 1];
    strcpy(str, other.str);
}

void CellString::Clear()
{
    delete[] str;
    str = nullptr;
}
