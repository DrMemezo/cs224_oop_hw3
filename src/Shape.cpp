#include "Shape.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Angle.hpp"
#include "Triangle.hpp"

#include <stdexcept>

int Shape::nextID = 1;

Shape::Shape(Triangle* prevT)
    : ID(nextID++), prevTriangle(prevT), num_of_references(0) {
  if (prevTriangle) prevTriangle->incrementReferences();
};


Shape::Shape(const Shape& other) {
    std::runtime_error("Not implemented yet.");
}

Shape::~Shape() {
  if (prevTriangle) prevTriangle->decrementReferences();
}

Shape& Shape::operator=(const Shape& other) {
    std::runtime_error("Not implemented yet.");
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

    throw std::invalid_argument("Not allowed!");
}
