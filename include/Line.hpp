#pragma once
#include "Shape.hpp"

class Point;
class Angle;

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
  static void drawSegment(Grid& grid, 
                          int px1, int py1, 
                          int px2, int py2, char line_char);
  std::string to_string() const override;

  // NOTE: I'll do this later if needed 
  Line(const Line& l) = delete;
  ~Line();


  std::string debug_str() const override;
  const Point* getStart() const;
  const Point* getEnd() const;
  char getLineChar() const;

  double getAngle() const;

  void setStart(Point* newStart);
  void setEnd(Point* newEnd);

  friend Angle* operator+(Line& lhs, Line& rhs);

  bool sameAs(const Shape* other) const override;
};
