#pragma once

class Grid;
class Triangle;

#include <string>
#include <stdexcept>

class Shape {
private:
  static int nextID;

protected:
  int ID;
  Triangle* prevTriangle;

public:
  // TODO: ADD GET POINT BY X,Y FUNC FOR addPoint

  Shape(Triangle* prevT);
  Shape(const Shape& other);
  Shape& operator=(const Shape& other);

  static void resetNextID();
  int getID() const;
  virtual void draw(Grid& grid) const = 0;
  virtual std::string to_string() const = 0;
  virtual ~Shape() = default;

  static Shape* addShapes(Shape& s1, Shape& s2);

  virtual std::string debug_str() const {throw std::invalid_argument("oops i hortoned");}

};

