#include <iostream>
#include <string>

template <class T>
class DummyClass
{
private:
    T data;

public:
    DummyClass();
    DummyClass(const DummyClass& other);
    DummyClass& operator = (const DummyClass& other);
    ~DummyClass();

    T getData() const;
    void setData(const T& data);
};

template <class T>
DummyClass<T>::DummyClass()
{
    std::cout << "Default constructor called" << std::endl;
}

template <class T>
DummyClass<T>::DummyClass(const DummyClass<T>& other)
{
    std::cout << "Copy constructor called" << std::endl;
    this->data = other.data;
}

template <class T>
DummyClass<T>& DummyClass<T>::operator = (const DummyClass<T>& other)
{
    std::cout << "Operator = called" << std::endl;
    if (this != &other)
    {
        this->data = other.data;
    }

    return *this;
}

template <class T>
DummyClass<T>::~DummyClass()
{
    std::cout << "Destructor called" << std::endl;
}

template <class T>
T DummyClass<T>::getData() const
{
    return this->data;
}

template <class T>
void DummyClass<T>::setData(const T& data)
{
    this->data = data;
}

int main ()
{
    DummyClass<int> dummyInt;
    dummyInt.setData(5);

    DummyClass<int> dummyIntCopy = dummyInt;
    std::cout << dummyIntCopy.getData() << std::endl;


    DummyClass<std::string> dummyString;
    dummyString.setData("aloo");

    DummyClass<std::string> dummyStringCopy;
    dummyStringCopy = dummyString;
    std::cout << dummyStringCopy.getData() << std::endl;

    return 0;
}