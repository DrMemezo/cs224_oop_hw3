#pragma once

#include "Shape.hpp"
#include <string>

class Point : public Shape
{
private:
    int _x;
    int _y;
public:
    // 
    Point(int x, int y);
    void draw(Grid& grid) const override;

    /// @brief gets string representation of a point: "Point (x, y)"
    std::string to_string() const override;

    // TODO: change this if needed
    ~Point() = default;

    int getX() const; 
    int getY() const; 
};

