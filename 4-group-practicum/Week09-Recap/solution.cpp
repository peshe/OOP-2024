#include <iostream>
#include <string>
#include <cassert>

typedef std::string MyString;

class Vehicle
{
private:
    MyString m_registration;
    MyString m_description;
    std::size_t m_space;

public:
    Vehicle(const char* registration, const char* description, std::size_t space)
        : m_registration(registration), m_description(description), m_space(space) {}

    const char* registration() const
    {
        return this->m_registration.c_str();
    }

    const char* description() const
    {
        return this->m_description.c_str();
    }

    std::size_t space() const
    {
        return this->m_space;
    }

    void print() const
    {
        std::cout << m_registration << " " << m_description << std::endl;
    }
};

class Garage
{
private:
    std::size_t m_size;
    Vehicle** vehicles;
    std::size_t currentPos;
    std::size_t currentSize;

public:
    Garage(std::size_t size)
        : m_size(size), currentPos(0), currentSize(0)
    {
        this->vehicles = new Vehicle*[size];
        for (std::size_t i = 0; i < size; ++i)
        {
            vehicles[i] = nullptr;
        }
    }

    Garage(const Garage& other) = delete;
    Garage& operator = (const Garage& other) = delete;

    ~Garage()
    {
        delete[] vehicles;
    }

    void print() const
    {
        for (std::size_t i = 0; i < currentPos; ++i)
        {
            vehicles[i]->print();
        }

        std::cout << "Space left: " << m_size - currentSize << std::endl;
    }

    void insert(Vehicle& v)
    {
        if (currentSize + v.space() > m_size)
        {
            throw std::out_of_range("Nema mqsto w garaja, brat");
        }

        vehicles[currentPos++] = &v;
        currentSize += v.space();
    }

    void erase(const char* registration)
    {
        for (std::size_t i = 0; i < currentPos; ++i)
        {
            if (registration == vehicles[i]->registration())
            {
                currentSize -= vehicles[i]->space();
                std::swap(vehicles[i], vehicles[currentPos - 1]);
                --currentPos;
            }
        }
    }

    const Vehicle& at(std::size_t pos) const
    {
        if (pos >= currentPos)
        {
            throw std::out_of_range("mn golqm index, brat");
        }

        return *vehicles[pos];
    }

    const Vehicle& operator[](std::size_t pos) const
    {
        assert(pos < currentPos);

        return *vehicles[pos];
    }

    bool empty() const
    {
        return currentSize == 0;
    }

    std::size_t size() const
    {
        return currentPos;
    }

    void clear()
    {
        for (std::size_t i = 0; i < currentPos; ++i)
        {
            vehicles[i] = nullptr;
        }

        currentPos = 0;
        currentSize = 0;
    }

    const Vehicle* find(const char* registration) const
    {
        for (std::size_t i = 0; i < currentPos; ++i)
        {
            if (registration == vehicles[i]->registration())
            {
                return vehicles[i];
            }
        }

        return nullptr;
    }
};

class VehicleRepository
{
private:
    static constexpr std::size_t INITIAL_CAPACITY = 2;
    static constexpr std::size_t INCREATE_STEP = 2;

    Vehicle** vehicles;
    std::size_t capacity;
    std::size_t size;

    void resize()
    {
        Vehicle** newVehicles = new Vehicle*[capacity * INCREATE_STEP];

        for (std::size_t i = 0; i < size; ++i)
        {
            newVehicles[i] = vehicles[i];
        }

        delete[] vehicles;
        vehicles = newVehicles;
        capacity *= INCREATE_STEP;
    }

    void copy(const VehicleRepository& other)
    {
        this->vehicles = new Vehicle*[other.capacity];

        for (std::size_t i = 0; i < other.size; ++i)
        {
            this->vehicles[i] = new Vehicle(*other.vehicles[i]);
        }

        this->size = other.size;
        this->capacity = other.capacity;
    }

    void deallocate()
    {
        for (std::size_t i = 0; i < size; ++i)
        {
            delete vehicles[i];
        }

        delete[] vehicles;
    }

public:
    VehicleRepository()
        : size(0), capacity(INITIAL_CAPACITY)
    {
        vehicles = new Vehicle*[INITIAL_CAPACITY];
    }

    VehicleRepository(const VehicleRepository& other)
    {
        this->copy(other);
    }

    VehicleRepository& operator = (const VehicleRepository& other)
    {
        if (this != &other)
        {
            this->deallocate();
            this->copy(other);
        }

        return *this;
    }

    ~VehicleRepository()
    {
        this->deallocate();
    }

    void createVehicle(const char* registration, const char* description, std::size_t space)
    {
        if (size == capacity)
        {
            resize();
        }
        vehicles[size] = new Vehicle(registration, description, space);
        ++size;
    }

    Vehicle* operator [] (std::size_t index) 
    {
        if (index >= size)
        {
            return nullptr;
        }

        return vehicles[index];
    }
};

int main ()
{
    VehicleRepository repo;

    repo.createVehicle("B3745PK", "pezho", 2);
    repo.createVehicle("CA1234BA", "seat", 1);
    repo.createVehicle("CB5555BB", "avtobus", 8);

    Garage g(10);

    g.insert(*repo[0]);
    g.insert(*repo[1]);
    g.insert(*repo[2]);

    g.print();

    return 0;
}