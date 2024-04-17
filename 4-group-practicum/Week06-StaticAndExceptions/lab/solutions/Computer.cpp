#include "Computer.h"

#include <cassert>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <new>


static constexpr std::size_t BUFFER_SIZE = 10000u;
/*static*/ unsigned Computer::nComputers = 0;

static const char* copyString(const char* str)
{
  if (str == nullptr) {
    return nullptr;
  }

  char* newStr = new (std::nothrow) char[strlen(str) + 1];
  if (newStr != nullptr) {
    strcpy(newStr, str);
  }

  return newStr;
}

Computer::Computer(
  const char* brand, const char* processor, unsigned video, unsigned hdd,
  unsigned weight, unsigned batteryLife, float price, unsigned quantity
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

Computer::~Computer() noexcept
{
  freeMemory();
}

/*static*/ Computer Computer::loadFromText(std::istream& istream)
{
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

  Computer result(brand, processor, video, hdd, weight, batteryLife, price, quantity);

  delete[] brand;
  delete[] processor;

  if (!istream) throw "Problem reading from text file!";

  return result;
}

void Computer::saveAsText(std::ostream& ostream) const
{
  ostream << serialNumber << '\n' << brand << '\n' << processor << '\n';
  ostream << video << ' ' << hdd << ' ' << weight << ' ' << batteryLife << ' ';
  ostream << price << ' ' << quantity << '\n';
}

static const char* loadCstringFromBinary(std::istream& istream)
{
  std::size_t len = 0;
  istream.read(reinterpret_cast<char*>(&len), sizeof(len));

  char* str = new char[len + 1];
  istream.read(str, len);
  str[len] = '\0';

  return str;
}

/*static*/ Computer Computer::loadFromBinary(std::istream& istream)
{
  unsigned serialNumber = 0;
  istream.read(reinterpret_cast<char*>(&serialNumber), sizeof(serialNumber));

  const char* brand = loadCstringFromBinary(istream);
  const char* processor = loadCstringFromBinary(istream);

  unsigned video = 0;
  istream.read(reinterpret_cast<char*>(&video), sizeof(video));

  unsigned hdd = 0;
  istream.read(reinterpret_cast<char*>(&hdd), sizeof(hdd));

  unsigned weight = 0;
  istream.read(reinterpret_cast<char*>(&weight), sizeof(weight));

  unsigned batteryLife = 0;
  istream.read(reinterpret_cast<char*>(&batteryLife), sizeof(batteryLife));

  float price = 0.0f;
  istream.read(reinterpret_cast<char*>(&price), sizeof(price));

  unsigned quantity = 0;
  istream.read(reinterpret_cast<char*>(&quantity), sizeof(quantity));

  Computer result(brand, processor, video, hdd, weight, batteryLife, price, quantity);

  delete[] brand;
  delete[] processor;

  if (!istream) throw "Problem reading from binary file!";

  return result;
}

static void saveCstringAsBinary(const char* str, std::ostream& ostream)
{
  assert(str != nullptr);

  std::size_t len = strlen(str);
  ostream.write(reinterpret_cast<const char*>(&len), sizeof(len));
  ostream.write(str, len);
}

void Computer::saveAsBinary(std::ostream& ostream) const {
  ostream.write(reinterpret_cast<const char*>(&serialNumber), sizeof(serialNumber));
  saveCstringAsBinary(brand, ostream);
  saveCstringAsBinary(processor, ostream);
  ostream.write(reinterpret_cast<const char*>(&video), sizeof(video));
  ostream.write(reinterpret_cast<const char*>(&hdd), sizeof(hdd));
  ostream.write(reinterpret_cast<const char*>(&weight), sizeof(weight));
  ostream.write(reinterpret_cast<const char*>(&batteryLife), sizeof(batteryLife));
  ostream.write(reinterpret_cast<const char*>(&price), sizeof(price));
  ostream.write(reinterpret_cast<const char*>(&quantity), sizeof(quantity));
}

void Computer::freeMemory() noexcept
{
  delete[] brand;
  delete[] processor;
}
