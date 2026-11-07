#pragma once

class Canvas;
class Triangle;

class Shape {
protected:
  int ID;
  Triangle* prevTriangle;
public:

  Shape(int id, Triangle* prevT);
  virtual void draw(const Canvas&) = 0;
  virtual ~Shape() = default;

};

