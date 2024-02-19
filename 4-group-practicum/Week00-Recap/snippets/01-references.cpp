#include <iostream>

// pass by value
// makes a copy of the object
void f(int a)
{
    std::cout << "The address of a in f() is: " << &a << std::endl;
}

// pass by reference
// the object here and the object in the main are the same
void g(int& a)
{
    std::cout << "The address of a in g() is: " << &a << std::endl;
}

// void swap(int a, int b) ---> will not work 
void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int a = 3;

    std::cout << "The address of a in main() is: " << &a << std::endl;
    f(a);
    g(a);

    // g(3); --> cannot pass something like that
    // "3" is int literal 
    // the function expects reference to int, which can be modified

    int b = 4;
    swap(a, b);

    std::cout << a << " " << b << std::endl; // 4 3

    return 0;
}