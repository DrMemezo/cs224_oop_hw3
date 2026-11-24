#include "Point.hpp"
#include "Angle.hpp"
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
  
  p1->incrementReferences();
  p2->incrementReferences();

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

  angle = std::atan2(dy, dx) * (180 / PI);

  if (angle <= 95 && angle >= 85 || 
      angle >= -95 && angle <= -85) {

      line_char = shape_symbols::VERTICAL;
  }
  else if (angle >= -5 && angle <= 5 || angle >= 175 || angle <= -175) {
    line_char = shape_symbols::HORIZONTAL;
  }
  else if (angle > 5 && angle < 85 || angle < -95 && angle > -175){
    line_char = shape_symbols::DIAGONAL_DR;
  }
  else {
    line_char = shape_symbols::DIAGONAL_LU;
  }
}

void Line::drawSegment(Grid& grid, 
                        int px1, int py1, 
                        int px2, int py2,
                        char line_char)
{

  double d = sqrt(pow(px2 - px1, 2) + pow(py2 - py1, 2)) ;
  int n = std::max(1, static_cast<int>(std::round(d)));

  for (int i = 0; i <= n; i++) {
    double t = static_cast<double>(i) / n;
    int x = static_cast<int>(std::round(px1 + t * (px2 - px1)));
    int y = static_cast<int>(std::round(py1 + t * (py2 - py1)));
    grid.setCell(x, y, line_char);
  }
}

void Line::draw(Grid& grid) const {
  int px1 = point1->getX();
  int px2 = point2->getX();

  int py1 = point1->getY();
  int py2 = point2->getY();

  drawSegment(grid, px1, py1, px2, py2, line_char);
} 

std::string Line::to_string() const { 
    std::stringstream ss;
    ss << "ID: " << ID << " Line\n" 
        << "\tPoint 1 (ID): " << point1->getID() << "\n" 
        << "\tPoint 2 (ID): " << point2->getID();
    return ss.str();
}

std::string Line::debug_str() const {
    std::stringstream ss;
    ss << "ID: " << ID << " Line\n" 
        << "\tPoint 1 (ID): " << point1->getID() << "\n" 
        << "\tPoint 2 (ID): " << point2->getID() << "\n"
        << "\tGradient: " << gradient << "\n"
        << "\tAngle (deg): " << angle;
    return ss.str();
}

Line::~Line() {
  point1->decrementReferences();
  point2->decrementReferences();
}

const Point* Line::getStart() const { return point1; }
const Point* Line::getEnd() const {return point2;}
double Line::getAngle() const {return angle;}
char Line::getLineChar() const {return  line_char;}


void Line::setStart(Point* newStart) {
  point1->decrementReferences();
  point1 = newStart;
  point1->incrementReferences();
}
void Line::setEnd(Point* newEnd) {

  point2->decrementReferences();
  point2 = newEnd;
  point2->incrementReferences();
}

bool Line::sameAs(const Shape* other) const {
  if (this == other) return true;

  const Line* l = dynamic_cast<const Line*>(other);
  if (!l) return false;

  return (*point1 == *l->point1 && *point2 == *l->point2) ||
         (*point1 == *l->point2 && *point2 == *l->point1);
}

Angle* operator+(Line& lhs, Line& rhs) {
  if (&lhs == &rhs) 
    throw std::invalid_argument("Cannot add the same line!");
  Angle* a = new Angle(&lhs, &rhs);
  return a;
}
