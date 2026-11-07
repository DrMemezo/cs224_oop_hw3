#pragma once

#include "Shape.hpp"

class Point : public Shape
{
private:
    int _x;
    int _y;
    const char SYMBOL = 'o';
public:
    // 
    Point(int x, int y);
    void draw(Grid& grid) override;
    // TODO: change this if needed
    ~Point() = default;
};

