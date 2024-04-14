#include <iostream>
#include <fstream>

#include "Computer.h"


int main() {
  Computer original(
    "Maybe Dell", "Probably Intel", 1080, 4000, 10, 3, 820.3f, 1
  );
  Computer directCopy = original;

  std::ofstream outputTextFile("test.txt");
  original.saveAsText(outputTextFile);
  directCopy.saveAsText(outputTextFile);
  outputTextFile.close();

  std::ifstream inputTextFile("test.txt");
  Computer indirectCopy = Computer::loadFromText(inputTextFile);
  Computer indirectCopy2 = Computer::loadFromText(inputTextFile);
  inputTextFile.close();

  original.saveAsText(std::cout);
  directCopy.saveAsText(std::cout);
  indirectCopy.saveAsText(std::cout);
  indirectCopy2.saveAsText(std::cout);

  try {
    Computer incorrect(nullptr, nullptr, 0, 0, 0, 0, 0.0f, 0);
  }
  catch (const char* msg) {
    std::cout << msg << '\n';
  }
  
  return 0;
}
