#include <iostream>
#include <fstream>
#include <iomanip>

struct Point {
    float x;
    float y;
    float z;
};

float distance(const Point& p) {
    return p.x * p.x + p.y * p.y + p.z * p.z;
}

int main() {
    Point p[64];
    char fileName[33];
    size_t indexPosition = 0;
    int n;
    std::cin >> fileName;
    std::ifstream fin;
    fin.open(fileName);
    if (!fin) {
        std::cerr<<"Such file does not exist or not able to be opened"<<std::endl;
        return -1;
    }
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin>>p[i].x>>p[i].y>>p[i].z;
    }
    fin.close();
    float minDistance = distance(p[0]);
    for (int i = 1; i < n; i++) {
        float currentDistance = distance(p[i]);
        if (minDistance > currentDistance) {
            minDistance = currentDistance;
            indexPosition = i;
        }
    }
    std::ofstream fout;
    fout.open(fileName, std::ios::app);
    if (!fout) {
        std::cerr<<"Such file does not exist or not abl to be opened"<<std::endl;
        return -1;
    }
    fout << "The expected result is ("
         << std::setprecision(2)
         << std::fixed
         << sqrt(minDistance)
         << std::setprecision(-1) //hacky way to restore precision
         << std::defaultfloat
         << ") with position ("
         << p[indexPosition].x
         << ", "
         << p[indexPosition].y
         << ", "
         << p[indexPosition].z
         << ')'<<std::endl;
    fout.close();

}
