#pragma once

#include "Line.hpp"
#include "Point.hpp"

namespace GeometryHelper {
    /// @brief sets x and y to where the lines cross
    ///   Also gets t and u, which is measure of where the point lies on each line
    /// @return false if the lines are parallel
    bool intersectLines(const Line& line1, const Line& line2,
                                    double& x, double& y,
                                    double& t, double& u);

    
    /// @brief true if the two lines point in directions less than 5 degrees apart
    bool areParallel(const Line& a, const Line& b);
    const Point* sharedEndpoint(const Line* a, const Line* b);

    // Refelcts a point p, across a line. Stores the co-ords of new point in rx, ry
    void reflectPoint(const Line& line, const Point& p, double& rx, double& ry);
    // @brief Tells you if the point is at or beyond the end of a line
    // t just shows you how far along the line the point is. 
    //  t=0 or 1 means at the start or end respectively
    bool atOrBeyondFarEnd(const Line* arm, const Point* vertex, double t);
};
