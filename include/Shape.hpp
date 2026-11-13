#pragma once

class Grid;
class Triangle;

#include <string>

class Shape {
private:
  static int nextID;

protected:
  int ID;
  Triangle* prevTriangle;
public:

  Shape(Triangle* prevT);
  Shape(const Shape& other);
  Shape& operator=(const Shape& other);

  static void resetNextID();
  int getID() const;
  virtual void draw(Grid& grid) const = 0;
  virtual std::string to_string() const = 0;
  virtual ~Shape() = default;

};

