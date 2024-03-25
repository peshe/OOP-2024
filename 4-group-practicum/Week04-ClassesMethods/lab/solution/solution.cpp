#include <iostream>
#include <fstream>
#include <cstring>

constexpr std::size_t BUFFER_SIZE = 128;
constexpr std::size_t MAX_CAPACITY_IN_DISCO = 1000;

class Balloon 
{
private:
    char color[BUFFER_SIZE];
    double price;

public:
    Balloon() : Balloon("", 0.0) {}

    Balloon(const char* color, double price)
        : price(price) 
    {
        this->setColor(color);
    }

    void setColor(const char* color) 
    {
        strcpy(this->color, color);
    }

    const char* getColor() const 
    {
        return this->color;
    }

    void setPrice(double price) 
    {
        this->price = price;
    }

    double getPrice() const 
    {
        return this->price;
    }

    void readFromTextFile(std::ifstream& in) 
    {
        in.getline(this->color, BUFFER_SIZE);
        in >> this->price;
    }

    void writeToTextFile(std::ofstream& out) const
    {
        out << this->color << std::endl;
        out << this->price << std::endl;
    }

    void readFromBinaryFile(std::ifstream& in)
    {
        in.read(reinterpret_cast<char*>(this), sizeof(Balloon));
    }

    void writeToBinaryFile(std::ofstream& out) const 
    {
        out.write(reinterpret_cast<const char*>(this), sizeof(Balloon));
    }

    void print() const 
    {
        std::cout << "Baloon with color \"" << color << "\" costs " << price << std::endl;
    }
};

class Shisha 
{
private:
    char* brand;
    char* taste;
    double price;

    void deleteData() 
    {
        delete[] this->brand;
        this->brand = nullptr;

        delete[] this->taste;
        this->taste = nullptr;

        this->price = 0.0;
    }

public:
    Shisha() : brand(nullptr), taste(nullptr), price(0.0) {}

    Shisha(const char* brand, const char* taste, double price)
        : price(price), brand(nullptr), taste(nullptr)
    {
        this->setBrand(brand);

        if (!this->brand) 
        {
            deleteData();
            return;
        }

        this->setTaste(taste);

        if (!this->taste) 
        {
            deleteData();
            return;
        }
    }

    ~Shisha() 
    {
        this->deleteData();
    }

    void setBrand(const char* brand) 
    {
        delete[] this->brand;

        this->brand = new (std::nothrow) char[strlen(brand) + 1];

        if (!this->brand) 
        {
            std::cout << "Memory problem!" << std::endl;
            return;
        }

        strcpy(this->brand, brand);
    }

    const char* getBrand() const 
    {
        return this->brand;
    }

    void setTaste(const char* taste) 
    {
        delete[] this->taste;

        this->taste = new (std::nothrow) char[strlen(taste) + 1];

        if (!this->taste) 
        {
            std::cout << "Memory problem!" << std::endl;
            return;
        }

        strcpy(this->taste, taste);
    }

    const char* getTaste() const 
    {
        return this->taste;
    }

    void setPrice(double price) 
    {
        this->price = price;
    }

    double getPrice() const 
    {
        return this->price;
    }

    void readFromTextFile(std::ifstream& in) 
    {
        this->deleteData();

        char buffer[BUFFER_SIZE];
        in.getline(buffer, BUFFER_SIZE);

        this->brand = new (std::nothrow) char[strlen(buffer) + 1];
        if (!this->brand)
        {
            std::cout << "Memory problem!" << std::endl;
            return;
        }
        strcpy(this->brand, buffer);

        in.getline(buffer, BUFFER_SIZE);

        this->taste = new (std::nothrow) char[strlen(buffer) + 1];
        if (!this->taste)
        {
            this->deleteData();
            std::cout << "Memory problem!" << std::endl;
            return;
        }
        strcpy(this->taste, buffer);

        in >> this->price;
    }

    void writeToTextFile(std::ofstream& out) const 
    {
        out << this->brand << std::endl;
        out << this->taste << std::endl;
        out << this->price << std::endl;
    }

    void readFromBinaryFile(std::ifstream& in)
    {
        this->deleteData();

        std::size_t sizeBrand;
        in.read(reinterpret_cast<char*>(&sizeBrand), sizeof(std::size_t));

        this->brand = new (std::nothrow) char[sizeBrand + 1];
        if (!this->brand)
        {
            std::cout << "Memory problem!" << std::endl;
            return;
        }
        in.read(this->brand, sizeBrand);
        this->brand[sizeBrand] = '\0';

        std::size_t sizeTaste;
        in.read(reinterpret_cast<char*>(&sizeTaste), sizeof(std::size_t));

        this->taste = new (std::nothrow) char[sizeTaste + 1];
        if (!this->taste)
        {
            this->deleteData();
            std::cout << "Memory problem!" << std::endl;
            return;
        }
        in.read(this->taste, sizeTaste);
        this->taste[sizeTaste] = '\0';

        in.read(reinterpret_cast<char*>(&this->price), sizeof(double));
    }

    void writeToBinaryFile(std::ofstream& out) const
    {
        std::size_t sizeBrand = strlen(this->brand);
        std::size_t sizeTaste = strlen(this->taste);

        out.write(reinterpret_cast<const char*>(&sizeBrand), sizeof(std::size_t));
        out.write(this->brand, sizeBrand);

        out.write(reinterpret_cast<const char*>(&sizeTaste), sizeof(std::size_t));
        out.write(this->taste, sizeTaste);

        out.write(reinterpret_cast<const char*>(&this->price), sizeof(double));
    }

    void print() const 
    {
        std::cout << "Shisha from \"" << this->brand << "\" with a taste \"" << this->taste << "\" costs " << this->price << std::endl;
    }
};

class Alcohol 
{
private:
    char* name;
    double price;

    void deleteData() 
    {
        delete[] this->name;
        this->name = nullptr;

        this->price = 0.0;
    }

public:
    Alcohol() : name(nullptr), price(0.0) {}

    Alcohol(const char* name, double price)
        : price(price) 
    {
        this->setName(name);

        if (!this->name) 
        {
            this->price = 0;
            return;
        }
    }

    ~Alcohol() 
    {
        this->deleteData();
    }

    void setName(const char* name) 
    {
        delete[] this->name;

        this->name = new (std::nothrow) char[strlen(name) + 1];

        if (!this->name) 
        {
            std::cout << "Memory problem!" << std::endl;
            return;
        }

        strcpy(this->name, name);
    }

    const char* getName() const 
    {
        return this->name;
    }

    void setPrice(double price) 
    {
        this->price = price;
    }

    double getPrice() const 
    {
        return this->price;
    }

    void readFromTextFile(std::ifstream& in) 
    {
        this->deleteData();

        char buffer[BUFFER_SIZE];
        in.getline(buffer, BUFFER_SIZE);

        this->name = new (std::nothrow) char[strlen(buffer) + 1];
        if (!this->name)
        {
            std::cout << "Memory problem!" << std::endl;
            return;
        }
        strcpy(this->name, buffer);

        in >> this->price;
    }

    void writeToTextFile(std::ofstream& out) const 
    {
        out << this->name << std::endl;
        out << this->price << std::endl;
    }

    void readFromBinaryFile(std::ifstream& in)
    {
        this->deleteData();

        std::size_t sizeName;
        in.read(reinterpret_cast<char*>(&sizeName), sizeof(std::size_t));

        this->name = new (std::nothrow) char[sizeName + 1];
        if (!this->name)
        {
            std::cout << "Memory problem!" << std::endl;
            return;
        }
        in.read(this->name, sizeName);
        this->name[sizeName] = '\0';

        in.read(reinterpret_cast<char*>(&this->price), sizeof(double));
    }

    void writeToBinaryFile(std::ofstream& out) const
    {
        std::size_t sizeName = strlen(this->name);

        out.write(reinterpret_cast<const char*>(&sizeName), sizeof(std::size_t));
        out.write(this->name, sizeName);

        out.write(reinterpret_cast<const char*>(&this->price), sizeof(double));
    }

    void print() const 
    {
        std::cout << this->name << " costs " << this->price << std::endl;
    }
};

class NightClub 
{
private:
    Balloon balloons[MAX_CAPACITY_IN_DISCO]{};
    Shisha shishas[MAX_CAPACITY_IN_DISCO]{};
    Alcohol alcohols[MAX_CAPACITY_IN_DISCO]{};

    std::size_t balloonsSize;
    std::size_t shishasSize;
    std::size_t alcoholsSize;

public:
    NightClub() : balloonsSize(0), shishasSize(0), alcoholsSize(0) {}

    void addABaloon(const char* color, double price) 
    {
        if (balloonsSize == MAX_CAPACITY_IN_DISCO) 
        {
            std::cout << "No space for more balloons!" << std::endl;
            return;
        }

        balloons[balloonsSize].setColor(color);
        balloons[balloonsSize].setPrice(price);

        ++balloonsSize;
    }

    void addShisha(const char* brand, const char* taste, double price) 
    {
        if (shishasSize == MAX_CAPACITY_IN_DISCO) 
        {
            std::cout << "No space for more shishas" << std::endl;    
            return;
        }
        
        shishas[shishasSize].setBrand(brand);
        shishas[shishasSize].setTaste(taste);
        shishas[shishasSize].setPrice(price);

        ++shishasSize;
    }

    void addAlcohol(const char* name, double price) 
    {
        if (alcoholsSize == MAX_CAPACITY_IN_DISCO) 
        {
            std::cout << "No space for more alcohol drinks" << std::endl;
            return;
        }
        
        alcohols[alcoholsSize].setName(name);
        alcohols[alcoholsSize].setPrice(price);

        ++alcoholsSize;
    }

    void removeBaloon(const char* color) 
    {
        for (std::size_t i = 0; i < balloonsSize; ++i) 
        {
            if (strcmp(balloons[i].getColor(), color) == 0) 
            {
                --balloonsSize;
                if (balloonsSize != 0) 
                {
                    balloons[i].setColor(balloons[balloonsSize].getColor());
                    balloons[i].setPrice(balloons[balloonsSize].getPrice());
                }

                return;
            }
        }
    }

    void removeShisha(const char* brand) 
    {
        for (std::size_t i = 0; i < shishasSize; ++i) 
        {
            if (strcmp(shishas[i].getBrand(), brand) == 0) 
            {
                --shishasSize;
                if (shishasSize != 0) 
                {
                    shishas[i].setBrand(shishas[shishasSize].getBrand());
                    shishas[i].setTaste(shishas[shishasSize].getTaste());
                    shishas[i].setPrice(shishas[shishasSize].getPrice());
                }

                return;
            }
        }
    }

    void removeAlcohol(const char* name) 
    {
        for (std::size_t i = 0; i < alcoholsSize; ++i) 
        {
            if (strcmp(alcohols[i].getName(), name) == 0) 
            {
                --alcoholsSize;
                if (alcoholsSize != 0) 
                {
                    alcohols[i].setName(alcohols[alcoholsSize].getName());
                    alcohols[i].setPrice(alcohols[alcoholsSize].getPrice());
                }

                return;
            }
        }
    }

    bool checkForBaloonsCheaperThan(double price) {
        for (std::size_t i = 0; i < balloonsSize; ++i) 
        {
            if (balloons[i].getPrice() < price) 
            {
                return true;
            }
        }
        
        return false;
    }

    bool checkForShishaWithTaste(const char* taste) 
    {
        for (std::size_t i = 0; i < shishasSize; ++i) 
        {
            if (strcmp(shishas[i].getTaste(), taste) == 0) 
            {
                return true;
            }
        }

        return false;
    }

    bool checkForAlcoholWithPriceBetween(double min, double max) 
    {
        for (std::size_t i = 0; i < alcoholsSize; ++i) 
        {
            double currentPrice = alcohols[i].getPrice();
            if (min <= currentPrice && currentPrice <= max) 
            {
                return true;
            }
        }

        return false;
    }

    void print() const 
    {
        std::cout << "Baloons:" << std::endl;

        for (std::size_t i = 0; i < balloonsSize; ++i) 
        {
            balloons[i].print();
        }

        std::cout << std::endl << "Shishas:" << std::endl;

        for (std::size_t i = 0; i < shishasSize; ++i)
        {
            shishas[i].print();
        }

        std::cout << std::endl << "Alcohol drinks:" << std::endl;

        for (std::size_t i = 0; i < alcoholsSize; ++i) {
            alcohols[i].print();
        }

        std::cout << std::endl;
    }

    void readFromTextFile(std::ifstream& in)
    {
        in >> this->balloonsSize >> this->shishasSize >> this->alcoholsSize;

        for (std::size_t i = 0; i < this->balloonsSize; ++i)
        {
            in.ignore();
            this->balloons[i].readFromTextFile(in);
        }

        for (std::size_t i = 0; i < this->shishasSize; ++i)
        {
            in.ignore();
            this->shishas[i].readFromTextFile(in);
        }

        for (std::size_t i = 0; i < this->alcoholsSize; ++i)
        {
            in.ignore();
            this->alcohols[i].readFromTextFile(in);
        }
    }

    void writeToTextFile(std::ofstream& out) const
    {
        out << this->balloonsSize << " " << this->shishasSize << " " << this->alcoholsSize << std::endl;

        for (std::size_t i = 0; i < this->balloonsSize; ++i)
        {
            this->balloons[i].writeToTextFile(out);
        }

        for (std::size_t i = 0; i < this->shishasSize; ++i)
        {
            this->shishas[i].writeToTextFile(out);
        }

        for (std::size_t i = 0; i < this->alcoholsSize; ++i)
        {
            this->alcohols[i].writeToTextFile(out);
        }
    }

    void readFromBinaryFile(std::ifstream& in)
    {
        in.read(reinterpret_cast<char*>(&this->balloonsSize), sizeof(std::size_t));
        in.read(reinterpret_cast<char*>(&this->shishasSize), sizeof(std::size_t));
        in.read(reinterpret_cast<char*>(&this->alcoholsSize), sizeof(std::size_t));

        for (std::size_t i = 0; i < this->balloonsSize; ++i)
        {
            this->balloons[i].readFromBinaryFile(in);
        }

        for (std::size_t i = 0; i < this->shishasSize; ++i)
        {
            this->shishas[i].readFromBinaryFile(in);
        }

        for (std::size_t i = 0; i < this->alcoholsSize; ++i)
        {
            this->alcohols[i].readFromBinaryFile(in);
        }
    }

    void writeToBinaryFile(std::ofstream& out) const
    {
        out.write(reinterpret_cast<const char*>(&this->balloonsSize), sizeof(std::size_t));
        out.write(reinterpret_cast<const char*>(&this->shishasSize), sizeof(std::size_t));
        out.write(reinterpret_cast<const char*>(&this->alcoholsSize), sizeof(std::size_t));

        for (std::size_t i = 0; i < this->balloonsSize; ++i)
        {
            this->balloons[i].writeToBinaryFile(out);
        }

        for (std::size_t i = 0; i < this->shishasSize; ++i)
        {
            this->shishas[i].writeToBinaryFile(out);
        }

        for (std::size_t i = 0; i < this->alcoholsSize; ++i)
        {
            this->alcohols[i].writeToBinaryFile(out);
        }
    }
};

int main() 
{
    NightClub club;

    club.addABaloon("Purple", 15);
    club.addABaloon("Blue", 10);
    club.addABaloon("Green", 7);
    club.addABaloon("Red", 5);

    club.addShisha("Tangers", "Chocolate Ice Cream", 26);
    club.addShisha("Dark Side", "Grape", 20);
    club.addShisha("Ososuma", "Peach", 14);

    club.addAlcohol("Jack Daniels", 40);
    club.addAlcohol("Red Johnny Walker", 35);
    club.addAlcohol("Jim Beam", 30);
    club.addAlcohol("Absolute", 25);

    club.print();

    const char* discoTextFile = "disco.txt";
    const char* discoBinaryFile = "disco.bin";

    // std::ofstream out(discoTextFile);
    // if (!out)
    // {
    //     std::cout << "Problem while opening the file!" << std::endl;
    //     return 1;
    // }

    // club.writeToTextFile(out);

    std::ifstream in(discoTextFile);
    if (!in)
    {
        std::cout << "Problem while opening the file!" << std::endl;
        return 1;
    }

    NightClub clubFromTextFile;
    clubFromTextFile.readFromTextFile(in);

    std::cout << "------------------------------" << std::endl;
    std::cout << "CLUB FROM A TEXT FILE:" << std::endl;
    clubFromTextFile.print();

    // std::ofstream outBinary(discoBinaryFile, std::ios::binary);
    // if (!outBinary)
    // {
    //     std::cout << "Problem while opening the file!" << std::endl;
    //     return 1;
    // }

    // club.writeToBinaryFile(outBinary);

    std::ifstream inBinary(discoBinaryFile, std::ios::binary);
    if (!inBinary)
    {
        std::cout << "Problem while opening the file!" << std::endl;
        return 1;
    }

    NightClub clubFromBinaryFile;
    clubFromBinaryFile.readFromBinaryFile(inBinary);

    std::cout << "------------------------------" << std::endl;
    std::cout << "CLUB FROM A BINARY FILE:" << std::endl;
    clubFromBinaryFile.print();

    // club.removeBaloon("Red");
    // club.removeShisha("Ososuma");
    // club.removeAlcohol("Red Johnny Walker");

    // club.print();

    // std::cout << std::boolalpha << club.checkForBaloonsCheaperThan(7.5) << std::endl;
    // std::cout << club.checkForShishaWithTaste("Monster") << std::endl;
    // std::cout << club.checkForAlcoholWithPriceBetween(10, 15) << std::endl;

    return 0;
}