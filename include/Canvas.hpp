#pragma once

// There will only be 1 Canvas at a time
#include "Grid.hpp"


class Canvas {
    private:
        struct Node {
            Node* prevNode;
            Node* nextNode;

        }

        int _width;
        int _height;

        Grid grid;
        int nextID = 1;

        void destroy();
        void copy(const Canvas&);

        // TODO: Have a LinkedList history
    public:
        Canvas(int width);
        void display() const;
};
