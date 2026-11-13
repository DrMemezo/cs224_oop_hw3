#include "Point.hpp"
#include "Line.hpp"
#include "Grid.hpp"
#include "constants.hpp"

#include <stdexcept>
#include <sstream>
#include <cmath>

Line::Line(Point* p1, Point* p2)
  : Shape(nullptr), point1(p1), point2(p2)
{
  // This shouldnt happen but thats the point.
  if (!point1 || !point2) throw std::runtime_error("Points were null"); 

  double dy = static_cast<double>(point2->getY() - point1->getY());
  double dx = static_cast<double>(point2->getX() - point1->getX());
  if (dx == 0) {
    if (dy < 0) {
      gradient = -INFINITY;
    }
    else {
      gradient = INFINITY;
    }
  }
  else {
    gradient = dy/dx;
  }

  const double PI = std::acos(-1); 
  angle = std::atan2(dy, dx) * (180 / PI);

  // TODO: Get line_char from angle
  line_char = shape_symbols::HORIZONTAL;
}

void Line::draw(Grid& grid) const {
  double px1 = point1->getX();
  double px2 = point2->getX();

  double py1 = point1->getY();
  double py2 = point2->getY();

  double d = sqrt(pow(px2 - px1, 2) + pow(py2 - py1, 2)) ;
  int n = std::max(1, static_cast<int>(std::round(d)));

  for (int i = 0; i <= n; i++) {
    double t = static_cast<double>(i) / n;
    int x = static_cast<int>(std::round(px1 + t * (px2 - px1)));
    int y = static_cast<int>(std::round(py1 + t * (py2 - py1)));
    grid.setCell(x, y, line_char);
  }
} 

std::string Line::to_string() const { 
    std::stringstream ss;
    ss << "ID: " << ID << "\n" 
        << "\tPoint 1: " << point1->getID() << "\n" 
        << "\tPoint 2: " << point2->getID();
    return ss.str();
}


