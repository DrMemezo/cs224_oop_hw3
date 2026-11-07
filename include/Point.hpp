#pragma once

#include "Shape.hpp"

class Point : public Shape
{
private:
    int x;
    int y;
public:
    // 
    Point(int x, int y);
    ~Point();
};

