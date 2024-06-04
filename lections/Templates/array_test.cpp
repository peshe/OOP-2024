#include "array.hpp"

template <typename T, size_t n>
void print(const Array<T, n>& arr)
{
    std::cout << "Array data: ";
    arr.map([](const T& val) {std::cout << val << ' '; });
    std::cout << '\n';
}

template <typename T, size_t n1, size_t n2>
bool equals(const Array<T, n1>& a1, const Array<T, n2>& a2)
{
    if (a1.getSize() != a2.getSize()) {
        return false;
    }

    for (size_t i = 0; i < a1.getSize(); ++i) {
        if (a1[i] != a2[i]) {
            return false;
        }
    }
    return true;
}

static void test1()
{
    Array<int, 5> arr{ 1, 2, 3, 4, 5 };
    print(arr);

    Array<unsigned, 8> arr2(arr);
    arr2[arr2.getSize()] = 11;
    print(arr2);

    Array<char> text;
    print(text);
    for (char c = 'a'; c < 'm'; ++c)
        text.append(c);
    print(text);
}

static void test2()
{
    const char* text = "Some templates";
    Array<char> textArray(text, strlen(text));
    print(textArray);

    Array<int, 20> intCopy(textArray);
    print(intCopy);

    intCopy = Array<int, 10>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    print(intCopy);
    
    Array <int, 10> intCopy2 = std::move(intCopy);
    print(intCopy2);
    print(intCopy);
}

static int mul2(int val)
{
    return val * 2;
}

static void test3()
{
    Array<int> arr { 1, 2, 3, 4, 5 };
    print(arr);

    arr.append(6);
    print(arr);

    arr.at(2) = 33;
    print(arr);
    arr.at(15) = 250;
    print(arr);

    arr.filter([](int val) { return val; });
    print(arr);
    
    std::cout << arr.accumulate([](int acc, int val) { return acc + val; }) << '\n';

    std::cout << arr.find(250) << '\n';

    arr.remove(arr.find(250));
    print(arr);

    arr.map(mul2);
    std::cout << arr << '\n';
}

#if 0
int main()
{
    test1();
    test2();
    test3();
    return 0;
}
#endif
