#include <iostream>
#include <string>

struct Movie
{
    std::string name;
    Movie* nextMovie;

    Movie(const std::string& name, Movie* nextMovie = nullptr)
        : name(name), nextMovie(nextMovie) {}
};

class MovieCollection
{
private:
    Movie* collectionStart;

public:
    MovieCollection(Movie* collectionStart)
        : collectionStart(collectionStart) {}

    MovieCollection(const MovieCollection& other) = delete;
    MovieCollection& operator = (const MovieCollection& other) = delete;

    ~MovieCollection()
    {
        Movie* currentMovie = collectionStart;
        while (currentMovie)
        {
            Movie* movieToDelete = currentMovie;

            currentMovie = currentMovie->nextMovie;

            delete movieToDelete;
        }
    }

    std::size_t size() const
    {
        std::size_t size = 0;

        Movie* currentMovie = collectionStart;
        while (currentMovie)
        {
            ++size;
            currentMovie = currentMovie->nextMovie;
        }

        return size;
    }

    void print() const
    {
        if (!collectionStart)
        {
            return;
        }

        Movie* currentMovie = collectionStart;
        std::cout << currentMovie->name;

        while (currentMovie->nextMovie)
        {
            std::cout << " -> " << currentMovie->nextMovie->name;

            currentMovie = currentMovie->nextMovie;
        }
        std::cout << std::endl;
    }
};

int main ()
{
    // Generally not a good practice to allocate the memory in main 
    // and deallocate it in the destructor of another class
    // Done here for simplicity
    
    Movie* hp = new Movie("HP1", new Movie("HP2", new Movie("HP3", new Movie("HP4", new Movie("HP5")))));

    MovieCollection hpCollection(hp);

    std::cout << "Size: " << hpCollection.size() << std::endl;
    hpCollection.print();

    return 0;
}