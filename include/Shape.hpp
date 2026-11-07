#pragma once

class Grid;
class Triangle;

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
  virtual void draw(Grid& grid) = 0;
  virtual ~Shape() = default;

};

