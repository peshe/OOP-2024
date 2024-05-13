#include <iostream>
#include <vector>
//
//void print3(int a, int b, int c) {
//	std::cout << a << ", " << b << ", " << c << std::endl;
//}
//
//void print3(std::string a, std::string b, std::string c) {
//	std::cout << a << ", " << b << ", " << c << std::endl;
//}

template<typename T1, typename T2, typename T3>
void print3(T1 a, T2 b, T3 c) {
	std::cout << a << ", " << b << ", " << c << std::endl;
}

void print3(int a, int b, std::string c) {
	std::cout << "INTS" << std::endl;
	std::cout << a << ", " << b << ", " << c << std::endl;
}

template<typename T>
T max(T a, T b) {
	return a < b ? b : a;
}

template<typename T>
bool compare(const T& a, const T& b) {
	return a < b;
}

bool compare(const char* a, const char* b) {
	return strcmp(a, b) < 0;
}

template<typename TFirst, typename TSecond>
struct Pair {
	TFirst first;
	TSecond second;

	bool operator<(const Pair& other) const {
		return this->first < other.first && this->second < other.second;
	}
};

//void printn() {
//	std::cout << std::endl;
//}

template<typename TLast>
void printn(TLast last) {
	std::cout << last << std::endl;
}

template<typename T1, typename... Rest>
void printn(T1 p1, Rest... rest) {
	std::cout << p1 << ", ";
	printn(rest...);
}

template<typename T, size_t size>
struct StaticArray {
	T array[size];
};

int factorial(int n) {
	if (n == 0 || n == 1) {
		return 1;
	}

	return n * factorial(n - 1);
}

template<int N>
struct Factorial {
	static constexpr int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<1> {
	static constexpr int value = 1;
};


int main()
{
	StaticArray<int, 25> arr;
	std::cout << Factorial<5>::value;
	std::cout << std::boolalpha;
	printn(1);
	printn(1, 2, 3, 4, 5);

	//printn(12.34, compare("ABCD", "ABC"), "Bye", 1, 2, 3, 4, 5, 5);

	/*Pair<int, std::string> p{ 1,"Introduction" };
	Pair<int, std::string> p2{ 10,"Introduction" };
	std::cout << compare(p, p2) << std::endl;

	print3(1, 2, "asd");*/

	/*print3<int>(1, 2, 3);
	print3<std::string>("a", "b", "c");
	print3<float>(1.0f, 2.53f, 4.0f);
	print3(1, true, "Hi");*/




}