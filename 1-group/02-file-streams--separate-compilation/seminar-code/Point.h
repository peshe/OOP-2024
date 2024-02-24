//#pragma once
// or

#ifndef __POINT_HEADER_INCLUDED__
#define __POINT_HEADER_INCLUDED__ 

struct Point
{
    double x = 0.0; // default (starting) value of 0.0
    double y = 0.0; // default (starting) value of 0.0
};

void printPoint(const Point& pt);

#endif // __POINT_HEADER_INCLUDED__ 
