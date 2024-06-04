#include <iostream>

template <class T, class U = int> // by default, the second argument will be 'int'
struct MyPair
{
    T first;
    U second;
};

template <class T, class U>
void print(const MyPair<T, U>& pair)
{
    std::cout << "<" << pair.first << ", " << pair.second << ">" << std::endl;
}

int main ()
{
    MyPair<int, const char*> pair1 = {99, "Kireto"};
    MyPair<const char*, char> pair2 = {"Pesho", 'P'};
    MyPair<double> pair3 = {3.14, 3};

    print(pair1);
    print(pair2);
    print(pair3);
    
    return 0;
}