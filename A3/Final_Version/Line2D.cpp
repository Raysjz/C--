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

bool Line2D::compareP1asc(Line2D l1, Line2D l2)
    {
        const Point2D& p1 = l1.getPt1();
        const Point2D& p2 = l2.getPt1();
        
        // Compare X coordinates
        if (p1.getX() < p2.getX()) return true;
        if (p1.getX() > p2.getX()) return false;
        
        // If X coordinates are equal, compare Y coordinates
        if (p1.getY() < p2.getY()) return true;
        if (p1.getY() > p2.getY()) return false;
        
        // If both X and Y coordinates are equal, consider them equal
        return false;
    }
bool Line2D::compareP1dsc(Line2D l1, Line2D l2)
    {
        const Point2D& p1 = l1.getPt1();
        const Point2D& p2 = l2.getPt1();
        
        // Compare X coordinates
        if (p1.getX() > p2.getX()) return true;
        if (p1.getX() < p2.getX()) return false;
        
        // If X coordinates are equal, compare Y coordinates
        if (p1.getY() > p2.getY()) return true;
        if (p1.getY() < p2.getY()) return false;
        
        // If both X and Y coordinates are equal, consider them equal
        return false;
    }
bool Line2D::compareP2asc(Line2D l1, Line2D l2)
    {
        const Point2D& p1 = l1.getPt2();
        const Point2D& p2 = l2.getPt2();
        
        // Compare X coordinates
        if (p1.getX() < p2.getX()) return true;
        if (p1.getX() > p2.getX()) return false;
        
        // If X coordinates are equal, compare Y coordinates
        if (p1.getY() < p2.getY()) return true;
        if (p1.getY() > p2.getY()) return false;
        
        // If both X and Y coordinates are equal, consider them equal
        return false;
    }
bool Line2D::compareP2dsc(Line2D l1, Line2D l2)
    {
        const Point2D& p1 = l1.getPt2();
        const Point2D& p2 = l2.getPt2();
        
        // Compare X coordinates
        if (p1.getX() > p2.getX()) return true;
        if (p1.getX() < p2.getX()) return false;
        
        // If X coordinates are equal, compare Y coordinates
        if (p1.getY() > p2.getY()) return true;
        if (p1.getY() < p2.getY()) return false;
        
        // If both X and Y coordinates are equal, consider them equal
        return false;
    }

// Static method to compare two Point2D objects based on distance from origin in ascending order
bool Line2D::compareLengthAsc(const Line2D& l1, const Line2D& l2) {
    return l1.getScalarValue() < l2.getScalarValue();
}

// Static method to compare two Point2D objects based on distance from origin in descending order
bool Line2D::compareLengthDsc(const Line2D& l1, const Line2D& l2) {
    return l1.getScalarValue() > l2.getScalarValue();
}

//---------------Display and Output Stream Method------------------------

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

//----------------Overload operator Method--------------------------------------------

bool Line2D::operator==(const Line2D &obj) const
{
    return (pt1 == obj.getPt1() && pt2 == obj.getPt2());
}
bool Line2D::operator<(const Line2D &obj) const
{
    return (length < obj.getScalarValue());
}
bool Line2D::operator>(const Line2D &obj) const
{
    return (length > obj.getScalarValue());
}
