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
  virtual ~Shape();
  int num_of_references;

public:
  Shape(Triangle* prevT);
  Shape(const Shape& other);
  Shape& operator=(const Shape& other);

  static void resetNextID();
  int getID() const;
  virtual void draw(Grid& grid) const = 0;
  virtual std::string to_string() const = 0;
  virtual void destroy(bool force=false);

  static Shape* addShapes(Shape& s1, Shape& s2);

  virtual std::string debug_str() const {throw std::invalid_argument("debug_str not defined for this");}

  void incrementReferences();
  void decrementReferences();
};

