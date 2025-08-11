// Line2D.cpp

// Header Files
#include "Line2D.h"

// Constructor implementations
Line2D::Line2D(int x1, int y1, int x2, int y2)
    : pt1(x1, y1), pt2(x2, y2) {
    setLength(); // Calculate length upon construction
}

Line2D::Line2D(Point2D p1, Point2D p2)
    : pt1(p1), pt2(p2) {
    setLength(); // Calculate length upon construction
}

// Method implementations
void Line2D::setLength() {
    int x_sq = pt2.getX() - pt1.getX();
    int y_sq = pt2.getY() - pt1.getY();
    length = sqrt(x_sq * x_sq + y_sq * y_sq);
}

Point2D Line2D::getPt1() const {
    return pt1;
}

Point2D Line2D::getPt2() const {
    return pt2;
}

double Line2D::getScalarValue() const {
    return length;
}

void Line2D::setPt1(int x, int y) {
    pt1.setX(x);
    pt1.setY(y);
    setLength(); // Recalculate length after setting a new point
}

void Line2D::setPt2(int x, int y) {
    pt2.setX(x);
    pt2.setY(y);
    setLength(); // Recalculate length after setting a new point
}

//---------------Display Method------------------------

// Friend function to overload the << operator for output
    ostream& operator<<(ostream& os, const Line2D& line2d) {
        Point2D pt1 = line2d.getPt1();
        Point2D pt2 = line2d.getPt2();
        os << "[" << setw(4) << right << fixed << setprecision(3) << pt1.getX() 
             << "," << setw(5) << right << fixed << setprecision(3) << pt1.getY() << "]"
                    << setw(4) << right << "[" 
                    << setw(4) << right << fixed << setprecision(3) << pt2.getX() 
             << "," << setw(5) << right << fixed << setprecision(3) << pt2.getY() << "]"
                    << "   "   << line2d.getScalarValue();
        return os;
    }
