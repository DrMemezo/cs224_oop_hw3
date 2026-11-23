#include "GeometryHelper.hpp"
#include <cmath>
#include <stdexcept>


bool GeometryHelper::areParallel(const Line& a, const Line& b) {
  double angleA = a.getAngle();
  double angleB = b.getAngle();

  double diff = std::fmod(std::fabs(angleA - angleB), 180.0);
  if (diff > 90) diff = 180 - diff;

  return diff < 5;
}

bool GeometryHelper::intersectLines(const Line& line1, const Line& line2,
                                    double& x, double& y,
                                    double& t, double& u)
{

    if ( GeometryHelper::areParallel(line1, line2) ) 
      return false;

    const Point* start1 = line1.getStart();
    const Point* end1 = line1.getEnd();

    const Point* start2 = line2.getStart();
    const Point* end2 = line2.getEnd();

    if (start1 == start2 || start1 == end2) {
        x = start1->getX();
        y = start1 -> getY();
        return true;
    }
    else if (end1 == start2 || end1 == end2) {
        x = end1->getX();
        y = end1 -> getY();
        return true;
    }

    double ax1 = start1->getX();
    double ay1 = start1->getY();

    // Direction vector of line 1
    double dax = end1->getX() - ax1;
    double day = end1->getY() - ay1;

    double bx1 = line2.getStart()->getX();
    double by1 = line2.getStart()->getY();

    // Direciton vector of line 2
    double dbx = line2.getEnd()->getX() - bx1;
    double dby = line2.getEnd()->getY() - by1;

    // This is the cross product
    double denom = dax * dby - day * dbx;

    // Uhh so i know if its parallel or not but this shouldnt happen
    // so i know where the code might be going wrong
    if (std::fabs(denom) < 1e-9) 
      throw std::runtime_error("Lines were parallel!"); 
  
    double wx = bx1 - ax1;
    double wy = by1 - ay1;

    // How far along Line 1 do you have to travel to get the intersection point.
    t = (wx * dby - wy * dbx) / denom;   // position along l1
    // Same for line 2
    u = (wx * day - wy * dax) / denom;   // position along l2

    x = ax1 + t * dax;
    y = ay1 + t * day;
    return true;
}

const Point* GeometryHelper::sharedEndpoint(const Line* a, const Line* b) {
    const Point* a_ends[2] = { a -> getStart(), a -> getEnd() };
    const Point* b_ends[2] = { b -> getStart(), b -> getEnd() };

    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        if (*a_ends[i] == *b_ends[j]) return a_ends[i];
      }
    }
    return nullptr;
}

void GeometryHelper::reflectPoint(const Line& line, const Point& p, double& rx, double& ry) {
    int ax = line.getStart()->getX();
    int ay = line.getStart()->getY();
    
    int bx = line.getEnd()->getX();
    int by = line.getEnd()->getY();

    double dx = bx - ax;
    double dy = by - ay;
    double d = std::sqrt(dx * dx + dy * dy);

    double ux = dx / d;
    double uy = dy / d;

    // * R = [[2ux^2 - 1, 2ux*uy], [2ux*uy, 2uy^2 - 1]]
    double qx = p.getX() - ax;
    double qy = p.getY() - ay;
    rx = ax + (2 * ux * ux - 1) * qx + (2 * ux * uy) * qy;
    ry = ay + (2 * ux * uy) * qx + (2 * uy * uy - 1) * qy;
}
