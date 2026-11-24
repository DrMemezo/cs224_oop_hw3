#include "Hexagon.hpp"
#include "Triangle.hpp"
#include "Grid.hpp"

#include <sstream>

Hexagon::Hexagon(Triangle* lastTriangle)
    : Shape(lastTriangle)
{
}

void Hexagon::draw(Grid& grid) const {
    for (Triangle* t = prevTriangle; t; t = t->getPrevTriangle()) {
        t->draw(grid);
    }
}

std::string Hexagon::to_string() const {
    std::stringstream ss;
    ss << "ID: " << ID << " Hexagon\n"
       << "\tTriangles (ID, last to first):";
    for (Triangle* t = prevTriangle; t; t = t->getPrevTriangle()) {
        ss << " " << t->getID();
    }
    return ss.str();
}

bool Hexagon::sameAs(const Shape* other) const {
    if (this == other) return true;

    const Hexagon* p = dynamic_cast<const Hexagon*>(other);
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
