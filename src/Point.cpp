#include "Point.hpp"
#include "Grid.hpp"
#include "constants.hpp"
#include <sstream>

Point::Point(int x, int y) 
    : Shape(nullptr), _x(x), _y(y) 
{
    
}

void Point::draw(Grid& grid) const {
    // This can throw an exception
    // Which ill let get to main so that it can do 
    // Error handling.
    grid.setCell(_x, _y, shape_symbols::POINT);
}

std::string Point::to_string() const {
    std::stringstream ss;
    ss << "Point (" << _x << "," << _y << ")";
    return ss.str();
}



int Point::getX() const {return _x;}
int Point::getY() const {return _y;}