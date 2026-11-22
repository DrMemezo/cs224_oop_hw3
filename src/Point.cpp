#include "Point.hpp"
#include "Line.hpp"
#include "Grid.hpp"

#include "constants.hpp"
#include <stdexcept>
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
    ss << "ID: " << ID << " "
            <<  "Point (" << _x << "," << _y << ")";
    return ss.str();
}



int Point::getX() const {return _x;}
int Point::getY() const {return _y;}

Line* operator+(Point& lhs, Point& rhs) {
    if (lhs._x == rhs._x && lhs._y == rhs._y) {
        throw std::invalid_argument("Cannot make a line from the same points!");
    }

    Line* l = new Line(&lhs, &rhs);

    return l;

}

bool Point::operator==(const Point& rhs) const {
  return (_x == rhs._x && _y == rhs._y); 
}
