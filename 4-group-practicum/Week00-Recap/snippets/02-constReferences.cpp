#include <iostream>

void f(const int& a)
{
    std::cout << "The address of a in f() is: " << &a << std::endl;
    // a = 4; --> cannot change the value of const
}

int main ()
{
    int a = 3;

    f(a);
    f(4); // this also works as the function will not change the value anyway
    // if a literal is passed, a temporary object for it is created

    return 0;
}