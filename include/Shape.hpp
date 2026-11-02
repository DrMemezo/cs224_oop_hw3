#pragma once

class Triangle;

class Shape {
protected:
  int ID;
  Triangle* prevTriangle;
public:
  virtual void draw() = 0;
  virtual ~Shape() = default;

};

