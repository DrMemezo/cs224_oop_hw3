#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;

#include "Canvas.hpp"
#include "Point.hpp"
#include "Angle.hpp"
#include "Line.hpp"
#include "Triangle.hpp"
#include "constants.hpp"

Canvas::Canvas(int width) 
    : _width(width),_height(width*2),grid(width, width * 2)
{};

void Canvas::render(){
    shape_list.drawAll(grid);
    grid.display();
}

bool Canvas::addPoint(int px, int py) {
    // * Check if point is out of bounds
    if (px < 0 || px >= _width) {return false;}
    if (py < 0 || py >= _height) {return false;}

    // * Don't allow more than one point on the same co-ordinates
    if (const Point* p = shape_list.getPointByCoords(px, py)) return false;

    Point* point = new Point(px, py);

    shape_list.addShape(point);
    return true;

}

bool Canvas::addPoint(Point& point) {

    // * Make sure we're not adding the same shape again.
    if (shape_list.getShapeByID(point.getID()) != nullptr) return false;

    int px = point.getX();
    int py = point.getY();

    // * Check if point is out of bounds
    if (px < 0 || px >= _width) {return false;}
    if (py < 0 || py >= _height) {return false;}

    // TODO: MAKE THIS NOT ON THE GRID
    // * Don't allow more than one point on the same co-ordinates
    // if (grid.getCell(px, py) == shape_symbols::POINT) {return false;}

    shape_list.addShape(&point);
    return true;
}

bool Canvas::addShape(Shape& shape) {
    // * Make sure we're not adding the same shape again.
    if (shape_list.getShapeByID(shape.getID()) != nullptr) return false;

    shape_list.addShape(&shape);
    return false;
    
}

void Canvas::show_history() const {
    shape_list.print_history();
}


void Canvas::clear()  {
    shape_list.clearList();
    grid.clear();
    Shape::resetNextID();
}

bool Canvas::checkBounds(const Point& p) {
  return !(p.getX() < 0 || p.getX() >= _width || 
      p.getY() < 0 || p.getY() >= _height);
}

int Canvas::combine(int id1, int id2) {
    Shape* shape1 = shape_list.getShapeByID(id1);
    if (!shape1) throw std::invalid_argument("ID1 not in history");

    Shape* shape2 = shape_list.getShapeByID(id2);
    if (!shape2) throw std::invalid_argument("ID2 not in history");

    Shape* new_shape = Shape::addShapes(*shape1, *shape2);

    
    if (auto a = dynamic_cast<Angle*>(new_shape)) {
      if (a->getExtensionFlag()) {
         auto v = a->getVertex();
        a->resetExtensionFlag();

        if (!checkBounds(*v)) {
          v->destroy(true);
          a->destroy(true);
          throw std::invalid_argument("Action resulted in out of bounds point!");
        }
        shape_list.addShape(v);
      }
    }

    shape_list.addShape(new_shape);
    return new_shape->getID();

}

void Canvas::debug(int id_) {
    Shape* shape = shape_list.getShapeByID(id_);
    if (!shape) throw std::invalid_argument("Shape not in history");

    cout << shape -> debug_str() << endl;
}

int Canvas::mirror(int line_id) {
    Shape* line_shape = shape_list.getShapeByID(line_id);
    if (!line_shape) throw std::invalid_argument("Line not in history");

    Line* line = dynamic_cast<Line*>(line_shape);
    if (!line) throw std::invalid_argument("Mirror needs a line!");

    Triangle* tri = shape_list.getLastTriangleWithSide(line);
    if (!tri) throw std::invalid_argument("No triangle has that line as a side!");

    Triangle* mirrored_triangle = tri->mirrored(line);

    // Verifying a triangle is withing bounds. 
    // Otherwise delete everything.
    for (int i=0; i < 3; i++) {
      Point* this_p = mirrored_triangle->getCorner(i);
      if (!checkBounds(*this_p)) {
        Triangle::deleteReflectedTriangle(mirrored_triangle, line);
        throw std::invalid_argument("Mirrored Line was out of bounds!");
      }
    }
  
    int mirror_line_idx = mirrored_triangle->sideIndex(line);
    Line* added_line_1 = mirrored_triangle->getSide(( mirror_line_idx + 1 ) % 3);
    Line* added_line_2 = mirrored_triangle->getSide(( mirror_line_idx + 2 ) % 3);
    Point* added_point = mirrored_triangle->getCorner(mirror_line_idx);
  
    shape_list.addShape(added_point);
    shape_list.addShape(added_line_1);
    shape_list.addShape(added_line_2);

    return mirrored_triangle->getID();

}
