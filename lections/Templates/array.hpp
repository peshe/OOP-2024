#pragma once

#include <iostream>
#include <cassert>

#ifndef _ARRAY_HEADER_INCLUDED
#define _ARRAY_HEADER_INCLUDED

template <typename Type, size_t size = 32>
class Array
{
public:

#pragma region Constructors

    Array() : used(0) {}

    Array(std::initializer_list<Type> list) : used(0) {
        for (const Type& elem : list) {
            arr[used] = std::move(elem);
            ++used;
            if (used == size) return;
        }
    }

    template<typename OtherType>
    Array(const OtherType* arr, size_t n)
    {
        used = std::min(size, n);
        for (size_t i = 0; i < used; i++) {
            this->arr[i] = arr[i];
        }
    }

    template<typename OtherType, size_t otherSize>
    Array(const Array<OtherType, otherSize>& arr) {
        used = std::min(size, arr.getSize());
        for (size_t index = 0; index < used; ++index) {
            this->arr[index] = arr[index];
        }
    }

    template<size_t otherSize>
    Array(Array<Type, otherSize>&& other) noexcept : used(0){
        used = std::min(size, other.getSize());
        for (size_t i = 0; i < used; ++i) {
            arr[i] = std::move(other[i]);
        }
        other.used = 0;
    }

    template<typename OtherType, size_t otherSize>
    Array<Type, size> operator=(const Array<OtherType, otherSize>& other);

    template<typename OtherType, size_t otherSize>
    Array<Type, size> operator=(Array<OtherType, otherSize>&& other) noexcept;

#pragma endregion

#pragma region Accessors

    bool append(const Type& val)
    {
        if (used < size) {
            arr[used] = val;
            ++used;
            return true;
        }
        return false;
    }

    size_t getSize() const
    {
        return used;
    }
    
    Type& operator[](size_t index)
    {
        assert(index < size);
        return arr[index];
    }

    const Type& operator[](size_t index) const
    {
        assert(index < used);
        return arr[index];
    }

    const Type& at(size_t index) const
    {
        if (index >= used) { 
            throw std::overflow_error("Index out of array bounds.");
        }
        return arr[index];
    }

    Type& at(size_t index)
    {
        if (index >= size) {
            throw std::overflow_error("Index out of array bounds.");
        }
        if (index > used) {
            for (; used < index; ++used) {
                arr[used] = Type{};
            }
            used = index+1;
        }
        return arr[index];
    }

    bool remove(size_t index)
    {
        if (index >= used) return false;
        for (size_t i = index; i < used; ++i)
            arr[i] = std::move(arr[i + 1]);
        --used;
        return true;
    }

    void clear()
    {
        used = 0;
    }

#pragma endregion

#pragma region HigherOrderFunctions

template <typename Predicate>
void filter(const Predicate& p)
{
    size_t newSize = 0;
    for (size_t index = 0; index < used; ++index) {
        if (p(arr[index])) {
            arr[newSize++] = std::move(arr[index]);
        }
    }
    used = newSize;
}

template <typename Transformer>
void map(const Transformer& fun)
{
    for (size_t index = 0; index < used; ++index) {
        arr[index] = fun(arr[index]);
    }
}

template <typename Transformer>
void map(const Transformer& fun) const
{
    for (size_t index = 0; index < used; ++index) {
        fun(arr[index]);
    }
}

template <typename Accumulator>
auto accumulate(const Accumulator& fun) const
{
    decltype(fun({}, arr[0])) result {};
    for (size_t i = 0; i < used; ++i) {
        result = fun(result, arr[i]);
    }
    return result;
}

int find(const Type& val) const
{
    struct {
        mutable int pos;
        mutable int index;
        const Type& val;

        void operator()(const Type& elem) const{
            if (elem == val)
                pos = index;
            ++index;
        }
    }f{ -1, 0, val };

    map(f);
    return f.pos;
}

#pragma endregion

friend std::ostream& operator<< (std::ostream& out, const Array& arr)
{
    for (size_t i = 0; i < arr.used; ++i) {
        out << arr[i] << ' ';
    }
    return out;
}

private:
    Type arr[size];
    size_t used;

    template <typename T, size_t n> friend class Array;
};

template<typename Type, size_t size>
template<typename OtherType, size_t otherSize>
Array<Type, size> Array<Type, size>::operator=(const Array<OtherType, otherSize>& other)
{
    if ((void*)this != (void*) & other) {
        *this = Array<Type, size>(other);
    }
    return *this;
}

template<typename Type, size_t size>
template<typename OtherType, size_t otherSize>
Array<Type, size> Array<Type, size>::operator=(Array<OtherType, otherSize>&& other) noexcept
{
    if ((void*)this != (void*) &other) {
        size_t newCount = std::min(size, other.getSize());
        for (size_t i = 0; i < newCount; ++i) {
            this->arr[i] = std::move(other[i]);
        }
        this->used = newCount;
        other.used = 0;
    }
    return *this;
}


#endif // !_ARRAY_HEADER_INCLUDED
