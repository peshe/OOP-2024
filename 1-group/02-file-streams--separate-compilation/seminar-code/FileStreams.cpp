#include <iostream>
#include <fstream>

int main()
{
    /// Text file example
    std::ofstream out("file.txt"); // Step 1 
    if (!out) 
    { // Step 2 
        std::cout << "Couldn't open file for writing!" << std::endl;
    } 
    else 
    { 
        out << "This text will go in the file" << std::endl; // Step 3 
        out.close(); // Step 4 
    }

    /// Binary file write example
    const int MAX_LEN = 128;
    int num = 42; 
    char str[MAX_LEN]; 
    strcpy(str, "Test string");

    // Step 1 
    std::ofstream outBin("data.bin");

    // Step 2 
    if (!outBin) 
    { 
        std::cout << "Couldn't open file for writing!" << std::endl;
    } 
    else 
    { 
        // Step 3 
        // Writing primitive data types 
        outBin.write(reinterpret_cast<const char*>(&num), sizeof(num)); 

        // Writing C strings involves writing their length first 
        // and then writing the actual string	 
        int len = strlen(str); 
        outBin.write(reinterpret_cast<const char*>(&len), sizeof(len)); 
        outBin.write(str, len); 

        // Step 4 
        outBin.close(); 
    }

    /// Binary file read example
    int readNum; 
    char readStr[MAX_LEN] = {}; 

    // Step 1 
    std::ifstream inBin("data.bin");

    // Step 2 
    if (!inBin) 
    { 
        std::cout << "Couldn't open file for reading!" << std::endl;
    } 
    else 
    { 
        // Step 3 
        // Reading primitive data types 
        inBin.read(reinterpret_cast<char*>(&readNum), sizeof(readNum)); 

        std::cout << "The number " << readNum << " was read from `data.bin`" << std::endl;

        // Reading C strings involves reading their length first 
        // and then reading the actual string	 
        int len; 
        inBin.read(reinterpret_cast<char*>(&len), sizeof(len)); 

        if (len < MAX_LEN - 1) 
        { 
            inBin.read(readStr, len); 
            readStr[len+1] = '\0';
        } 

        // Step 4 
        inBin.close();

        std::cout << "The following text with length " << len << " was read from `data.bin`" << std::endl;
        std::cout << readStr << std::endl;
    }

	return 0;
}
