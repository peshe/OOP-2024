#pragma once

class Song
{
private:
    static const unsigned int MAX_DURATION;
    char* name;
    char* genre;
    unsigned int duration;
    Song* next;

public:
    Song(const char* name, const char* genre, unsigned int duration);

    Song(const Song& other) = delete;
    Song& operator = (const Song& other) = delete;
    ~Song();

    const char* getName() const;
    const char* getGenre() const;
    int getDuration() const;
    Song* getNext() const;
    void setNext(Song* next);
};