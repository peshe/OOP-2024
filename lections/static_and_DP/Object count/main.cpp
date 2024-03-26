#include <iostream>
#include "ObjectCounter.hpp"

using std::cout;
using std::endl;
using fmi::oop::ObjectCounter;

ObjectCounter global;

int main()
{
    cout << "Global: " << global.getObjID() << " count: "
         << ObjectCounter::getCurrentCount() << endl;

    {
        ObjectCounter O1;
        ObjectCounter O2 = O1;
        cout << "O1 : " << O1.getObjID() << " O2: " << O2.getObjID() << " count: ";
        cout << ObjectCounter::getCurrentCount() << endl;
    }
    cout << "After local block count is ";
    cout << ObjectCounter::getCurrentCount() << endl;

    ObjectCounter *counters = new ObjectCounter[10];

    cout << "10 new dynamic objects are created. Count is: "
         << ObjectCounter::getCurrentCount() << endl;

    cout << "Id of first is " << counters[0].getObjID()
         << " and of the last: " << counters[9].getObjID() << endl;


    ObjectCounter *counters2 = new ObjectCounter[5];
    cout << "5 more are created. Count: "
         << ObjectCounter::getCurrentCount() << endl;

    cout << "Object IDs: ";
    for (int i = 0; i < 5; ++i) {
        cout << counters2[i].getObjID() << " ";
    }
    cout << "\n";

    delete[] counters;
    cout << "First 10 is deleted. Count: "
         << ObjectCounter::getCurrentCount() << endl;

    delete[] counters2;
    cout << "All are deleted. Count: "
         <<ObjectCounter::getCurrentCount() << endl;

    return 0;
}
