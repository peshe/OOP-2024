#include <iostream>
#include <cstring>
#include <cassert>
#include <fstream>

void copyString(char*& destination, const char* source)
{
    destination = new (std::nothrow) char[strlen(source) + 1];
    if (!destination)
    {
        std::cout << "Memory problem!" << std::endl;
        return;
    }

    strcpy(destination, source);
}

const unsigned int MAX_MINUTES_AND_SECONDS = 60;
const std::size_t INITIAL_CAPACITY = 2;
const std::size_t INCREASE_STEP = 2;
const std::size_t BUFFER_SIZE = 128;

struct Duration
{
    unsigned int minutes;
    unsigned int seconds;

    Duration() : Duration(0, 0) {}

    Duration(unsigned int minutes, unsigned int seconds)
        : minutes(minutes), seconds(seconds) {}

    bool isValid() const
    {
        return this->minutes < MAX_MINUTES_AND_SECONDS && 
               this->seconds < MAX_MINUTES_AND_SECONDS;
    }

    void print() const
    {
        std::cout << this->minutes << ":" << this->seconds << std::endl;
    }

    void readFromTextFile(std::ifstream& in)
    {
        char delimiter;
        in >> this->minutes >> delimiter >> this->seconds;
    }

    void writeToTextFile(std::ofstream& out) const
    {
        out << this->minutes << ":" << this->seconds << std::endl;
    }

    void readFromBinaryFile(std::ifstream& in)
    {
        in.read(reinterpret_cast<char*>(this), sizeof(Duration));
    }

    void writeToBinaryFile(std::ofstream& out) const
    {
        out.write(reinterpret_cast<const char*>(this), sizeof(Duration));
    }
};

class Song
{
private:
    char* name;
    char* genre;
    Duration duration;

    void deallocate()
    {
        delete[] this->name;
        delete[] this->genre;
    }

    void copy(const Song& other)
    {
        assert(other.name != nullptr);
        assert(other.genre != nullptr);
        assert(other.duration.isValid());

        copyString(this->name, other.name);
        copyString(this->genre, other.genre);
        this->duration = other.duration;
    }

public:
    Song() : name(nullptr), genre(nullptr) {}

    Song(const char* name, const char* genre, const Duration& duration)
        : name(nullptr), genre(nullptr), duration(duration) 
    {
        this->setName(name);
        this->setGenre(genre);
    }

    Song(const Song& other)
    {
        this->copy(other);
    }

    Song& operator = (const Song& other)
    {
        if (this != &other)
        {
            this->deallocate();
            this->copy(other);
        }

        return *this;
    }

    void setName(const char* name)
    {
        assert(name != nullptr);

        delete[] this->name;
        copyString(this->name, name);
    }

    void setGenre(const char* genre)
    {
        assert(name != nullptr);

        delete[] this->genre;
        copyString(this->genre, genre);
    }

    void setDuration(const Duration& duration)
    {
        this->duration = duration;
    }

    const char* getName() const
    {
        return this->name;
    }

    const char* getGenre() const
    {
        return this->genre;
    }

    Duration getDuration() const
    {
        return this->duration;
    }

    ~Song()
    {
        this->deallocate();
    }

    void readFromTextFile(std::ifstream& in)
    {
        this->deallocate();

        char buffer[BUFFER_SIZE];
        in.getline(buffer, BUFFER_SIZE);

        this->name = new (std::nothrow) char[strlen(buffer) + 1];
        if (!this->name)
        {
            std::cout << "Memory problem!" << std::endl;
            return;
        }
        strcpy(this->name, buffer);

        in.getline(buffer, BUFFER_SIZE);

        this->genre = new (std::nothrow) char[strlen(buffer) + 1];
        if (!this->genre)
        {
            this->deallocate();
            std::cout << "Memory problem!" << std::endl;
            return;
        }
        strcpy(this->genre, buffer);

        this->duration.readFromTextFile(in);
    }

    void writeToTextFile(std::ofstream& out) const
    {
        out << this->name << std::endl;
        out << this->genre << std::endl;
        this->duration.writeToTextFile(out);
    }

    void readFromBinaryFile(std::ifstream& in)
    {
        this->deallocate();

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

        std::size_t sizeGenre;
        in.read(reinterpret_cast<char*>(&sizeGenre), sizeof(std::size_t));

        this->genre = new (std::nothrow) char[sizeGenre + 1];
        if (!this->genre)
        {
            this->deallocate();
            std::cout << "Memory problem!" << std::endl;
            return;
        }
        in.read(this->genre, sizeGenre);
        this->genre[sizeGenre] = '\0';

        this->duration.readFromBinaryFile(in);
    }

    void writeToBinaryFile(std::ofstream& out) const
    {
        std::size_t sizeName = strlen(this->name);
        std::size_t sizeGenre = strlen(this->genre);

        out.write(reinterpret_cast<const char*>(&sizeName), sizeof(std::size_t));
        out.write(this->name, sizeName);

        out.write(reinterpret_cast<const char*>(&sizeGenre), sizeof(std::size_t));
        out.write(this->genre, sizeGenre);

        this->duration.writeToBinaryFile(out);
    }

    void print() const
    {
        std::cout << "Name: " << this->name << std::endl;
        std::cout << "Genre: " << this->genre << std::endl;
        std::cout << "Duration: ";
        this->duration.print();
    }
};

class Playlist
{
private:
    Song* songs;
    std::size_t size;
    std::size_t capacity;
    char* name;

    void copy(const Playlist& other)
    {
        copyString(name, other.name);

        this->songs = new (std::nothrow) Song[other.capacity];
        if (!this->songs)
        {
            std::cout << "Memory problem!" << std::endl;
            return;
        }

        for (std::size_t i = 0; i < other.size; ++i)
        {
            this->songs[i] = other.songs[i];
        }

        this->capacity = other.capacity;
        this->size = other.size;
    }

    void deallocate()
    {
        delete[] this->songs;
        delete[] this->name;
    }

    void resize()
    {
        Song* newSongs = new (std::nothrow) Song[this->capacity * INCREASE_STEP];
        if (!newSongs)
        {
            std::cout << "Memory problem!" << std::endl;
            return;
        }

        for (std::size_t i = 0; i < this->size; ++i)
        {
            newSongs[i] = this->songs[i];
        }

        delete[] this->songs;
        this->songs = newSongs;
        this->capacity *= INCREASE_STEP;
    }

    /**
     * @brief A method for getting the index of a song
     * 
     * @param songName the song's name we are checking
     * @return the index of the song if it is contained
     * @return -1 if the song is not contained
     */
    int getSongIndex(const char* songName)
    {
        assert(songName != nullptr);

        for(std::size_t i = 0; i < this->size; ++i)
        {
            if (strcmp(songName, this->songs[i].getName()) == 0)
            {
                return i;
            }
        }

        return -1;
    }

public:
    Playlist(const char* playlistName)
    {
        copyString(this->name, playlistName);

        this->songs = new (std::nothrow) Song[INITIAL_CAPACITY];
        if (!this->songs)
        {
            std::cout << "Memory problem!" << std::endl;
            return;
        }

        this->capacity = INITIAL_CAPACITY;
        this->size = 0;
    }

    Playlist(const Playlist& other)
    {
        this->copy(other);
    }

    Playlist& operator = (const Playlist& other)
    {
        if (this != &other)
        {
            this->deallocate();
            this->copy(other);
        }

        return *this;
    }

    ~Playlist()
    {
        this->deallocate();
    }

    /**
     * @brief A method for adding a song to the playlist
     * @details The song should be added to the playlist only if 
     * there isn't a song with the same name
     * 
     * @param songToAdd the song that should be added
     */
    void addSong(const Song& songToAdd)
    {
        if (this->getSongIndex(songToAdd.getName()) == -1)
        {
            if (this->size == this->capacity)
            {
                this->resize();
            }
            this->songs[this->size++] = songToAdd;
        }
    }

    /**
     * @brief A method for removing a song from the playlist
     * 
     * @param songName the song's name we are removing
     * @return true if the removal is successfull
     * @return false if the removal is not successfull
     */
    bool removeSong(const char* songName)
    {
        int songIndex = this->getSongIndex(songName);

        if (songIndex == -1)
        {
            return false;
        }

        this->songs[songIndex] = this->songs[this->size - 1];
        --this->size;

        return true;
    }

    /**
     * @brief A method for printing information about the playlist
     * 
     */
    void printPlaylistInfo()
    {
        std::cout << "SIZE: " << this->size << std::endl;
        std::cout << "CAPACITY: " << this->capacity << std::endl;
        for (std::size_t i = 0; i < this->size; ++i)
        {
            std::cout << "SONG #" << i+1 << std::endl;
            this->songs[i].print();
        }
    }

    void readFromTextFile(std::ifstream& in)
    {
        this->deallocate();

        char buffer[BUFFER_SIZE];
        in.getline(buffer, BUFFER_SIZE);

        this->name = new (std::nothrow) char[strlen(buffer) + 1];
        if (!this->name)
        {
            std::cout << "Memory problem!" << std::endl;
            return;
        }
        strcpy(this->name, buffer);

        in >> this->size >> this->capacity;

        this->songs = new (std::nothrow) Song[this->capacity];
        if (!this->songs)
        {
            delete[] this->name;
            std::cout << "Memory problem!" << std::endl;
            return;
        }

        for (std::size_t i = 0; i < this->size; ++i)
        {
            in.ignore();
            this->songs[i].readFromTextFile(in);
        }
    }

    void writeToTextFile(std::ofstream& out) const
    {
        out << this->name << std::endl;
        out << this->size << " " << this->capacity << std::endl;

        for (std::size_t i = 0; i < this->size; ++i)
        {
            this->songs[i].writeToTextFile(out);
        }
    }

    void readFromBinaryFile(std::ifstream& in)
    {
        this->deallocate();

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

        in.read(reinterpret_cast<char*>(&this->size), sizeof(std::size_t));
        in.read(reinterpret_cast<char*>(&this->capacity), sizeof(std::size_t));

        this->songs = new (std::nothrow) Song[this->capacity];
        if (!this->songs)
        {
            delete[] this->name;
            std::cout << "Memory problem!" << std::endl;
            return;
        }

        for (std::size_t i = 0; i < this->size; ++i)
        {
            this->songs[i].readFromBinaryFile(in);
        }
    }

    void writeToBinaryFile(std::ofstream& out) const
    {
        std::size_t sizeName = strlen(this->name);

        out.write(reinterpret_cast<const char*>(&sizeName), sizeof(std::size_t));
        out.write(this->name, sizeName);

        out.write(reinterpret_cast<const char*>(&this->size), sizeof(std::size_t));
        out.write(reinterpret_cast<const char*>(&this->capacity), sizeof(std::size_t));

        for (std::size_t i = 0; i < this->size; ++i)
        {
            this->songs[i].writeToBinaryFile(out);
        }
    }
};


int main()
{
    Song song1("Can't let you go", "Rock", Duration(4, 17));
    Song song2("E.T.", "Pop", Duration(3, 40));
    Song song3("Da ne pitat", "Rap", Duration(3, 20));
    Song song4("Vodka s uteha", "Pop-folk", Duration(4, 7));
    Song song5("Senorita", "Pop", Duration(3, 25));

    Playlist mishMash("Mish-Mash");
    mishMash.addSong(song1);
    mishMash.addSong(song2);
    mishMash.addSong(song3);
    mishMash.addSong(song4);
    mishMash.addSong(song5);

    mishMash.printPlaylistInfo();

    // std::ofstream out("MyPlaylist.txt");
    // if (!out)
    // {
    //     std::cout << "Problem while opening the file!" << std::endl;
    //     return 1;
    // }

    // mishMash.writeToTextFile(out);

    // std::ifstream in("MyPlaylist.txt");
    // if (!in)
    // {
    //     std::cout << "Problem while opening the file!" << std::endl;
    //     return 1;
    // }

    // Playlist playlistFromTextFile("tekstov");
    // playlistFromTextFile.readFromTextFile(in);

    // playlistFromTextFile.printPlaylistInfo();

    // std::ofstream outBinary("MyPlaylist.bin");
    // if (!outBinary)
    // {
    //     std::cout << "Problem while opening the file!" << std::endl;
    //     return 1;
    // }

    // mishMash.writeToBinaryFile(outBinary);

    // std::ifstream inBinary("MyPlaylist.bin");
    // if (!inBinary)
    // {
    //     std::cout << "Problem while opening the file!" << std::endl;
    //     return 1;
    // }

    // Playlist playlistFromBinaryFile("binaren");
    // playlistFromBinaryFile.readFromBinaryFile(inBinary);

    // playlistFromBinaryFile.printPlaylistInfo();

    Playlist copyWithoutGreshki = mishMash;
    copyWithoutGreshki.removeSong("Nqkakva greshna");
    copyWithoutGreshki.printPlaylistInfo();

    Playlist onlyOneSong("One song only");
    onlyOneSong.addSong(song1);
    onlyOneSong.removeSong("Can't let you go");
    onlyOneSong.printPlaylistInfo();

    Playlist emptyPlaylist("Empty");
    std::cout << std::boolalpha << emptyPlaylist.removeSong("neshto") << std::endl;

    return 0;
}