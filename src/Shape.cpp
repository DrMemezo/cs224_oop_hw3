#include "Shape.hpp"
#include "Point.hpp"
#include "Line.hpp"

#include <stdexcept>

int Shape::nextID = 1;

Shape::Shape(Triangle* prevT)
    : ID(nextID++), prevTriangle(prevT) {};


Shape::Shape(const Shape& other) {
    std::runtime_error("Not implemented yet.");
}

Shape& Shape::operator=(const Shape& other) {
    std::runtime_error("Not implemented yet.");
    return *this;
}

int Shape::getID() const {
    return ID;
}

void Shape::resetNextID() {
    nextID = 1;
}

Shape* Shape::addShapes(Shape& s1, Shape& s2) {
    if ( auto p1 = dynamic_cast<Point*>(&s1) )
    {
        // * point + point = line
        if ( auto p2 = dynamic_cast<Point*>(&s2)) {
            return *p1 + *p2;
        }
    }

    throw std::invalid_argument("Not allowed!");
}