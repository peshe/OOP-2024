// Example task that was developed during the seminar.

#include <iostream>

using namespace std;

// Renamed from "Point" to "Point3D". Better naming.
struct Point3D {
	double x;
	double y;
	double z;
};

// Declarations.
double distance(double x1, double y1, double x2, double y2, double z1, double z2);
double distance(Point3D p1, Point3D p2);
void readFromConsole(Point3D& p);

int main()
{
	Point3D p1, p2;

	readFromConsole(p1);
	readFromConsole(p2);

	double d = distance(p1, p2);
	cout << "The distance between the first and second point is: " << d << endl;

	return 0;
}

double distance(double x1, double y1, double x2, double y2, double z1, double z2)
{
	double distance = sqrt(
		(x2 - x1) * (x2 - x1) +
		(y2 - y1) * (y2 - y1) +
		(z2 - z1) * (z2 - z1)
	);

	return distance;
}

double distance(Point3D p1, Point3D p2)
{
	double distance = sqrt(
		(p2.x - p1.x) * (p2.x - p1.x) +
		(p2.y - p1.y) * (p2.y - p1.y) +
		(p2.z - p1.z) * (p2.z - p1.z)
	);

	return distance;
}

// We use the "&" here to "pass by reference",
// meaning that variables that are passed as parameters to this function
// will persist the changes made to them after the function call ends.
void readFromConsole(Point3D& p) {
	cout << "Please add x, y, z coordinates for the first point:" << endl;
	cin >> p.x >> p.y >> p.z;
}
