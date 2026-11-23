#pragma once

#include "Shape.hpp"
#include <string>

/// @brief Three triangles joined in a row (5 sides).
class Pentagon : public Shape {
public:
    /// @param lastTriangle The last triangle of the shape. 
    Pentagon(Triangle* lastTriangle);

    // TODO: Rule of three. 
    Pentagon(const Pentagon& other);
    Pentagon& operator=(const Pentagon& other);
    ~Pentagon();

    void draw(Grid& grid) const override;
    std::string to_string() const override;
    bool sameAs(const Shape* other) const override;
};
