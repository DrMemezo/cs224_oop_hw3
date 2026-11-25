#pragma once

// There will only be 1 Canvas at a time
#include "Grid.hpp"
#include "ShapeLinkedList.hpp"
#include <stdexcept>

class Point;

class Canvas {
    private:

        int _width;
        int _height;

        Grid grid;
        ShapeLinkedList shape_list;

        void destroy();
        void copy(const Canvas&);
    
        bool checkBounds(const Point& p);

    public:
        Canvas(int width);

        /// @brief Clears the screen
        void clear();
        /// @brief Adds the point object to the linkedlist
        bool addPoint(Point& point);
        /// @brief Adds the point object simply thru x and y coords
        bool addPoint(int px, int py);
        /// @brief Adds a shape to th elinked list
        bool addShape(Shape& shape);

        /// @brief Show the grid onto the screen
        void render();
        /// @brief shows the shapes in the linked list
        void show_history() const;


        /// @brief Trys to combine the shapes with the respecitive ids. Shows an error if not
        int combine(int id1, int id2);

        void debug(int id_);

        /// @brief Subtracts shape id2 from shape id1. Returns the new id, or -1 if both shapes were removed
        int sub(int id1, int id2) {throw std::runtime_error("not implementd yet");}

        /// @brief Mirrors the last triangle that uses the line across that line. Returns the new triangle id
        int mirror(int line_id);
        /// @brief Deletes the shape with the given id
        void del(int id);
        
};
