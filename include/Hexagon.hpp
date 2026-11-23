#pragma once

#include "Shape.hpp"
#include <string>

/// @brief Four triangles joined in a row (6 sides). 
class Hexagon : public Shape {
public:
    /// @param lastTriangle The last triangle of the shape. 
    Hexagon(Triangle* lastTriangle);

    // TODO: Rule of three. 
    Hexagon(const Hexagon& other);
    Hexagon& operator=(const Hexagon& other);
    ~Hexagon();

    void draw(Grid& grid) const override;
    std::string to_string() const override;
    bool sameAs(const Shape* other) const override;
};
