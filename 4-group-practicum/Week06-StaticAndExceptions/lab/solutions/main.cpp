#include <exception>
#include <iostream>
#include <fstream>

#include "Computer.h"


int main() {
  try {
    Computer original(
      "Maybe Dell", "Probably Intel", 1080, 4000, 10, 3, 820.3f, 1
    );
    Computer directCopy = original;
  
    std::ofstream outputTextFile("test.txt");
    original.saveAsText(outputTextFile);
    directCopy.saveAsText(outputTextFile);
    outputTextFile.close();
  
    std::ifstream inputTextFile("test.txt");
    Computer copyThroughText = Computer::loadFromText(inputTextFile);
    Computer copyThroughText2 = Computer::loadFromText(inputTextFile);
    inputTextFile.close();
  
    std::ofstream outputBinaryFile("test.bin", std::ios::binary);
    original.saveAsBinary(outputBinaryFile);
    copyThroughText2.saveAsBinary(outputBinaryFile);
    outputBinaryFile.close();
  
    std::ifstream inputBinaryFile("test.bin", std::ios::binary);
    Computer copyThroughBinary = Computer::loadFromBinary(inputBinaryFile);
    Computer copyThroughBinary2 = Computer::loadFromBinary(inputBinaryFile);
    inputBinaryFile.close();
  
    original.saveAsText(std::cout);
    directCopy.saveAsText(std::cout);
    copyThroughText.saveAsText(std::cout);
    copyThroughText2.saveAsText(std::cout);
    copyThroughBinary.saveAsText(std::cout);
    copyThroughBinary2.saveAsText(std::cout);

    Computer incorrect(nullptr, nullptr, 0, 0, 0, 0, 0.0f, 0);
  }
  catch (const std::exception& e) {
    std::cout << e.what() << '\n';
    return 1;
  }
  catch (const char* msg) {
    std::cout << msg << '\n';
    return 1;
  }
  
  return 0;
}
