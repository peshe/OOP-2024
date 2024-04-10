#pragma once

#ifndef _SORTED_ARRAY_HEADER_INCLUDED__
#define _SORTED_ARRAY_HEADER_INCLUDED__

#include <initializer_list>
#include <iostream>

namespace fmi::oop {

    class SortedArray
    {
    public:
        SortedArray();
        explicit SortedArray(size_t initialCapacity);
        SortedArray(const int* data, size_t len);
        SortedArray(std::initializer_list<int> list);
        SortedArray(const SortedArray& other);
        SortedArray(SortedArray&& other) noexcept;
        ~SortedArray() noexcept;
        SortedArray& operator=(const SortedArray& other);
        SortedArray& operator=(SortedArray&& other) noexcept;

        class SAIterator;
        class SAProxy;

        SAIterator begin() const;
        SAIterator end() const;
        SAIterator find(int key) const;

        int operator[](int index) const;
        int at(int index) const;
        SAProxy operator[](int index);
        SAProxy at(int index);

        void insert(int key);
        SortedArray& operator+=(int key);

        void remove(int key);
        void remove(const SAIterator& where);
        SortedArray& operator-=(int key);

        size_t size() const;
        bool empty() const;

        void ensureCapacity(size_t newSize);

    private:
        void sortUp(size_t start);
        void sortDown(size_t start);

    private:
        size_t count, capacity;
        int* elements;
    };

    class SortedArray::SAIterator
    {
        friend class SortedArray;

    public:
        int operator*() const;

        SortedArray::SAIterator& operator++();
        SortedArray::SAIterator  operator++(int);

        SortedArray::SAIterator& operator--();
        SortedArray::SAIterator  operator--(int);

        SortedArray::SAIterator& operator+=(int);
        SortedArray::SAIterator  operator+(int);

        bool operator==(const SAIterator& other) const;
        bool operator!=(const SAIterator& other) const;

        bool operator< (const SAIterator& other) const;
        bool operator<=(const SAIterator& other) const;
        bool operator> (const SAIterator& other) const;
        bool operator>=(const SAIterator& other) const;

        bool operator!() const;
        operator bool() const;
    private:
        SAIterator(const SortedArray& owner, int start);

        const SortedArray& owner;
        int position;
    };

    class SortedArray::SAProxy
    {
        friend class SortedArray;
    public:
        operator int() const;
        SAProxy& operator=(int data);

        SAProxy& operator=(const SAProxy& rhs);

    private:
        SAProxy(SortedArray& owner, size_t pos);

    private:
        SortedArray& owner;
        size_t position;
    };

    std::ostream& operator<<(std::ostream& os, const SortedArray& arr);
    std::istream& operator>>(std::istream& is, SortedArray& arr);
    SortedArray operator+(const SortedArray& arr, int x);
    SortedArray operator-(const SortedArray& arr, int x);

    bool operator==(const SortedArray& first, const SortedArray& second);
    bool operator!=(const SortedArray& first, const SortedArray& second);
}
#endif //_SORTED_ARRAY_HEADER_INCLUDED__
