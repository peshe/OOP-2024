#include "playlist.h"

int main ()
{
    Playlist p;

    p += Song("Can't let you go", "Rock", 257);
    p += Song("E.T.", "Pop", 220);
    p += Song("Da ne pitat", "Rap", 200);
    p += Song("Vodka s uteha", "Pop-folk", 247);
    p += Song("Senorita", "Pop", 205);

    if (p)
    {
        std::cout << "The playlist is empty\n"; 
    }
    else
    {
        std::cout << "The playlist is not empty\n";
        p();
    }

    return 0;
}