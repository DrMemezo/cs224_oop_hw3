#include "Rectangle.hpp"
#include "Triangle.hpp"
#include <sstream>

Rectangle::Rectangle(Triangle* lastTriangle)
    : Shape(lastTriangle)
{
}


void Rectangle::draw(Grid& grid) const {
    for (Triangle* t = prevTriangle; t; t = t->getPrevTriangle()) {
        t->draw(grid);
    }
}

std::string Rectangle::to_string() const {
    std::stringstream ss;
    ss << "ID: " << ID << " Rectangle\n"
       << "\tTriangles (ID, last to first):";
    for (Triangle* t = prevTriangle; t; t = t->getPrevTriangle()) {
        ss << " " << t->getID();
    }
    return ss.str();
}

bool Rectangle::sameAs(const Shape* other) const {
    if (this == other) return true;

    const Rectangle* p = dynamic_cast<const Rectangle*>(other);
    if (!p) return false;

    // Same if the triangles are the same, one by one
    Triangle* a = prevTriangle;
    Triangle* b = p->prevTriangle;
    while (a && b) {
        if (!a->sameAs(b)) return false;
        a = a->getPrevTriangle();
        b = b->getPrevTriangle();
    }
    return a == nullptr && b == nullptr;
}
