#include <vector>
#include <iostream>
#include <functional>

template<typename T>
struct equals
{
    bool operator()(const T& a, const T& b)const { return a == b; }
};

template <typename Type>
int find(const Type* array, int size, const Type& value)
{
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1;
}

template <typename Collection, typename Type>
int find(const Collection& array, const Type& value)
{
    decltype(std::begin(array)) iterator = std::begin(array);
    int pos = 0;

    while (iterator != std::end(array)) {
        if (*iterator == value) {
            return pos;
        }
        ++iterator;
        ++pos;
    }
    return -1;
}

template <typename Collection, typename Type, typename Comparator>
int find(const Collection& array, const Type& value, const Comparator& cmp = equals<const Type&>{})
{
    decltype(std::begin(array)) iterator = std::begin(array);
    int pos = 0;

    while (iterator != std::end(array)) {
        if (cmp(*iterator, value)) {
            return pos;
        }
        ++iterator;
        ++pos;
    }
    return -1;
}

bool eq5(int a, int b)
{
    return a % 5 == b % 5;
}

template <typename Type>
struct FindStatistics
{
    mutable int counter = 0;

    bool operator()(const Type& a, const Type& b) const
    {
        ++counter;
        return a == b;
    }
};

#if 0
int main()
{
    int array[] = { 1, 2, 3, 4, 5 };
    std::cout << 3 << ' ' << find(array, 3) << '\n';
    std::cout << 13 << ' ' << find(array, 13) << '\n';

    std::vector<int> v{ 1, 3, 5, 7, 9, 11 };
    std::cout << 3 << ' ' << find(v, 3) << '\n';
    std::cout << 13 << ' ' << find(v, 13) << '\n';
    std::cout << 13 << ' ' << find(v, 13, eq5) << '\n';
    
    int x = 4;
    std::cout << 13 << ' ' << find(v, 13, [x](int a, int b) { return a % x == b % x; }) << '\n';

    FindStatistics<char> fs;
    std::string str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam in tortor in augue laoreet rutrum convallis non nulla. Praesent pellentesque eu enim eu facilisis. Etiam ligula mi, aliquet non leo in, lacinia volutpat lorem.";

    find(str, 'a', fs);
    std::cout << "comparisons: " << fs.counter << "\n";
    
    fs.counter = 0;
    find(str, 'z', fs);
    std::cout << "comparisons: " << fs.counter << "\n";
    return 0;
}
#endif
