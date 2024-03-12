#include <iostream>
#include <fstream>

using namespace std;


#include "address.h"
#include "student.h"

using namespace fmi::oop;


static Student test()
{
    Address adr;
    Student sb("John Doe", adr, Subject::INFORMATICS, 43123, 1);
    return sb;
}


static void print(Student s)
{
    cout << "Printing data ....";
    s.print();
}


int main()
{
    try {
        Student pesho;
        pesho.setName("Pesho");
        pesho.print();

        Address adr("Sofia", "Studentski", 52, 1700);
        Student gosho("Gosho", adr, Subject::INFORMATICS, 43000, 3, true);
        gosho.print();
        Student nasko = gosho;
        print(test());

        try {
            Student badGuy("WD", adr, Subject::INFORMATICS, 1000, true);
        }
        catch (const char* what) {
            cout << "Bad guy catched : " << what << endl;
        }

    catch (const std::bad_alloc&) {
        cout << "Some memory was not allocated properly.";
    }
    return 0;
}
