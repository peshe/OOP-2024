#include <iostream>
#include <fstream>
#include "Dealership.hpp"

int main(){

    std::ifstream ifs("objects.txt");
    if(!ifs.is_open()) return -1;

    try{
        Dealership ds(10);
        ds.Add(Car(ifs), 1000.0);
        ds.Add(Car(ifs), 2000.0);
        ds.Add(Car(ifs), 3000.0);
        ds.PrintData("Volkswagen");
        ds.PrintData("Nissan");
        ds.PrintData(2500.0);
        ds.PrintData(1987u);
        ds.Sell(1);
        ds.PrintStatistics();
        ds.SaveData("copy.txt");
        ds.Sell(2);
        ds.PrintStatistics();
    }
    catch(std::bad_alloc const &ex){
        std::cerr << ex.what() << '\n';
    }
    catch(std::out_of_range const &ex){
        std::cerr << ex.what() << '\n';
    }
    catch(std::ios_base::failure const &ex){
        std::cerr << ex.what() << '\n';
    }
    catch(std::exception const &ex){
        std::cerr << ex.what() << '\n';
    }
    catch(...){
        std::cerr << "Exception occurred\n";
    }

    ifs.close();

    return 0;

}