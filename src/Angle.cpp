#include "Angle.hpp"
#include "Line.hpp"
#include "Point.hpp"
#include "Grid.hpp"
#include "GeometryHelper.hpp"
#include "constants.hpp"

#include <sstream>
#include <stdexcept>

Angle::Angle(Line* a, Line* b)
    : Shape(nullptr), arm1(a), arm2(b), vertex(nullptr), extensionRequiredFlag(false)
{
    if (!a || !b) throw std::invalid_argument("An angle needs two lines!");

    double x, y, t, u;
    if (!GeometryHelper::intersectLines(*a, *b, x, y, t, u))
        throw std::invalid_argument("Lines are parallel!");

    if ((t > EPS && t < 1 - EPS) || (u > EPS && u < 1 - EPS))
        throw std::invalid_argument("Ambiguous angle!");

    bool ext1 = (t > 1 + EPS) || (t < -EPS);
    bool ext2 = (u > 1 + EPS) || (u < -EPS);
    extensionRequiredFlag = ext1 || ext2;

    // Checked now so that the canvas doesnt have to do it.
    if (extensionRequiredFlag && !Shape::inBounds(std::lround(x), std::lround(y)))
        throw std::invalid_argument("Action resulted in out of bounds point!");

    if (!extensionRequiredFlag) {
        // Lines already meet at their ends so we can reuse the existing endpoint
        vertex = (t < 0.5) ? const_cast<Point*>(a->getStart())
                           : const_cast<Point*>(a->getEnd());
    } else {
        vertex = new Point(std::lround(x), std::lround(y));
        if (t > 1 + EPS)  a->setEnd(vertex);   
        else if (t < -EPS) a->setStart(vertex);

        if (u > 1 + EPS)  b->setEnd(vertex);   
        else if (u < -EPS) b->setStart(vertex);
    }

    a->incrementReferences();
    b->incrementReferences();
    vertex->incrementReferences();
}

  
Angle::~Angle() {
  arm1->decrementReferences();
  arm2->decrementReferences();
  vertex->decrementReferences();
}

void Angle::draw(Grid& grid) const {
    // * Each arm is drawn from the vertex out to both of its ends (this covers any extension)
    // int vert_x = vertex->getX();
    // int vert_y = vertex->getY();
    
    arm1 -> draw(grid);
    arm2 -> draw(grid);
    vertex->draw(grid);

    // Line::drawSegment(grid, vert_x, vert_y,
    //                   arm1->getStart()->getX(), arm1->getStart()->getY(),
    //                   arm1->getLineChar());
    //
    // Line::drawSegment(grid, vert_x, vert_y,
    //                   arm1->getEnd()->getX(), arm1->getEnd()->getY(),
    //                   arm1->getLineChar());
    //
    // Line::drawSegment(grid, vert_x, vert_y,
    //                   arm2->getStart()->getX(), arm2->getStart()->getY(),
    //                   arm2->getLineChar());
    //
    // Line::drawSegment(grid, vert_x, vert_y,
    //                   arm2->getEnd()->getX(), arm2->getEnd()->getY(),
    //                   arm2->getLineChar());
}

std::string Angle::to_string() const {
    std::stringstream ss;
    ss << "ID: " << ID << " Angle\n"
       << "\tArm 1 (ID): " << arm1->getID() << "\n"
       << "\tArm 2 (ID): " << arm2->getID() << "\n"
       << "\tVertex (ID): " << vertex -> getID();
    return ss.str();
}


bool Angle::usesArm(const Shape* s) const {
    return s == arm1 || s == arm2;
}

bool Angle::sameAs(const Shape* other) const {
    if (this == other) return true;

    const Angle* a = dynamic_cast<const Angle*>(other);
    if (!a) return false;

    return (arm1 == a->arm1 && arm2 == a->arm2) || (arm1 == a->arm2 && arm2 == a->arm1);
}

Line* Angle::getArm1() const { return arm1; }
Line* Angle::getArm2() const { return arm2; }


Triangle* operator+(Angle& lhs, Line& rhs) {
  
    Line* arm1 = lhs.getArm1();
    Line* arm2 = lhs.getArm2();
    Point* v = lhs.getVertex();

    if (&rhs == arm1 || &rhs == arm2)
        throw std::invalid_argument("The line is already an arm of the angle!");

    double x1, y1, t1, u1;
    // u1 and u2 is where the point lies on the rhs line 
    // respective to arm1 and arm2
    double x2, y2, t2, u2;
    if (!GeometryHelper::intersectLines(*arm1, rhs, x1, y1, t1, u1) ||
        !GeometryHelper::intersectLines(*arm2, rhs, x2, y2, t2, u2))
        throw std::invalid_argument("The line is parallel to an arm of the angle!");

    // Im opting to not allow extensions where there will be multiple angles created. 
    double u_low = std::min(u1, u2);
    double u_high = std::max(u1, u2);
    if (!GeometryHelper::atOrBeyondFarEnd(arm1, v, t1) // intersecting WITHIn arm1
      || !GeometryHelper::atOrBeyondFarEnd(arm2, v, t2) // intersecting WITHIn arm2
      || u_low > EPS || u_high < 1 - EPS) // Intersecting within the rhs line.
        throw std::invalid_argument("These lines cannot make a triangle by only extending them!");

    int rx1 = std::lround(x1);
    int ry1 = std::lround(y1);
    int rx2 = std::lround(x2);
    int ry2 = std::lround(y2);

    // Check if its not intersecting at the exact same point
    if (rx1 == rx2 && ry1 == ry2)
        throw std::invalid_argument("The triangle would be too small!");
    if (!Shape::inBounds(rx1, ry1) || !Shape::inBounds(rx2, ry2))
        throw std::invalid_argument("Action resulted in out of bounds point!");

    // TODO: ADD DOING LOGIC
}
Line* operator-(Angle& lhs, Line& rhs) {

}
