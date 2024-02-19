#include <iostream>

int main ()
{
    int a = 3;

    int* aPtr = &a;

    std::cout << a << " " << *aPtr << std::endl;
    *aPtr = 4; 
    std::cout << a << " " << *aPtr << std::endl;

    const int* aPtr2 = &a;
    std::cout << a << " " << *aPtr2 << std::endl;
    // *aPtr2 = 5; ---> cannot change the value, as the pointer is pointing to a const

    int** doublePtr = &aPtr;
    std::cout << **doublePtr << std::endl;

    int arr[] = {1, 2, 3, 4, 5};

    std::cout << *arr << std::endl; // 1

    std::cout << *(arr + 2) << std::endl; // 3
    std::cout << arr[2] << std::endl; // 3
    std::cout << *(2 + arr) << std::endl; // 3
    std::cout << 2[arr] << std::endl; // 3

    int* arrPtr = arr;
    arrPtr += 3; // pointer arithmetic

    std::cout << *arrPtr << std::endl; // 4

    int *const arrConstPtr = arr;
    std::cout << *arrConstPtr << std::endl;
    // arrConstPtr += 3; // cannot move the pointer, as it is const
    *arrConstPtr = 5; // can hange the value

    const int *const constPtrToConstInt = arr;
    // *constPtrToConstInt = 3; // cannot change the value
    // constPtrToConstInt += 2; // cannot move the pointer;

    const int *const *const magic = nullptr; // How do you read this?

    return 0;
}