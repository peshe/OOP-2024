#include "sorted_array.hpp"

#include <sstream>

using namespace fmi::oop;

void testSortedArray()
{
    int data[10] = { 0, 4, 3, 6, 8, 1, 9, 2, 7, 5 };
    SortedArray a1, a2(10);
    SortedArray a3(data, 10);

    std::cout << a1 << ' ' << a2 << ' ' << a3 << '\n';

    SortedArray a4{ 0, 4, 3, 6, 8, 1, 9, 2, 7, 5 };
    SortedArray a5 = a3;
    SortedArray a6(std::move(a3));

    std::cout << a4 << ' ' << a5 << ' ' << a6 << '\n';

    a5.insert(3);
    a5 += 11;
    a5 += -6;

    std::cout << a5 << '\n';
    a3 = a5;
    a4 = std::move(a5);
    std::cout << a3 << ' ' << a4 << '\n';

    a1 = a2 + 1 + 3 + 11 + 0 + -1;
    for (int elem : a1) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';

    const SortedArray sa = a4;
    for (size_t i = 0; i < sa.size(); ++i) {
        std::cout << sa[i] << ' ' << a4[i] << '\n';
    }
    std::cout << '\n';

    for (int i = 0; i < (int)sa.size(); ++i) {
        std::cout << a4 << '\n';
        a4[i] = 10 - i;
    }
    std::cout << a4 << '\n';

    std::cout << *a4.find(2) << '\n';

    a4.remove(a4.find(2));
    std::cout << a4 << '\n';
    a4 -= 0;
    a3 = a4 - 1;
    std::cout << a4 << '\n' << a3 << '\n';


    for (int i = 0; i < 10; ++i) {
        SortedArray::SAIterator pos = a3.find(i);
        if (pos) a3.remove(pos);
    }
    std::cout << a3 << '\n';

    std::cin >> a3;
    std::cout << a3 << '\n';

    std::stringstream ss;
    ss << a4;
    ss >> a2;

    std::cout << a2 << ' ' << (a4 == a2) << '\n';
 
    std::cin >> a3;
    std::cout << a3 << '\n';
}

int main()
{
    testSortedArray();
    return 0;
}
