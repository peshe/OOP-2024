#include <iostream>
#include <fstream> // you need this if you want to work with files

struct Money
{
    unsigned int levs;
    unsigned int stotinkas;
};

void writeMoney (std::ofstream& out, const Money& money);

int main ()
{
    // o - output
    // f - file
    // stream
    std::ofstream tempFile("tempInfo.txt"); 

    if (!tempFile.is_open()) // always check if the opening is successfull
    {
        std::cout << "Problem while opening the file" << std::endl;
        return 1;
    }

    tempFile << "New info\n"; // writng a string
    tempFile << 5 + 7 << "\n"; // writing a number

    Money money{1, 20};
    writeMoney(tempFile, money); // writing an object

    tempFile.close(); // always close the streams


    std::ofstream importantFile("importantInfo.txt", std::ios::app); // always add the flag `app` (append) when you don't want to lose the old information

    if (!importantFile) // other way to check if the opening is successfull
    {
        std::cout << "Problem while opening the file" << std::endl;
        return 1;
    }

    importantFile << "I am not the first line of the file\n";

    importantFile.close();

    return 0;
}

void writeMoney (std::ofstream& out, const Money& money)
{
    out << money.levs << " levs and " << money.stotinkas << " stotinkas\n";
}