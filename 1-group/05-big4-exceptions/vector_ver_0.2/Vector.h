#ifndef WEEK05_VECTOR_H
#define WEEK05_VECTOR_H
#include <fstream>
class Vector
{
public:
    Vector();
    ~Vector();
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    int& at(size_t position);
    void push_back(int element);
    void print(std::ostream& out) const;
private:
    int* arr;
    size_t size;
    size_t capacity;
    void clean();
    void copy(const Vector& other);
    void makeNewArr();
    void resize();
};

#endif //WEEK05_VECTOR_H
