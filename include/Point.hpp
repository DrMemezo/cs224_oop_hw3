#pragma once

#include "Shape.hpp"
class Line;
#include <string>

class Point : public Shape
{
private:
    int _x;
    int _y;
    int num_of_references;
public:
    Point(int x, int y);
    void draw(Grid& grid) const override;
    void incrementReferences();
    void decrementReferences();

    // NOTE: I'll do this later if needed
    Point(const Point& p) = delete;

    friend Line* operator+(Point& lhs, Point& rhs);

    /// @brief gets string representation of a point: "Point (x, y)"
    std::string to_string() const override;

    int getX() const; 
    int getY() const;
};

