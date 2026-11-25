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
      vertices{nullptr, nullptr, nullptr}, mirroredFrom(nullptr)
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

Triangle* Triangle::mirrored(Line* line) {
  if (!line) throw std::invalid_argument("Line cannot be null!");


  Point* p = nullptr; 
  int p_idx;
  if (line == sides[0]) {
    p = vertices[0];
    p_idx = 0;
  }
  else if (line == sides[1]) {
    p = vertices[1];
    p_idx = 1;
  }
  else if (line == sides[2]) { 
    p = vertices[2];
    p_idx = 2;
  }
  else throw std::invalid_argument("Line not a part of this triangle!");

  double tempx, tempy;
  GeometryHelper::reflectPoint(*line, *p, tempx, tempy);
  
  int rx = std::lround(tempx);
  int ry = std::lround(tempy);

  Point* reflected_point = new Point(rx, ry);

  Line* new_line1 = new Line(vertices[(p_idx + 1) % 3], reflected_point);
  Line* new_line2 = new Line(vertices[(p_idx + 2) % 3], reflected_point);


  Triangle* yeaeh =new Triangle(line, new_line1, new_line2);
  yeaeh->mirroredFrom = this;
  return yeaeh;
}

bool Triangle::isMirrorOf(const Triangle& aaaa) const {
  return (mirroredFrom != nullptr && mirroredFrom == &aaaa);
}

bool Triangle::sameAs(const Shape* other) const {
    if (this == other) return true;

    const Triangle* t = dynamic_cast<const Triangle*>(other);
    if (!t) return false;

    // Same triangle if every corner is also a corner of the other one
    for (int i = 0; i < 3; i++) {
        bool found = false;
        for (int j = 0; j < 3; j++) {
            if (*vertices[i] == *t->vertices[j]) found = true;
        }
        if (!found) return false;
    }
    return true;
}

void Triangle::deleteReflectedTriangle(Triangle* to_delete, Line* line) {
  int mirror_line_idx = to_delete->sideIndex(line);
  if (mirror_line_idx == -1) throw std::runtime_error("Line not in to_delete!");

  Line* d_line_1 = to_delete->getSide(( mirror_line_idx + 1 ) % 3);
  Line* d_line_2 = to_delete->getSide(( mirror_line_idx + 2 ) % 3);

  Point* d_point = to_delete->getCorner(mirror_line_idx);

  d_line_1->decrementReferences();
  d_line_1->destroy();
  d_line_2->decrementReferences();
  d_line_2->destroy();

  d_point->decrementReferences();
  d_point->destroy();

  delete to_delete;
  
}  
