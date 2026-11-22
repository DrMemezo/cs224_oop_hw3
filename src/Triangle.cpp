#include "Triangle.hpp"
#include "Line.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Grid.hpp"
#include "GeometryHelper.hpp"

#include <sstream>
#include <stdexcept>

void Triangle::getVerticesFromSides() {
  const Point* start1 = sides[0] -> getStart();
  const Point* end1 = sides[0] -> getEnd();

  const Point* start2 = sides[1] -> getStart();
  const Point* end2 = sides[1] -> getEnd();

  const Point* start3 = sides[2] -> getStart();
  const Point* end3 = sides[2] -> getEnd();



  // Check each point indicidaually to get the vertices. Raise a invalid_argumenet 
  const Point* v12 = GeometryHelper::sharedEndpoint(sides[0], sides[1]);
  const Point* v23 = GeometryHelper::sharedEndpoint(sides[1], sides[2]);
  const Point* v13 = GeometryHelper::sharedEndpoint(sides[0], sides[2]);

  if (!v12 || !v23 || !v13 || 
      v12 == v23 || 
      v23 == v13 || 
      v12 == v13) {
    throw std::invalid_argument("The sides do not form a perfectly closed triangle!");
  }

  // vertices[i] is the corner that is opposite side i
  vertices[0] = const_cast<Point*>(v23);
  vertices[1] = const_cast<Point*>(v13);
  vertices[2] = const_cast<Point*>(v12); // error if it is not perfectly closed
  
}

Triangle::Triangle(Line* l1, Line* l2, Line* l3)
    : Shape(nullptr), sides{l1, l2, l3}, 
      vertices{nullptr, nullptr, nullptr}
{
    if (!l1 || !l2 || !l3) 
      throw std::invalid_argument("A triangle needs three lines!");

    getVerticesFromSides();

    for (int i=0; i< 3; i++) sides[i]->incrementReferences();
    for (int i=0; i< 3; i++) vertices[i]->incrementReferences();
}


Triangle::~Triangle() {
    for (int i=0; i< 3; i++) sides[i]->decrementReferences();
    for (int i=0; i< 3; i++) vertices[i]->decrementReferences();
}

void Triangle::draw(Grid& grid) const {
    for (int i=0; i< 3; i++) sides[i]->draw(grid);
    for (int i=0; i< 3; i++) vertices[i]->draw(grid);
}


std::string Triangle::to_string() const {
    std::stringstream ss;
    ss << "ID: " << ID << " Triangle\n"
       << "\tSide 1 (ID): " << sides[0]->getID() << "\n"
       << "\tSide 2 (ID): " << sides[1]->getID() << "\n"
       << "\tSide 3 (ID): " << sides[2]->getID();
    return ss.str();
}

int Triangle::sideIndex(const Shape* s) const {
    for (int i = 0; i < 3; i++) {
        if (sides[i] == s) return i;
    }
    return -1;
}

Line* Triangle::getSide(int i) const {
    return sides[i];
}

Point* Triangle::getCorner(int i) const {
    return vertices[i];
}

bool Triangle::sharesSideWith(const Triangle* other) const {
    for (int i = 0; i < 3; i++) {
        if (other->sideIndex(sides[i]) >= 0) return true;
    }
    return false;
}

Triangle* mirrored(Line* line) {

}
