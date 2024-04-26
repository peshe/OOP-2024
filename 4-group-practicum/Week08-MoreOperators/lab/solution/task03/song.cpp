#include "song.h"
#include <stdexcept>
#include <cstring>

const unsigned int Song::MAX_DURATION = 600;

Song::Song(const char* name, const char* genre, unsigned int duration)
{
    if (!name || !genre || duration > MAX_DURATION)
    {
        throw std::invalid_argument("Invalid song parameters");
    }

    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    try 
    {
        this->genre = new char[strlen(genre) + 1];
    }
    catch (std::bad_alloc& ba)
    {
        delete[] this->name;
        throw ba;
    }
    strcpy(this->genre, genre);

    this->duration = duration;
    this->next = nullptr;
}

Song::~Song() 
{
    delete[] this->name;
    delete[] this->genre;
}

const char* Song::getName() const 
{ 
    return name;
}

const char* Song::getGenre() const 
{ 
    return genre; 
}

int Song::getDuration() const 
{ 
    return duration; 
}

Song* Song::getNext() const 
{ 
    return next;
}

void Song::setNext(Song* next) 
{ 
    this->next = next; 
}