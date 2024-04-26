#pragma once
#include "song.h"
#include <iostream>

class Playlist {
private:
    Song* head;

public:
    Playlist();

    Playlist(const Playlist& other) = delete;
    Playlist& operator = (const Playlist& other) = delete;

    ~Playlist();

    Playlist& operator += (const Song& songToAdd);

    Song& operator [] (const char* name);
    const Song& operator [] (const char* name) const;

    Song& operator [] (std::size_t index);
    const Song& operator [] (std::size_t index) const;

    Playlist& operator -= (const char* name);

    operator bool();

    void operator () () const;

    unsigned int totalDuration() const;

    std::size_t songCount() const;
};
// };
// Пример за използване в main
// cpp
// Copy code
// int main() {
//     try {
//         Playlist p;
//         p.addSong("Song 1", "Pop", 300);
//         p.addSong("Song 2", "Rock", 250);
//         p.addSong("Song 3", "Jazz", 200);
//         p.addSong("Song 4", "Classical", 350);
//         p.addSong("Song 5", "Metal", 180);

//         std::cout << "Total Duration: " << p.totalDuration() << " seconds\n";
//         std::cout << "Total Songs: " << p.songCount() << std::endl;

//         p.print();

//         p.removeSong("Song 3");
//         p.print();

//         Song* song = p.findSongByName("Song 2");
//         if (song) {
//             std::cout << "Found: " << song->getName() << " - " << song->getGenre() << ", " << song->getDuration() << " seconds\n";
//         }
//     } catch (const std::exception& e) {
//         std::cerr << "Exception: " << e.what() << std::endl;
//     }

//     return 0;
// }