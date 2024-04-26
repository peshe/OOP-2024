#include "playlist.h"
#include <cstring>
#include <stdexcept>

Playlist::Playlist()
    : head(nullptr) {}

Playlist::~Playlist() 
{
    Song* current = head;
    while (current != nullptr) 
    {
        Song* next = current->getNext();
        delete current;
        current = next;
    }
}

Playlist& Playlist::operator += (const Song& songToAdd)
{
    Song* newSong = new Song(songToAdd.getName(), songToAdd.getGenre(), songToAdd.getDuration());
    if (!head) 
    {
        head = newSong;
    } 
    else 
    {
        Song* current = head;
        while (current->getNext()) 
        {
            current = current->getNext();
        }
        current->setNext(newSong);
    }

    return *this;
}

Song& Playlist::operator [] (const char* name) 
{
    Song* current = head;
    while (current) 
    {
        if (strcmp(current->getName(), name) == 0) 
        {
            return *current;
        }
        current = current->getNext();
    }

    throw std::invalid_argument("There is no song with such name in the playlist");
}

const Song& Playlist::operator [] (const char* name) const
{
    Song* current = head;
    while (current) 
    {
        if (strcmp(current->getName(), name) == 0) 
        {
            return *current;
        }
        current = current->getNext();
    }

    throw std::invalid_argument("There is no song with such name in the playlist");
}

Song& Playlist::operator [] (std::size_t index) 
{
    int count = 0;
    Song* current = head;
    while (current != nullptr) 
    {
        if (count == index) 
        {
            return *current;
        }
        current = current->getNext();
        count++;
    }

    throw std::out_of_range("Index out of range");
}

const Song& Playlist::operator [] (std::size_t index) const
{
    int count = 0;
    Song* current = head;
    while (current != nullptr) 
    {
        if (count == index) 
        {
            return *current;
        }
        current = current->getNext();
        count++;
    }
    
    throw std::out_of_range("Index out of range");
}

Playlist& Playlist::operator -= (const char* name) 
{
    Song* current = head;
    Song* prev = nullptr;
    while (current) 
    {
        if (strcmp(current->getName(), name) == 0) 
        {
            if (prev) 
            {
                prev->setNext(current->getNext());
            } 
            else 
            {
                head = current->getNext();
            }
            delete current;
            return *this;
        }
        prev = current;
        current = current->getNext();
    }

    return *this;
}

Playlist::operator bool ()
{
    return !this->head;
}

void Playlist::operator () () const
{
    Song* current = this->head;

    while (current)
    {
        std::cout << current->getName() << std::endl;
        current = current->getNext();
    }
}

unsigned int Playlist::totalDuration() const 
{
    unsigned int total = 0;
    Song* current = head;

    while (current) 
    {
        total += current->getDuration();
        current = current->getNext();
    }

    return total;
}

std::size_t Playlist::songCount() const 
{
    std::size_t count = 0;
    Song* current = head;

    while (current) 
    {
        ++count;
        current = current->getNext();
    }

    return count;
}