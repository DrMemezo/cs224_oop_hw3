#include "Shape.hpp"
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

void Shape::resetNextID() {
    nextID = 1;
}