# Задача

*Бележка: Условието не е довършено и е по-скоро ориентировъчно с цел улеснение по време на преподаване.*

1.  (**inline class template**) Създайте клас отговаряш на математически вектор Vector<T,N>, където T е типът на координатната система, а N е пространството, в което е векторът. Например Vector<double,2> би имал семантиката на вектор в двумерното пространство с реални координати. За класът имплементирайте следните методи и оператори:
    1. operator+, който събира 2 вектора
    2. operator-, който изважда 2 вектора
    3. operator*, който умножава вектор по скалар
    4. Конструктор, който приема инициализиращ списък
    5. operator[](size_t index)
2. **(class template)** Разделете дефиницията и имплементацията на класа
    1. **Note**: **Не е толкова важно, в края, ако остане време**
3. **(templates & composition)** Имплементирайте клас Particle, който описва частица, която се движи в N-мерното пространство. Една частица се описва от 3 вектора:
    1. Position - Началната точка/вектор на частицата
    2. Velocity - Векторът, отговарящ на посоката и скоростта на движение
    3. Acceleration - Векторът, отговарящ за ускорението на частицат
    4. Класът трябва да има метод update, който да обновява позицията и скоростта на частицата за единица време
4. **(usage of template classes)** Имплементирайте симулация, която по 2 зададени частици започва тяхното движение, докато те не се сблъскат. Използвайте update() метода, за да променяте местоположението на частиците и for-loop, за да симуларате преминаването на секунди. Прекратете симулацията, когато 2те частици се блъснат.
5. **(inheritance + class templates)** ColoredVector
    1. Which are all the  possibilities?
6. std::vector custom class

---

### Кодът от семинара
```c++
#include <iostream>
#include <cassert>
#include <thread>

template<typename T, size_t N>
class Vector {
public:
	Vector(std::initializer_list<T> list)
	{
		if (list.size() != N) {
			throw std::invalid_argument("Initializer list size does not match vector dimensions.");
		}

		std::copy(list.begin(), list.end(), coords);
	}


	Vector<T, N>& operator+=(const Vector<T, N>& other) {
		for (size_t i = 0; i < N; i++)
		{
			coords[i] += other[i];
		}

		return *this;
	}

	Vector<T, N>& operator-=(const Vector<T, N>& other) {
		for (size_t i = 0; i < N; i++)
		{
			coords[i] -= other[i];
		}

		return *this;
	}

	Vector<T, N>& operator*=(const T& scalar) {
		for (size_t i = 0; i < N; i++)
		{
			coords[i] *= scalar;
		}

		return *this;
	}

	T& operator[](size_t index) {
		if (index >= N) {
			throw std::out_of_range("Index out of range");
		}

		return coords[index];
	}

	const T& operator[](size_t index) const {
		if (index >= N) {
			throw std::out_of_range("Index out of range");
		}

		return coords[index];
	}

private:
	T coords[N];
};

class ColoredVector2D : Vector<double, 2> {
public:
	ColoredVector2D(std::string color, std::initializer_list<double> list) :color(color), Vector(list)
	{

	}
public:
	std::string color;
};

template<typename T, size_t N>
Vector<T, N> operator+(const Vector<T, N>& a, const Vector<T, N>& b) {
	Vector<T, N> result = a;
	result += b;

	return result;
}

template<typename T, size_t N>
Vector<T, N> operator-(const Vector<T, N>& a, const Vector<T, N>& b) {
	Vector<T, N> result = a;
	result -= b;

	return result;
}

template<typename T, size_t N>
Vector<T, N> operator*(const Vector<T, N>& v, const T& scalar) {
	Vector<T, N> result = v;
	result *= scalar;

	return result;
}

template<typename T, size_t N>
class Particle {
public:
	Particle(Vector<T, N> pos, Vector<T, N> vel, Vector<T, N> acc)
		:position(pos), velocity(vel), acceleration(acc)
	{

	}

	void update(double timeStep) {
		position = position + velocity * timeStep + acceleration * (0.5 * timeStep * timeStep);
		velocity = velocity + acceleration * timeStep;
	}

	const Vector<T, N> getPosition() const {
		return position;
	}

	void setPosition(const Vector<T, N>& newPosition) {
		position = newPosition;
	}
private:
	Vector<T, N> position;
	Vector<T, N> velocity;
	Vector<T, N> acceleration;
};

void test_Vector() {
	// Test initialization
	Vector<int, 3> vec1 = { 1, 2, 3 };
	assert(vec1[0] == 1);
	assert(vec1[1] == 2);
	assert(vec1[2] == 3);

	// Test out-of-range access
	try {
		vec1[3];
		assert(false); // Should not reach here
	}
	catch (const std::out_of_range&) {
		assert(true); // Expected exception
	}

	// Test operator+=
	Vector<int, 3> vec2 = { 4, 5, 6 };
	vec1 += vec2;
	assert(vec1[0] == 5);
	assert(vec1[1] == 7);
	assert(vec1[2] == 9);

	// Test operator-=
	vec1 -= vec2;
	assert(vec1[0] == 1);
	assert(vec1[1] == 2);
	assert(vec1[2] == 3);

	// Test operator*=
	vec1 *= 2;
	assert(vec1[0] == 2);
	assert(vec1[1] == 4);
	assert(vec1[2] == 6);

	// Test operator+
	Vector<int, 3> vec3 = vec1 + vec2;
	assert(vec3[0] == 6);
	assert(vec3[1] == 9);
	assert(vec3[2] == 12);

	// Test operator-
	Vector<int, 3> vec4 = vec3 - vec2;
	assert(vec4[0] == 2);
	assert(vec4[1] == 4);
	assert(vec4[2] == 6);

	// Test operator* (scalar multiplication)
	Vector<int, 3> vec5 = vec4 * 3;
	assert(vec5[0] == 6);
	assert(vec5[1] == 12);
	assert(vec5[2] == 18);

	// Test initializer list size mismatch
	try {
		Vector<int, 2> vec6 = { 1, 2, 3 };
		assert(false); // Should not reach here
	}
	catch (const std::invalid_argument&) {
		assert(true); // Expected exception
	}
}

using Particle2D = Particle<double, 2>;

class ParticleSimulator {
public:
	ParticleSimulator(int width, int height) : windowWidth(width), windowHeight(height)
	{

	}

	void run(int iterations) {
		int maxWidth = 30;
		int maxHeight = 15;

		Particle2D p1({ 0,0 }, { 1,1 }, { 0.1,0.1 });
		Particle2D p2({ 10,10 }, { -1,-1 }, { 0.1,0.1 });

		for (int i = 0; i < iterations; i++)
		{
			system("cls");
			Vector<double, 2> pos1 = p1.getPosition();
			wrapPosition(pos1);
			p1.setPosition(pos1);

			int x1 = pos1[0];
			int y1 = pos1[1];


			Vector<double, 2> pos2 = p2.getPosition();
			wrapPosition(pos2);
			p2.setPosition(pos2);
			int x2 = pos2[0];
			int y2 = pos2[1];

			for (int y = 0; y < maxHeight; y++)
			{
				for (int x = 0; x < maxWidth; x++)
				{
					if (hasCollision(pos1, pos2)) {
						std::cout << "Particles have collided!" << std::endl;
						return;
					}
					if (x == x1 && y == y1) {
						std::cout << "x";
					}
					else if (x == x2 && y == y2) {
						std::cout << "o";
					}
					else {
						std::cout << " ";
					}
				}
				std::cout << std::endl;
			}

			p1.update(1.0);
			p2.update(1.0);
			std::this_thread::sleep_for(std::chrono::milliseconds(550));

		}
	}
private:
	int windowWidth;
	int windowHeight;

	bool hasCollision(const Vector<double, 2>& pos1, const Vector<double, 2>& pos2) {
		return abs((pos1[0] - pos2[0])) < 0.001 && abs((pos1[1] - pos2[1])) < 0.001;
	}

	void wrapPosition(Vector<double, 2>& pos) {
		if (pos[0] < 0) pos[0] += windowWidth;
		if (pos[0] >= windowWidth) pos[0] -= windowWidth;
		if (pos[1] < 0) pos[1] += windowHeight;
		if (pos[1] >= windowHeight) pos[1] -= windowHeight;
	}
};



int main() {
	ParticleSimulator simulator(30, 15);
	//ColoredVector<double, 2> v1 = ColoredVector<double,2>("red",{ 1, 2 });
	ColoredVector2D v1("red", { 1,2 });

	simulator.run(60);
	return 0;
}
```

---
# Custom vector class
```c++
#include <iostream>
#include <string>
#include <sstream>
#include "assert.h"

using namespace std;

template <typename T>
class Vector {
public:
    Vector() : size(0), capacity(0), data(nullptr){}
    
    Vector(size_t capacity) : size(0), capacity(capacity), data(new T[capacity]) {}
    
    Vector(const Vector& other):data(nullptr){
        copy(other);
    }
    
    Vector& operator=(const Vector& other){
        if(this != &other){
            copy(other);
        }
        
        return *this;
    }
    
    ~Vector(){
        delete[] data;
    }
    
    void push_back(const T& el){
        if(size >= capacity){
            resize();
        }
        
        data[size++] = el;
    }
    
    void pop_back() noexcept {
        if(!empty()){
            size--;
        }
    }
    
    T& operator[](size_t index) {
        if(index >= size) {
            throw std::out_of_range("Index out of range");
        }
        
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if(index >= size) {
            throw std::out_of_range("Index out of range.");
        }
        
        return data[index];
    }
    
    bool empty() const noexcept {
        return size == 0;
    }
    
    size_t getSize() const noexcept{
        return size;
    }
    
    void removeAt(size_t index) {
        if(index >= size){
            throw std::out_of_range("Index out of range.");
        }
        
        if(capacity == 0){
            throw std::runtime_error("The vector does not contain any elements");
        }
       
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        
        size--;
    }
    
    const T& first() const {
        if(size == 0){
            throw std::runtime_error("The vector does not contain any elements");
        }
        
        return data[0];
    }
    
    const T& last() const {
        if(size == 0){
            throw std::out_of_range("The vector does not contain any elements");
        }
        
        return data[size - 1];
    }
private:
    static constexpr unsigned int CAPACITY_GROWTH_FACTOR = 2;
    
    T* data;
    size_t size;
    size_t capacity;
    
    void resize(){
        T* temp;
        try{
            size_t newCapacity = (capacity == 0 ? 1 : capacity) * CAPACITY_GROWTH_FACTOR;
            temp = new T[newCapacity];
            for (int i = 0; i < size; i++) {
                temp[i] = data[i];
            }
            
            delete[] data;
            data = temp;
            capacity = newCapacity;
        }
        catch(const std::bad_alloc& e) {
            delete[] data;
            throw;
        }
            
    }
    
    void copy(const Vector& other){
        T* temp;
        try{
            
            temp = new T[other.capacity];
            for (int i = 0; i < other.size; i++) {
                temp[i] = other[i];
            }
            
            delete[] data;
            data = temp;
            size = other.size;
            capacity = other.capacity;
        }
        catch(const std::bad_alloc& e) {
            delete[] data;
            throw;
        }
    }
};
```