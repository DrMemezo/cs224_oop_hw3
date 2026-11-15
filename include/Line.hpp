#pragma once
#include "Shape.hpp"

class Point;

class Line : public Shape {
  private:
    Point* point1;
    Point* point2;
    double gradient;
    /// From the first point to the second point
    /// IN DEGREES
    double angle;
    char line_char;

public:
  Line(Point* p1, Point* p2);

  void draw(Grid& grid) const override;
  std::string to_string() const override;

  // NOTE: I'll do this later if needed 
  Line(const Line& l) = delete;
  ~Line();


  std::string debug_str() const override;
};
