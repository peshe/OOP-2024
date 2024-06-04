#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>
#include <algorithm>

template<typename Type>
class Array
{
public:
    Array() noexcept :
        data(nullptr), size(0), capacity(0) {}

    Array(size_t initial) :
        data(new Type[initial]), size(0), capacity(initial) {}

    Array(const Array& other) : data(nullptr)
    {
        copy(other);
    }

    Array(Array&& other) noexcept :
          data(other.data), size(other.size), capacity(other.capacity)
    {
        other.data = nullptr;
        other.size = 0;
    }


    Array& operator=(const Array& other)
    {
        return *this = Array(other);
    }

    Array& operator=(Array&& other)
    {
        if (&other != this) {
            std::swap(data, other.data);
            std::swap(size, other.size);
            std::swap(capacity, other.capacity);
        }
        return *this;
    }

    ~Array()
    {
        delete[]data;
    }

    void push_back(const Type& val)
    {
        ensure_size(size + 1);
        data[size] = val;
        ++size;
    }

    int find(const Type& val) const
    {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] == val)
                return (int)i;
        }
        return -1;
    }

    void print()const
    {
        for (size_t i = 0; i < size; ++i)
            std::cout << data[i] << ' ';
        std::cout << std::endl;
    }

    const Type& operator[](size_t index) const
    {
        return data[index];
    }
    Type& operator[](size_t index)
    {
        return data[index];
    }

private:
    void copy(const Array& arr)
    {
        Type* data = new Type[arr.capacity];
        try {
            for (int pos = 0; pos < arr.size; ++pos) {
                data[pos] = arr.data[pos];
            }
        }
        catch (...) {
            delete[] data;
            throw;
        }

        delete[] this->data;
        this->data = data;
        this->capacity = arr.capacity;
        this->size = arr.size;
    }

    void ensure_size(size_t size)
    {
        if (size < capacity) return;
        size_t new_capacity = std::max(size, capacity * 2);
        Type* data = new Type[new_capacity];
        for (int pos = 0; pos < this->size; ++pos) {
            data[pos] = std::move(this->data[pos]);
        }

        delete[] this->data;
        this->data = data;
        capacity = new_capacity;
    }

private:
    Type* data;
    size_t size, capacity;
};
#if 1
template<>
class Array<const char*>
{
public:
    Array(size_t initial = 8) :
        data(new char*[initial]), size(0), capacity(initial) {}

    Array(const Array& other) : data(nullptr), size(0)
    {
        copy(other);
    }

    Array(Array&& other) noexcept :
        data(other.data), size(other.size), capacity(other.capacity)
    {
        other.data = nullptr;
        other.size = 0;
    }

    Array& operator=(const Array& other)
    {
        return *this = Array(other);
    }

    Array& operator=(Array&& other)
    {
        if (&other != this) {
            std::swap(data, other.data);
            std::swap(size, other.size);
            std::swap(capacity, other.capacity);
        }
        return *this;
    }

    ~Array()
    {
        clear(data, size);
    }

    void push_back(const char* word)
    {
        ensure_size(size + 1);
        data[size] = dup(word);
        ++size;
    }

    int find(const char* val) const
    {
        for (size_t i = 0; i < size; ++i) {
            if (!strcmp(data[i], val))
                return (int)i;
        }
        return -1;
    }

    void print()const
    {
        for (size_t i = 0; i < size; ++i)
            std::cout << data[i] << ' ';
        std::cout << std::endl;
    }

    const char* operator[](size_t index) const
    {
        return data[index];
    }

private:
    char* dup(const char* data) {
        if (data) return strcpy(new char[strlen(data) + 1], data);
        return nullptr;
    }
    void clear(char** data, size_t size)
    {
        for (size_t i = 0; i < size; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
    void copy(const Array& arr)
    {
        char** data = new char*[arr.capacity];
        size_t pos;
        try {
            for (pos = 0; pos < arr.size; ++pos) {
                data[pos] = dup(arr.data[pos]);
            }
        }
        catch (...) {
            clear(data, pos);
            throw;
        }

        clear(this->data, size);
        this->data = data;
        this->capacity = arr.capacity;
        this->size = arr.size;
    }

    void ensure_size(size_t size)
    {
        if (size < capacity) return;
        size_t new_capacity = std::max(size, capacity * 2);
        char** data = new char*[new_capacity];
        for (int pos = 0; pos < this->size; ++pos) {
            data[pos] = this->data[pos];
        }

        delete[] this->data;
        this->data = data;
        capacity = new_capacity;
    }

private:
    char** data;
    size_t size, capacity;
};
#endif

#if 0
int main()
{
    Array<int> arr;
    for (int i = 0; i < 10; ++i)
        arr.push_back(i);
    arr.print();
    std::cout << arr[arr.find(3)] << "\n";

    Array<const char*> words;
    char word[] = "pesho";
    for (int i = 0; i < 10; ++i) {
        words.push_back(word);
        ++word[i % 5];
        words.push_back(word);
    }
    words.print();
    std::cout << arr[words.find("resho")] << "\n";

    return 0;
}
#endif
