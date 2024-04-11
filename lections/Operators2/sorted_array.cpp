#include "sorted_array.hpp"

#include <cassert>

namespace fmi::oop {

SortedArray::SortedArray()
    : SortedArray(16)
{}

SortedArray::SortedArray(size_t initial)
    : count(0), capacity(initial)
    , elements(new int[capacity])
{}

SortedArray::SortedArray(const int* data, size_t len)
    : SortedArray(len)
{
    if (!data) {
        delete[] elements;
        throw std::invalid_argument("Data cannot be null!");
    }
    for (size_t index = 0; index < len; ++index) {
        insert(data[index]);
    }
}

SortedArray::SortedArray(std::initializer_list<int> list)
    : SortedArray(list.size())
{
    for (int elem : list) {
        insert(elem);
    }
}

SortedArray::SortedArray(const SortedArray& other)
    : SortedArray(other.capacity)
{
    for (int elem : other) {
        insert(elem);
    }
}

SortedArray::SortedArray(SortedArray&& other) noexcept
    : count(other.count), capacity(other.capacity)
    , elements(other.elements)
{
    other.elements = nullptr;
    other.count = 0;
    other.capacity = 0;
}

SortedArray::~SortedArray() noexcept
{
    delete[] elements;
}

SortedArray& SortedArray::operator=(const SortedArray& other)
{
    if (&other != this) {
        ensureCapacity(other.capacity);
        this->count = 0;
        for (int elem : other) {
            insert(elem);
        }
    }
    return *this;
}

SortedArray& SortedArray::operator=(SortedArray&& other) noexcept
{
    std::swap(elements, other.elements);
    std::swap(count, other.count);
    std::swap(capacity, other.capacity);
    return *this;
}

SortedArray::SAIterator SortedArray::begin() const
{
    return SortedArray::SAIterator(*this, 0);
}

SortedArray::SAIterator SortedArray::end() const
{
    return SortedArray::SAIterator(*this, count);
}

SortedArray::SAIterator SortedArray::find(int key) const
{
    size_t left = 0, right = count;
    while (left < right) {
        size_t middle = left + (right - left) / 2;
        if (elements[middle] < key) left = middle + 1;
        else if (key < elements[middle]) right = middle;
        else return SortedArray::SAIterator(*this, middle);
    }

    return SortedArray::SAIterator(*this, -1);
}

int SortedArray::operator[](int index) const
{
    assert((size_t) index < count);
    return elements[index];
}

int SortedArray::at(int index) const
{
    if (index < 0 || index >= (int)count) {
        throw std::out_of_range("Invalid index!");
    }

    return (*this)[index];
}

SortedArray::SAProxy SortedArray::operator[](int index)
{
    assert((size_t)index < count);
    return SortedArray::SAProxy(*this, index);
}

SortedArray::SAProxy SortedArray::at(int index)
{
    if (index < 0 || index >= (int)count) {
        throw std::out_of_range("Invalid index!");
    }

    return (*this)[index];
}

void SortedArray::insert(int key)
{
    ensureCapacity(count + 1);
    elements[count++] = key;
    sortUp(count-1);
}

SortedArray& SortedArray::operator+=(int key)
{
    insert(key);
    return *this;
}

void SortedArray::remove(int key)
{
    remove(find(key));
}

void SortedArray::remove(const SAIterator& where)
{
    if (&where.owner != this) {
        throw std::runtime_error("Passed iterator to different object!");
    }
    if (where.position < 0 || where.position >= (int)count)
        return;

    for (size_t index = where.position; index < count-1; ++index) {
        elements[index] = elements[index + 1];
    }
    --count;
}

SortedArray& SortedArray::operator-=(int key)
{
    remove(key);
    return *this;
}

size_t SortedArray::size() const
{
    return count;
}

bool SortedArray::empty() const
{
    return !size();
}

void SortedArray::ensureCapacity(size_t newSize)
{
    if (newSize < capacity)
        return;

    int* newData = new int[newSize];
    for (size_t i = 0; i < count; ++i) {
        newData[i] = elements[i];
    }
    delete[] elements;
    elements = newData;
    capacity = newSize;
}

void SortedArray::sortUp(size_t start)
{
    if (start > 0 && elements[start] < elements[start - 1]) {
        int element = elements[start];
        while (start > 0 && element < elements[start - 1]) {
            elements[start] = elements[start - 1];
            --start;
        }
        elements[start] = element;
    }
}

void SortedArray::sortDown(size_t start)
{
    if (start < count - 1 && elements[start] > elements[start + 1]) {
        int element = elements[start];
        while (start < count - 1 && element > elements[start + 1]) {
            elements[start] = elements[start + 1];
            ++start;
        }
        elements[start] = element;
    }
}

SortedArray::SAIterator::SAIterator(const SortedArray& owner, int start)
    : owner(owner), position(start)
{}

int SortedArray::SAIterator::operator*() const
{
    assert((size_t)position < owner.count);

    return owner[position];
}

SortedArray::SAIterator& SortedArray::SAIterator::operator++()
{
    if (position >= 0) 
        ++position;
    return *this;
}

SortedArray::SAIterator SortedArray::SAIterator::operator++(int)
{
    SortedArray::SAIterator old(*this);
    ++(*this);
    return old;
}

SortedArray::SAIterator& SortedArray::SAIterator::operator--()
{
    if (position >= 0) 
        --position;
    return *this;
}

SortedArray::SAIterator SortedArray::SAIterator::operator--(int)
{
    SortedArray::SAIterator old(*this);
    --(*this);
    return old;
}

SortedArray::SAIterator& SortedArray::SAIterator::operator+=(int step)
{
    if (position >= 0) {
        position += step;
    }
    return *this;
}

SortedArray::SAIterator SortedArray::SAIterator::operator+(int step)
{
    SortedArray::SAIterator old(*this);
    old += step;
    return old;
}

SortedArray::SAIterator::operator bool() const
{
    return position >= 0 && position < (int)owner.count;
}

bool SortedArray::SAIterator::operator!() const
{
    return !(bool)*this;
}

bool SortedArray::SAIterator::operator==(const SAIterator& other) const
{
    return (&owner == &other.owner && position == other.position);
}

bool SortedArray::SAIterator::operator!=(const SAIterator& other) const
{
    return !(*this == other);
}

bool SortedArray::SAIterator::operator<(const SAIterator& other) const
{
    return (&owner == &other.owner && position < other.position);
}

bool SortedArray::SAIterator::operator>(const SAIterator& other) const
{
    return other < *this;
}

bool SortedArray::SAIterator::operator<=(const SAIterator& other) const
{
    return *this < other || other == *this;
}

bool SortedArray::SAIterator::operator>=(const SAIterator& other) const
{
    return other <= *this;
}

SortedArray::SAProxy::SAProxy(SortedArray& owner, size_t pos)
    : owner(owner), position(pos)
{}

SortedArray::SAProxy::operator int() const
{
    assert(position <= owner.size());
    return owner.elements[position];
}

SortedArray::SAProxy& SortedArray::SAProxy::operator=(int data)
{
    assert(position <= owner.size());

    int oldValue = owner.elements[position];
    owner.elements[position] = data;

    if (oldValue < data) {
        owner.sortDown(position);
    }
    else if (oldValue > data) {
        owner.sortUp(position);
    }

    return *this;
}

SortedArray::SAProxy& SortedArray::SAProxy::operator=(const SAProxy& other)
{
    return operator=((int)other);
}

std::ostream& operator<<(std::ostream& os, const SortedArray& arr)
{
    os << '[';
    SortedArray::SAIterator it = arr.begin();
    while (it) {
        os << *it;
        ++it;
        if (it) os << ", ";
    }
    os << ']';
    return os;
}

std::istream& operator>>(std::istream& is, SortedArray& arr)
{
    if (!is) return is;

    char ch = 0;

    is >> ch;
    if (!is || ch != '[') {
        is.setstate(std::ios::failbit);
        return is;
    }

    SortedArray result;
    while (is && ch != ']') {
        int value;
        is >> value;
        if (is) {
            result.insert(value);
        }
        else {
            is.clear();
            ch = 0;
        }
        is >> ch;
        if (ch != ',' && ch != ']') {
            is.setstate(std::ios::failbit);
            return is;
        }
    }

    if (is) {
        arr = std::move(result);
    }
    return is;
}

SortedArray operator+(const SortedArray& arr, int x)
{
    SortedArray result(arr);
    result += x;
    return result;
}

SortedArray operator-(const SortedArray& arr, int x)
{
    SortedArray result(arr);
    result -= x;
    return result;
}

bool operator==(const SortedArray& first, const SortedArray& second)
{
    if (first.size() != second.size())
        return false;

    for (size_t pos = 0; pos < first.size(); ++pos)
        if (first[pos] != second[pos])
            return false;

    return true;
}

bool operator!=(const SortedArray& first, const SortedArray& second)
{
    return !(first == second);
}

} // namespace fmi::oop
