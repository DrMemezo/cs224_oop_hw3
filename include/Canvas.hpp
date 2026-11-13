#pragma once

// There will only be 1 Canvas at a time
#include "Grid.hpp"
#include "ShapeLinkedList.hpp"

class Point;

class Canvas {
    private:

        int _width;
        int _height;

        Grid grid;
        ShapeLinkedList shape_list;

        void destroy();
        void copy(const Canvas&);


    public:
        void clear();
        bool addPoint(Point& point);
        bool addPoint(int px, int py);
        bool addShape(Shape& shape);
        Canvas(int width);
        void render() const;
        void show_history() const;
};
