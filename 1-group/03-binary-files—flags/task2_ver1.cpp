#include <iostream>
#include <fstream>

const float pi = 3.14;
struct Point {
    float x;
    float y;
};

float calcDistance(const Point& p1,const Point& p2) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return std::sqrt(dx*dx+dy*dy);
}


// Bubble sort written from your colleague
// The only difference is since we want to "reuse the original" points, we will sort only the positions into a new array
void sortPoints(const Point* const points ,size_t* positions, const int& numPoints, const Point& center) {
    for (size_t i = 0; i < numPoints - 1; ++i) {
        for (size_t j = 0; j <numPoints - i - 1; ++j) {
            float distanceA = calcDistance(points[positions[j]], center);
            float distanceB = calcDistance(points[positions[j + 1]], center);
            if (distanceA < distanceB) {
                size_t temp = positions[j];
                positions[j] = positions[j + 1];
                positions[j + 1] = temp;
            }
        }
    }
}

// Replace the points outside the circle with the center point
void pointsOutsideCircle(Point*& points,const size_t& numPoints, const Point& center, float radius ) {
    for (size_t i = 0; i < numPoints; i++)
    {
        float distance = calcDistance(points[i], center);
        if (distance > radius) {
            points[i] = center;
        }
    }
}

int main() {
    // Test file preparation
    std::ofstream outFileTest("input-points.dat", std::ios::binary);
    for (int i = 0; i < 100; ++i) {
        Point temp{(float)i, float(i)};
        outFileTest.write(reinterpret_cast<char*>(&temp), sizeof(Point));
    }
    outFileTest.close();
    // End testing data...


    std::ifstream inFile("input-points.dat", std::ios::binary);
    if (!inFile) {
        std::cerr << "Could not open file!" << std::endl;
        return -1;
    }
    // Find the size of the file and return go back to the beginning
    inFile.seekg(0, std::ios::end);
    size_t fileSize = inFile.tellg();

    // If the file is not correct, just exit
    // Why 0 != fileSize is better?
    if (0 != fileSize && fileSize % sizeof(Point) != 0) {
        std::cerr << "Invalid file" << std::endl;
        return -1;
    }
    const size_t numPoints = fileSize / sizeof(Point);
	
	// memory leak?
    Point* points = new Point[numPoints];
    size_t* positions = new size_t[numPoints];
    for (size_t i = 0; i < numPoints; i++) {
        positions[i] = i;
    }
    inFile.seekg(0, std::ios::beg);
    inFile.read(reinterpret_cast<char*>(points), fileSize );

    inFile.close();

    // Find the center of the points
    Point center = { 0, 0 };
    for (int i = 0; i < numPoints; ++i) {
        center.x += points[i].x;
        center.y += points[i].y;
    }
    center.x /= numPoints;
    center.y /= numPoints;

    std::ofstream outBin("input-points.dat", std::ios::binary);
    if (!outBin) {
        std::cerr << "Could not open file for writing!" << std::endl;
        delete[] points;
        return -1;
    }

    sortPoints(points, positions, numPoints, center);
    std::cout << "Farthest points: " << std::endl;
    for (size_t i = 0; i < 3; i++) {
        std::cout << points[positions[i]].x << " " << points[positions[i]].y << std::endl;
    }

    std::cout << "Input radius: " << std::endl;
    float radius;
    std::cin >> radius;

    pointsOutsideCircle(points, numPoints, center, radius);

    // We should update only the new points, using tellp to the correct position
    // One hacky way is to update the points into the array and directly write it into the file
    // Hacky, but much faster
    std::ofstream ouBin("input-points.dat", std::ios::binary | std::ios::trunc);
    if (!ouBin) {
        std::cout << "Could not open file for writing!" << std::endl;
        delete[] points;
        delete[] positions;
        return -1;
    }

    ouBin.write(reinterpret_cast<char*>(points), fileSize );
    ouBin.close();

    // Read again the entire file, with the updated values
    std::ifstream inFile1("input-points.dat", std::ios::binary);
    inFile1.read(reinterpret_cast<char*>(points), fileSize);
    inFile1.close();

    for (int i = 0; i < numPoints; ++i)
        std::cout << points[i].x << " " << points[i].y << std::endl;

    delete[] points;
    delete[] positions;
    return 0;
}