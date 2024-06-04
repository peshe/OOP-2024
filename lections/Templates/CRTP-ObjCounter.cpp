#include <cstdint>
#include <iostream>

template <typename CountedType>
class ObjCounter
{
private:
    static size_t count;
protected:
    ObjCounter()
    {
        ++count;
    }
    ObjCounter(const ObjCounter&)
    {
        ++count;
    }
    ~ObjCounter()
    {
        --count;
    }
public:
    static size_t getCount()
    {
        return count;
    }
};

template <typename CountedType>
size_t ObjCounter<CountedType>::count = 0;

class Test : public ObjCounter<Test>
{
public:
    Test() {}
    Test(const Test&) {}
    ~Test() {}

    void printCount() const
    {
        std::cout << "Count: " << getCount() << "\n";
    }
};

class MyClass : public ObjCounter<MyClass>
{
public:
    MyClass(int x)
    {
        this->x = x ? x : 1;
    }

private:
    int x;
};

#if 0
int main()
{
    Test obj1;
    Test arr[10];

    obj1.printCount();

    MyClass obj(0);
    std::cout << ObjCounter<Test>::getCount() << "\n";
    {
        MyClass arr[5] = { 1, 2, 3, 4, 5 };

        std::cout << ObjCounter<MyClass>::getCount() << "\n";
    }
    std::cout << ObjCounter<MyClass>::getCount() << "\n";
}
#endif
