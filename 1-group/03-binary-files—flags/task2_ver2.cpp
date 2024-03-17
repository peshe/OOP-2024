#include <iostream>
#include <fstream>

struct Point
{
	float x;
	float y;
};

void fillArrayFromFile(std::ifstream& inBin, Point* outArrPoints, size_t numPoints);
Point centerOfMass(const Point* arrPoints, size_t numPoints);
float sqDistance(const Point& p1, const Point& p2);
void printThreeFarthest(const Point* arrPoints, size_t numPoints, const Point& center);
void printPoint(const Point& pt);
bool isOutsideCircle(const Point& point, const Point& center, float radius);
void centerizeFarther(Point* inOutArr, size_t numPoints, const Point& ptCenter, float radius);
void printArrayToFileAndStdOut(std::ofstream& outBin, const Point* arrPoints, size_t numPoints);

void createInitialDatFile();

int main()
{
	// for testing purposes
	//createInitialDatFile();

	std::ifstream inBin("input-points.dat", std::ios::binary);
	if (!inBin)
	{
		std::cout << "Failed to open file for reading!\n";
		return 1;
	}

	// Go to the end of the file, get the last byte position, go back to the beginning
	inBin.seekg(0, std::ios::end);
	size_t fileSize = inBin.tellg();
	inBin.seekg(0, std::ios::beg);

	// fileSize should be a multiple of sizeof(Point)
	if (fileSize != 0 && fileSize % sizeof(Point) != 0)
	{
		std::cout << "Invalid file!\n";
		inBin.close();
		return 2;
	}

	size_t numPoints = fileSize / sizeof(Point);
	Point* arrPoints = new (std::nothrow) Point[numPoints];
	if (!arrPoints)
	{
		inBin.close();
		return 3;
	}

	// Read from the file
	fillArrayFromFile(inBin, arrPoints, numPoints);
	inBin.close();

	// Find the center of mass
	Point ptCenter = centerOfMass(arrPoints, numPoints);

	// Print three farthest
	printThreeFarthest(arrPoints, numPoints, ptCenter);

	float radius;
	std::cout << "Radius: ";
	std::cin >> radius;
	
	centerizeFarther(arrPoints, numPoints, ptCenter, radius);

	std::ofstream outBin("input-points.dat", std::ios::binary | std::ios::trunc);
	printArrayToFileAndStdOut(outBin, arrPoints, numPoints);
	outBin.close();

	delete[] arrPoints;

	return 0;
}

void fillArrayFromFile(std::ifstream& inBin, Point* outArrPoints, size_t numPoints)
{
	for (size_t i = 0; i < numPoints; i++)
	{
		Point& currPt = outArrPoints[i];
		inBin.read(reinterpret_cast<char*>(&(currPt.x)), sizeof(currPt.x));
		inBin.read(reinterpret_cast<char*>(&(currPt.y)), sizeof(currPt.y));
	}
}

Point centerOfMass(const Point* arrPoints, size_t numPoints)
{
	Point ptCenter = {0, 0};

	for (size_t i = 0; i < numPoints; i++)
	{
		ptCenter.x += arrPoints[i].x;
		ptCenter.y += arrPoints[i].y;
	}

	if ( numPoints != 0 )
	{
		ptCenter.x /= numPoints;
		ptCenter.y /= numPoints;
	}

	return ptCenter;
}

float sqDistance(const Point& p1, const Point& p2)
{
	float dx = p2.x - p1.x;
	float dy = p2.y - p1.y;
	return dx * dx + dy * dy;
}

void printThreeFarthest(const Point* arrPoints, size_t numPoints, const Point& center)
{
	Point* arrCopy = new (std::nothrow) Point[numPoints];
	if (!arrCopy)
		return;

	// Copy the original array
	for (size_t i = 0; i < numPoints; i++)
		arrCopy[i] = arrPoints[i];
	
	// Bubble sort with ONLY 3 outer steps, no need for more
	for (size_t i = 0; i < 3; i++)
		for (size_t j = 0; j < numPoints - i; j++)
			if (sqDistance(arrCopy[j], center) < sqDistance(arrCopy[i], center))
				std::swap(arrCopy[i], arrCopy[j]);

	// Last three points are farthest
	printPoint(arrCopy[numPoints - 1]);
	std::cout << "\n";
	printPoint(arrCopy[numPoints - 2]);
	std::cout << "\n";
	printPoint(arrCopy[numPoints - 3]);
	std::cout << "\n";

	delete[] arrCopy;
}

void printPoint(const Point& pt)
{
	std::cout << pt.x << ", " << pt.y;
}

bool isOutsideCircle(const Point& point, const Point& center, float radius)
{
	return sqDistance(point, center) > radius * radius;
}

void centerizeFarther(Point* inOutArr, size_t numPoints, const Point& ptCenter, float radius)
{
	for (size_t i = 0; i < numPoints; i++)
		if (isOutsideCircle(inOutArr[i], ptCenter, radius))
			inOutArr[i] = ptCenter;
}

void printArrayToFileAndStdOut(std::ofstream& outBin, const Point* arrPoints, size_t numPoints)
{
	for (size_t i = 0; i < numPoints; i++)
	{
		Point currPt = arrPoints[i];

		outBin.write(reinterpret_cast<const char*>(&(currPt.x)), sizeof(currPt.x));
		outBin.write(reinterpret_cast<const char*>(&(currPt.y)), sizeof(currPt.y));

		printPoint(currPt);
		std::cout << "\n";
	}
}

// for testing purposes only
void createInitialDatFile()
{
	const Point arrPoints[] = { {1,2}, {3,4}, {5,6}, {7,8}, {-2,1}, {3,5}, {10, 12}, {-5, 10} };
	std::ofstream outBin("input-points.dat", std::ios::binary | std::ios::trunc);
	printArrayToFileAndStdOut(outBin, arrPoints, 8);
	outBin.close();
}
