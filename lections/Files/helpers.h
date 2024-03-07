#pragma once

#ifndef _HELPERS_HEADER_INCLUDED
#define _HELPERS_HEADER_INCLUDED

#include <cctype>
#include <iostream>

inline void skipSpaces()
{
    while (isspace(std::cin.get()))
        ;
    std::cin.unget();
}


#endif //_HELPERS_HEADER_INCLUDED