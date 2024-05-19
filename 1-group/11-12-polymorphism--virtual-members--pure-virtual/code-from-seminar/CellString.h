#pragma once
#include "CellBase.h"

class CellString : public CellBase
{
public:
    CellString();
    CellString(const char* value);
    CellString(const CellString& other);
    CellString& operator=(const CellString& other);
    ~CellString();

    CellBase* Clone() const override;
    void Print() const override;
    void Set(const char* value);

private:
    void Copy(const CellString& other);
    void Clear();

private:
    char* str;
};
