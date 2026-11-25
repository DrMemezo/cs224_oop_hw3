#pragma once

class Grid;
class Triangle;
class Point;


#include <string>
#include <stdexcept>

class Shape {
private:
  static int nextID;
  static int x_bound; // x may not be equal to or more than this value
  static int y_bound; // same for y

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
  static int getNextID(); 
  static void setNextID(int n);
  int getID() const;


  virtual void draw(Grid& grid) const = 0;
  virtual std::string to_string() const = 0;
  virtual void destroy(bool force=false);

  static Shape* addShapes(Shape& s1, Shape& s2);
  static Shape* addShapes(Shape& s1, Shape& s2, Shape& s3);
  static Shape* subShapes(Shape& s1, Shape& s2);

  virtual std::string debug_str() const {throw std::invalid_argument("debug_str not defined for this");}
  virtual bool sameAs(const Shape* other) const {throw std::runtime_error("Not implemented yet");}

  Triangle* getPrevTriangle() const {return prevTriangle;}

  void incrementReferences();
  void decrementReferences();
  int getReferences() const {return num_of_references;}


  /// @brief Checks if the point is within bounds of the preset Canvas values.
  static bool inBounds(int x, int y);
  static bool inBounds(const Point& p);
  static void setBounds(int widht, int height);
  friend Shape* operator+(Shape& lhs, Triangle& rhs);
};

