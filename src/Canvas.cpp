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

void Canvas::render() const {
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
    shape_list.drawAll(grid);
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

    // * Don't allow more than one point on the same co-ordinates
    if (grid.getCell(px, py) == shape_symbols::POINT) {return false;}

    shape_list.addShape(&point);
    shape_list.drawAll(grid);
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

