#pragma once

#include "Shape.hpp"
#include <string>

/// @brief Two triangles joined along a line (4 sides).
/// It only keeps its last triangle (prevTriangle), and that triangle keeps the one before it, and so on.
class Rectangle : public Shape {
public:
    /// @param lastTriangle The last triangle of the shape. The shape owns it (and the chain behind it) from now on
    Rectangle(Triangle* lastTriangle);

    // TODO: Rule of three. 
    Rectangle(const Rectangle& other);
    Rectangle& operator=(const Rectangle& other);
    ~Rectangle();

    void draw(Grid& grid) const override;
    std::string to_string() const override;
    bool sameAs(const Shape* other) const override;
};
