#pragma once

#include "Shape.hpp"

class Line;
class Point;

class Triangle : public Shape {
private:
    /// sides[i] is the side that is opposite to corner i
    Line* sides[3];
    Point* vertices[3];

    void getVerticesFromSides();

public:
    /// @param prev the triangle this one was mirrored from (it is copied), or nullptr
    Triangle(Line* l1, Line* l2, Line* l3);
    Triangle(const Triangle& other) = delete;
    Triangle& operator=(const Triangle& other) = delete;
    ~Triangle();

    void draw(Grid& grid) const override;
    std::string to_string() const override;

    /// @return 0, 1 or 2 for the side, or -1 if s is not one of the sides
    int sideIndex(const Shape* s) const;
    Line* getSide(int i) const;
    Point* getCorner(int i) const;
    /// @brief true if the two triangles have at least one side in common
    bool sharesSideWith(const Triangle* other) const;

    /// @brief Returns a new triangle mirrored along the line.
    Triangle* mirrored(Line* line);

    bool sameAs(const Shape* other) const override;
    /// @brief deletes the triangle and the new points and lines and such EXCEPT 
    /// The line it was reflecting.
    static void deleteReflectedTriangle(Triangle* to_delete, Line* line);
};
