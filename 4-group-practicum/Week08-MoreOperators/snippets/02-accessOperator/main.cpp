#include "dummyArray.h"

void printArr(const DummyArray& arr, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main ()
{
    int arr[] = {1, 2, 3, 4, 5};

    DummyArray dummy(arr, 5);

    printArr(dummy, 5);

    return 0;
}