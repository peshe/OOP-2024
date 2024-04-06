#pragma once

class Singleton
{
public:
    static Singleton* Instance()
    {
        if (!pInstance)
            pInstance = new Singleton;

        return pInstance;
    }

    static void Release()
    {
        delete pInstance;
        pInstance = nullptr;
    }

    void DoCount(int cnt)
    {
        someData += cnt;
    }

    int GetData() const
    {
        return someData;
    }

public:
    Singleton(const Singleton& other) = delete;
    Singleton& operator=(const Singleton& other) = delete;

private:
    Singleton() : someData(0) {}

private:
    int someData;
    static Singleton* pInstance;
};

Singleton* Singleton::pInstance = nullptr;
