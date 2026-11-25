#include "Shape.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Angle.hpp"
#include "Triangle.hpp"
#include "Hexagon.hpp"
#include "Pentagon.hpp"
#include "Rectangle.hpp"
#include "GeometryHelper.hpp"

#include <stdexcept>

int Shape::nextID = 1;
int Shape::x_bound = 0; // Need to set this
int Shape::y_bound = 0;

Shape::Shape(Triangle* prevT)
    : ID(nextID++), prevTriangle(prevT), num_of_references(0) {
  if (prevTriangle) prevTriangle->incrementReferences();
};


Shape::Shape(const Shape& other) {
    throw std::runtime_error("Not implemented yet.");
}

Shape::~Shape() {
  if (prevTriangle) prevTriangle->decrementReferences();
}

Shape& Shape::operator=(const Shape& other) {
    throw std::runtime_error("Not implemented yet.");
    return *this;
}
void Shape::destroy(bool force) {
    if (!force && num_of_references > 0) 
      throw std::invalid_argument("Cannot delete a shape that is referenced by another shape!");

    delete this;
  }
void Shape::incrementReferences() {num_of_references++;}
void Shape::decrementReferences() {
    if (num_of_references == 0) {
        throw std::runtime_error("Decremented reference on unreferenced point");
    }

    num_of_references--;
}
int Shape::getID() const {
    return ID;
}

void Shape::resetNextID() {
    nextID = 1;
}

int Shape::getNextID() {return nextID;}
void Shape::setNextID(int n) {nextID = n;}

Shape* Shape::addShapes(Shape& s1, Shape& s2) {
    // point + point  = line
    if ( auto p1 = dynamic_cast<Point*>(&s1) )
    {
        // * point + point = line
        if ( auto p2 = dynamic_cast<Point*>(&s2)) {
            return *p1 + *p2;
        }
    }
    
    // line + line = angle
    if (auto l1 = dynamic_cast<Line*>(&s1) ) {
        if (auto l2 = dynamic_cast<Line*> (&s2)) {
            return *l1 + *l2;
      } 
    }

    // angle + line = triangle
    if (auto a = dynamic_cast<Angle*>(&s1)) {
        if (auto l = dynamic_cast<Line*>(&s2)) {
            return *a + *l;
        }
    }

    // triangle (or polygon) + triangle = polygon with one more side
    if (auto t = dynamic_cast<Triangle*>(&s2)) {
        return s1 + *t;
    }

    throw std::invalid_argument("Not allowed!");
}


Shape* operator+(Shape& lhs, Triangle& rhs) {

    if (dynamic_cast<Hexagon*>(&lhs) != nullptr) throw std::invalid_argument("A hexagon is the biggest shape!");
    Triangle* last = lhs.getPrevTriangle();
    if (!last) throw std::invalid_argument("Cannot perform this operation!");
    if (!rhs.isMirrorOf(*last)) throw std::invalid_argument("This is not the mirror image of the previous triangle!");
  
    lhs.incrementReferences();
    Rectangle* rect_ptr = dynamic_cast<Rectangle*>(&lhs);
    if (rect_ptr) {
    Pentagon* new_this = new Pentagon(&rhs);
    return new_this;
  }

    Pentagon* pen_ptr = dynamic_cast<Pentagon*>(&lhs);
    if (pen_ptr) {
    Hexagon* new_this = new Hexagon(&rhs);
    return new_this;
  }

  Triangle* tri_ptr = dynamic_cast<Triangle*>(&lhs);
  if (!tri_ptr) throw std::runtime_error("something went wrong with adding triangle to a shape");

  Rectangle* new_this = new Rectangle(&rhs);
  return new_this;
}

// TODO: For doing Line + Line + Line
Shape* Shape::addShapes(Shape& s1, Shape& s2, Shape& s3) {
 return nullptr;
}

// TODO: 
Shape* Shape::subShapes(Shape& s1, Shape& s2) {
    // TODO: any shape - same shape = blank
    //  gonna put this in canvas instead.
    if (s1.sameAs(&s2)) return nullptr;

    // TODO : angle - line = line
    if (auto a = dynamic_cast<Angle*>(&s1)) {
        if (auto l = dynamic_cast<Line*>(&s2)) {
            // return *a - *l;
        }
    }

    if (auto t = dynamic_cast<Triangle*>(&s1)) {
        // TODO: triangle - line = angle
        if (auto l = dynamic_cast<Line*>(&s2)) {
            // return *t - *l;
        }
        // TODO: triangle - angle = line
        if (auto a = dynamic_cast<Angle*>(&s2)) {
            // return *t - *a;
        }
    }

    // TODO: polygon - triangle = polygon with one less side
    if (auto t = dynamic_cast<Triangle*>(&s2)) {
        // return s1 - *t;
    }

    throw std::invalid_argument("Not allowed!");
}

bool Shape::inBounds(int x, int y) {
  return !(x < 0 || x >= x_bound  || 
      y < 0 || y >= y_bound);
  
}
bool Shape::inBounds(const Point& p) {
  return inBounds(p.getX(), p.getY());
}
void Shape::setBounds(int widht, int height) {
  x_bound = widht;
  y_bound = height;
}
