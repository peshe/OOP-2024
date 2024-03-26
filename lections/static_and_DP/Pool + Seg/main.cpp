#include <iostream>
#include <cstdlib>
#include "objPool.hpp"


using namespace std;
using fmi::oop::Worker;
using fmi::oop::ObjectPool;

void digChannel()
{
    try {
        Worker& w1 = ObjectPool::getPool().hireWorker();
        Worker& w2 = ObjectPool::getPool().hireWorker();

        w2.digForMe();
        for (int i = 0; i < 3; ++i)
            w1.digForMe();
        w2.digForMe();

        ObjectPool::getPool().dismissWorker(w1);
        w1.digForMe();

        if (rand() % 2) {
            ObjectPool::getPool().dismissWorker(w2);
        }
        if (rand() % 5 == 2) {
            ObjectPool::getPool().dismissWorker(w1);
        }
    }
    catch (const char* text) {
        cout << "Problem: " << text;
    }
}

int main()
{
    for (int i = 0; i < 10; ++i)
        digChannel();
}
