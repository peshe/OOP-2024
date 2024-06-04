# Композиция (флагане). Статични полета и методи на класове

Долу ще намерите кода от семинара. Темите, които покрихме са:
0. Проекти и първа защита.
1. Какво е композицията (флагането).
2. Поредност на създаване и унищожение на обекти при композиция на класове.
3. Статични полета и методи.

<small><b>Пример за композиция на класове Point и Color в клас Circle</b></small>
```c++
#include <iostream>

using namespace std;

class Point {
private:
	static int count;

	double x;
	double y;

public:

	Point(double x = 0, double y = 0) : x(x), y(y)
	{
		count++;
		cout << "Point constructor called with: (" << x << ", " << y << ")" << endl;
	}

	~Point() {
		count--;
		cout << "Point destructor called for: (" << x << ", " << y << ")" << endl;
	}

	Point(const Point& other) : x(other.x), y(other.y) {
		count++;
		cout << "Point copy constructor called with: (" << x << ", " << y << ")" << endl;
	}

	Point& operator=(const Point& other) {
		if (this == &other) {
			return *this;
		}

		x = other.x;
		y = other.y;

		cout << "Point operator= constructor called with: (" << x << ", " << y << ")" << endl;
		return *this;
	}

	double getX() const {
		return x;
	}

	double getY() const {
		return y;
	}

	static int getCount() {
		return count;
	}
};

int Point::count = 0;

class Color {
private:
	int red;
	int green;
	int blue;

public:
	Color(int r, int g, int b) :red(r), green(g), blue(b) {
		cout << "Color constructor called with: (" << red << ", " << green << ", " << blue << ")" << endl;
	}

	~Color() {
		cout << "Color destructor called for: (" << red << ", " << green << ", " << blue << ")" << endl;
	}

	Color(const Color& other) : red(other.red), green(other.green), blue(other.blue) {
		cout << "Color copy constructor called with: (" << red << ", " << green << ", " << blue << ")" << endl;
	}

	Color& operator=(const Color& other) {
		if (this == &other) {
			return *this;
		}

		red = other.red;
		green = other.green;
		blue = other.blue;

		cout << "Color operator= constructor called with: (" << red << ", " << green << ", " << blue << ")" << endl;
		return *this;
	}
};

class Circle {
private:
	double radius;
	Point center;
	Color color;

public:
	Circle(double radius, const Point& center, const Color& color) :radius(radius), center(center), color(color) {
		cout << "Circle constructor called with radius: " << radius << endl;
	}

	~Circle() {
		cout << "Circle destructor called with radius: " << radius << endl;
	}

	Circle(const Circle& other) : radius(other.radius), center(other.center), color(other.color) {
		cout << "Circle copy constructor called with radius: " << radius << endl;
	}

	Circle& operator=(const Circle& other) {
		if (this == &other) {
			return *this;
		}

		radius = other.radius;
		center = other.center;
		color = other.color;

		cout << "Circle operator= constructor called with radius:" << radius << endl;

		return *this;
	}



	double getRadius() const {
		return radius;
	}

	Point getCenter() const {
		return center;
	}
};

void f() {
	Point center = Point(0, 0);
	Color color = Color(255, 255, 255);
	Circle c = Circle(10, center, color);
	new Point(15, 15);
}

int main()
{
	f();
	Point p;
	cout << Point::getCount() << endl;
	// Point::count = 53; invalid. count is private.
	Point p2;
	Point p3;

	return 0;
}

```