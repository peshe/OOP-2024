#include <iostream>

// if the pointer is not passed by reference, a copy of the pointer will be passed
// so the pointer in the main will not point to the array allocated in the function
void createArray(int*& arr, std::size_t& size)
{
    std::cin >> size;

    arr = new (std::nothrow) int[size];
    if (!arr)
    {
        return;
    }

    for (std::size_t i = 0; i < size; ++i)
    {
        std::cin >> arr[i];
    }
}

void printArray(const int* array, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main ()
{
    int* arr;
    std::size_t size;

    createArray(arr, size);
    if (!arr)
    {
        std::cout << "Memory problem!"<< std::endl;
        return 1;
    }

    printArray(arr, size);

    delete[] arr;
}