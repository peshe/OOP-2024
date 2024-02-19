#include <iostream>

// We want to allocate a 'matrix' in the followong shape:
// (n = 5)
//  _
// |_|_
// |_|_|_
// |_|_|_|
// |_|_|_|_|
// |_|_|_|_|_|

void deallocate(int** matrix, std::size_t rows)
{
    for (std::size_t i = 0; i < rows; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int** generateMatrix(std::size_t size)
{
    int** matrix = new (std::nothrow) int*[size];
    if (!matrix)
    {
        return nullptr;
    }

    for (std::size_t i = 0; i < size; ++i)
    {
        matrix[i] = new (std::nothrow) int[i + 1];
        if (!matrix[i])
        {
            deallocate(matrix, i); // deallocate the already allocated rows
            return nullptr;
        }
    }

    return matrix;
}

void fillMatrix(int** matrix, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i)
    {
        for (std::size_t j = 0; j < i + 1; ++j)
        {
            matrix[i][j] = j + 1;
        }
    }
}

void printMatrix(int** matrix, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i)
    {
        for (std::size_t j = 0; j < i + 1; ++j)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main ()
{
    std::size_t size;
    std::cin >> size;

    int** matrix = generateMatrix(size);
    if (!matrix)
    {
        std::cout << "Memory problem!" << std::endl;
        return 1;
    }

    fillMatrix(matrix, size);
    printMatrix(matrix, size);

    deallocate(matrix, size);

    return 0;
}