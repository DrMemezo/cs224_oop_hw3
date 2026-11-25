#pragma once

#include "Shape.hpp"
#include <string>

class Line;
class Point;

/// @brief Two lines that meet at a vertex. The arms are lines that are owned by the canvas list
class Angle : public Shape {
private:
    Line* arm1;
    Line* arm2;
    Point* vertex;
    bool extensionRequiredFlag; // A signal to add vertex to the history
    
    ~Angle() override;

    /// @brief From the choice of the three points, gets the point which maches the coordinates 
    /// @returns one of the three points, or a new point.
    static Point* pointAt(int x, int y, Point* p1, Point* p2, Point* p3);
  
public:
    /// @throws invalid_argument if the lines are parallel
    Angle(Line* a, Line* b);

    void draw(Grid& grid) const override;
    std::string to_string() const override;
    // std::string debug_str() const override;

    Line* getArm1() const;
    Line* getArm2() const;
    Point* getVertex() const {return vertex;}

    bool usesArm(const Shape* s) const;
    bool sameAs(const Shape* other) const override;

    bool getExtensionFlag() const {return extensionRequiredFlag;}
    void resetExtensionFlag() {extensionRequiredFlag = false;}

    friend Triangle* operator+(Angle& lhs, Line& rhs);
    friend Line* operator-(Angle& lhs, Line& rhs);
};
