#pragma once

// There will only be 1 Canvas at a time
#include "Grid.hpp"
#include "ShapeLinkedList.hpp"


class Canvas {
    private:

        int _width;
        int _height;

        Grid grid;
        ShapeLinkedList shape_list;

        void destroy();
        void copy(const Canvas&);

    public:
        Canvas(int width);
        void display() const;
};
