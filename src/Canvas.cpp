#include <iostream>

#include <memory>
#include <stdexcept>

using std::cout;
using std::endl;

#include "Canvas.hpp"
#include "Point.hpp"
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


int Canvas::combine(int id1, int id2) {
    Shape* shape1 = shape_list.getShapeByID(id1);
    if (!shape1) throw std::invalid_argument("ID1 not in history");

    Shape* shape2 = shape_list.getShapeByID(id2);
    if (!shape2) throw std::invalid_argument("ID2 not in history");

    Shape* new_shape = Shape::addShapes(*shape1, *shape2);

    shape_list.addShape(new_shape);
    return new_shape->getID();

}

void Canvas::debug(int id_) {
    Shape* shape = shape_list.getShapeByID(id_);
    if (!shape) throw std::invalid_argument("Shape not in history");

    cout << shape -> debug_str() << endl;
}