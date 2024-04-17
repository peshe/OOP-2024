#include <iosfwd>

class Computer
{
public:
  Computer(
    const char* brand, const char* processor, unsigned video,
    unsigned hdd, unsigned weight, unsigned batteryLife, float price,
    unsigned quantity
  );

  Computer(const Computer&);
  ~Computer() noexcept;

  static Computer loadFromText(std::istream&);
  void saveAsText(std::ostream&) const;

  static Computer loadFromBinary(std::istream&);
  void saveAsBinary(std::ostream&) const;

  const char* getBrand()      const { return brand; }
  const char* getProcessor()  const { return processor; }
  unsigned getVideo()         const { return video; }
  unsigned getHdd()           const { return hdd; }
  unsigned getWeight()        const { return weight; }
  unsigned getBatteryLife()   const { return batteryLife; }
  float getPrice()            const { return price; }
  unsigned getQuantity()      const { return quantity; }

private:
  Computer& operator= (const Computer&) = delete;
  void freeMemory() noexcept;

private:
  static unsigned nComputers;
  const unsigned serialNumber;
  const char* const brand;
  const char* const processor;
  const unsigned video;
  const unsigned hdd;
  const unsigned weight;
  const unsigned batteryLife;
  const float price;
  const unsigned quantity;
};
