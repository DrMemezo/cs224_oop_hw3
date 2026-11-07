#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;

#include "Canvas.hpp"

Canvas::Canvas(int width) 
    : _width(width),_height(width*2),grid(width, width * 2)
{};


void Canvas::display() const {
    grid.display();
}