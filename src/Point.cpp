#include "Point.hpp"
#include "Grid.hpp"

Point::Point(int x, int y) 
    : Shape(nullptr), _x(x), _y(y) 
{
    
}

void Point::draw(Grid& grid) {
    // This can throw an exception
    // Which ill let get to main so that it can do 
    // Error handling.
    grid.setCell(_x, _y, SYMBOL);
}
