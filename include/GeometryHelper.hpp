#pragma once

#include "Line.hpp"
#include "Point.hpp"

namespace GeometryHelper {
    /// @brief sets x and y to where the lines cross
    /// @return false if the lines are parallel
    bool intersectLines(const Line& line1, const Line& line2,
                                    double& x, double& y,
                                    double& t, double& u);

    
    /// @brief true if the two lines point in directions less than 5 degrees apart
    bool areParallel(const Line& a, const Line& b);
    const Point* sharedEndpoint(const Line* a, const Line* b);

    // Refelcts a point p, across a line. Stores the co-ords of new point in rx, ry
    void reflectPoint(const Line& line, const Point& p, double& rx, double& ry);
};
