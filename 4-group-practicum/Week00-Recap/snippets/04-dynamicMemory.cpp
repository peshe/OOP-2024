#include <iostream>

/*
HOW TO WORK CORRECTLY WITH DYNAMIC MEMORY?
1. Try to allocate the memory
2. Check if the allocation is successfull
3. Use the memory
4. Delete the allocated memory
*/

// compiles, but is wrong
// it returns pointer to an array that will 'die' at the end of the function (local array)
// int* getArr()
// {
//     int arr[5] = {1, 2, 3, 4, 5};

//     return arr;
// }

// the function allocates array for 5 elements in the heap
// the array will continue to 'live' in the main
// a pointer to the first element is returned
int* getArr()
{
    int* arr = new (std::nothrow) int[5];
    if (!arr)
    {
        return nullptr;
    }

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;

    return arr;
}

void printArray(const int* arr, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main ()
{
    int* arr = getArr();
    if (!arr)
    {
        std::cout << "Memory problem!" << std::endl;
        return 1;
    }

    printArray(arr, 5);

    delete[] arr;

    return 0;
}