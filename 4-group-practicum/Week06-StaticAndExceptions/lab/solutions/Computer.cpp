#include "Computer.h"

#include <cstddef>
#include <cstring>
#include <fstream>
#include <new>


static constexpr std::size_t BUFFER_SIZE = 10000u;
/*static*/ unsigned Computer::nComputers = 0;

static const char* copyString(const char* str)
{
  if (str == nullptr) { return nullptr; }

  char* newStr = new(std::nothrow) char[strlen(str) + 1];
  if (newStr != nullptr) {
    strcpy(newStr, str);
  }
  return newStr;
}

Computer::Computer(
    const char* brand, const char* processor, unsigned video,
    unsigned hdd, unsigned weight, unsigned batteryLife, float price,
    unsigned quantity
) :
  serialNumber(nComputers++), brand(copyString(brand)),
  processor(copyString(processor)), video(video), hdd(hdd), weight(weight),
  batteryLife(batteryLife), price(price), quantity(quantity)
{
  if (this->brand == nullptr || this->processor == nullptr) {
    freeMemory();
    throw "Memory allocation problem!";
  }
}

Computer::Computer(const Computer& other) :
  Computer(
    other.brand, other.processor, other.video, other.hdd, other.weight,
    other.batteryLife, other.price, other.quantity
  )
{}

Computer::~Computer()
{
  freeMemory();
}

/*static*/ Computer Computer::loadFromText(std::istream& istream) {
  unsigned serialNumber = 0;
  istream >> serialNumber;
  istream.ignore();

  char stringBuffer[BUFFER_SIZE];
  istream.getline(stringBuffer, BUFFER_SIZE, '\n');
  const char* brand = copyString(stringBuffer);
  istream.getline(stringBuffer, BUFFER_SIZE, '\n');
  const char* processor = copyString(stringBuffer);

  unsigned video = 0;
  istream >> video;

  unsigned hdd = 0;
  istream >> hdd;

  unsigned weight = 0;
  istream >> weight;

  unsigned batteryLife = 0;
  istream >> batteryLife;

  float price = 0.0f;
  istream >> price;

  unsigned quantity = 0;
  istream >> quantity;

  return Computer(
    brand, processor, video, hdd, weight, batteryLife, price, quantity
  );
}

void Computer::saveAsText(std::ostream& ostream) {
    ostream << serialNumber << '\n' << brand << '\n' << processor << '\n';
    ostream << video << ' ' << hdd << ' ' << weight << ' ' << batteryLife << ' ';
    ostream << price << ' ' << quantity << '\n';
}

void Computer::freeMemory()
{
  delete[] brand;
  delete[] processor;
}
