// Line3D.cpp

// Header Files
#include "Point2D.h"
#include "Line2D.h"
#include "Point3D.h"
#include "Line3D.h"

// Default Constructor
Line3D::Line3D(int x1, int y1, int z1, int x2, int y2, int z2)
    : Line2D(x1, y1, x2, y2), pt1(x1, y1, z1), pt2(x2, y2, z2) {
    setLength(); // Calculate length upon construction
}

// Constructor with Point3D parameters
Line3D::Line3D(Point3D p1, Point3D p2)
    : Line2D(p1.getX(), p1.getY(), p2.getX(), p2.getY()), pt1(p1), pt2(p2) {
    setLength(); // Calculate length upon construction
}

// Override setLength to compute distance in 3D
void Line3D::setLength() {
    int x_diff = pt2.getX() - pt1.getX();
    int y_diff = pt2.getY() - pt1.getY();
    int z_diff = pt2.getZ() - pt1.getZ();
    length = sqrt(x_diff * x_diff + y_diff * y_diff + z_diff * z_diff);
}

// Accessor Methods
Point3D Line3D::getPt1() const {
    return pt1;
}

Point3D Line3D::getPt2() const {
    return pt2;
}

double Line3D::getScalarValue() const {
    return length;
}

// Mutator Methods
void Line3D::setPt1(Point3D p1) {
    pt1 = p1;
    Line2D::setPt1(p1.getX(), p1.getY()); // Update the base class part
    setLength(); // Recalculate length
}

void Line3D::setPt2(Point3D p2) {
    pt2 = p2;
    Line2D::setPt2(p2.getX(), p2.getY()); // Update the base class part
    setLength(); // Recalculate length
}

// Static methods for comparing Line3D objects using Point3D methods
    bool Line3D::compareP1asc(Line3D l1, Line3D l2)
    {
        const Point3D& p1 = l1.getPt1();
        const Point3D& p2 = l2.getPt1();
        
        // Compare X coordinates
        if (p1.getX() < p2.getX()) return true;
        if (p1.getX() > p2.getX()) return false;
        
        // If X coordinates are equal, compare Y coordinates
        if (p1.getY() < p2.getY()) return true;
        if (p1.getY() > p2.getY()) return false;

        // If Y coordinates are equal, compare Z coordinates
        if (p1.getZ() < p2.getZ()) return true;
        if (p1.getZ() > p2.getZ()) return false;

        // If both X, Y, and Z coordinates are equal, consider them equal
        return false;
    }
    bool Line3D::compareP1dsc(Line3D l1, Line3D l2)
    {
        const Point3D& p1 = l1.getPt1();
        const Point3D& p2 = l2.getPt1();
        
        // Compare X coordinates
        if (p1.getX() > p2.getX()) return true;
        if (p1.getX() < p2.getX()) return false;
        
        // If X coordinates are equal, compare Y coordinates
        if (p1.getY() > p2.getY()) return true;
        if (p1.getY() < p2.getY()) return false;

        // If Y coordinates are equal, compare Z coordinates
        if (p1.getZ() > p2.getZ()) return true;
        if (p1.getZ() < p2.getZ()) return false;

        // If both X, Y, and Z coordinates are equal, consider them equal
        return false;
    }
    bool Line3D::compareP2asc(Line3D l1, Line3D l2)
    {
        const Point3D& p1 = l1.getPt2();
        const Point3D& p2 = l2.getPt2();
        
        // Compare X coordinates
        if (p1.getX() < p2.getX()) return true;
        if (p1.getX() > p2.getX()) return false;
        
        // If X coordinates are equal, compare Y coordinates
        if (p1.getY() < p2.getY()) return true;
        if (p1.getY() > p2.getY()) return false;

        // If Y coordinates are equal, compare Z coordinates
        if (p1.getZ() < p2.getZ()) return true;
        if (p1.getZ() > p2.getZ()) return false;

        // If both X, Y, and Z coordinates are equal, consider them equal
        return false;
    }
    bool Line3D::compareP2dsc(Line3D l1, Line3D l2)
    {
        const Point3D& p1 = l1.getPt2();
        const Point3D& p2 = l2.getPt2();
        
        // Compare X coordinates
        if (p1.getX() > p2.getX()) return true;
        if (p1.getX() < p2.getX()) return false;
        
        // If X coordinates are equal, compare Y coordinates
        if (p1.getY() > p2.getY()) return true;
        if (p1.getY() < p2.getY()) return false;

        // If Y coordinates are equal, compare Z coordinates
        if (p1.getZ() > p2.getZ()) return true;
        if (p1.getZ() < p2.getZ()) return false;

        // If both X, Y, and Z coordinates are equal, consider them equal
        return false;
    }

// Static method to compare two Point3D objects based on distance from origin in ascending order
bool Line3D::compareLengthAsc(const Line3D& l1, const Line3D& l2) {
    return l1.getScalarValue() < l2.getScalarValue();
}

// Static method to compare two Point3D objects based on distance from origin in descending order
bool Line3D::compareLengthDsc(const Line3D& l1, const Line3D& l2) {
    return l1.getScalarValue() > l2.getScalarValue();
}

//---------------Display and Output Stream Method------------------------

// Friend function to overload the << operator for output
    ostream& operator<<(ostream& os, const Line3D& line3d) {
        Point3D pt1 = line3d.getPt1();
        Point3D pt2 = line3d.getPt2();
        os   << "[" << setw(4) << right << fixed << setprecision(3) << pt1.getX() 
             << "," << setw(5) << right << fixed << setprecision(3) << pt1.getY()
             << "," << setw(5) << right << fixed << setprecision(3) << pt1.getZ()
             << "]" << setw(4) << right << "[" 
                    << setw(4) << right << fixed << setprecision(3) << pt2.getX() 
             << "," << setw(5) << right << fixed << setprecision(3) << pt2.getY()
             << "," << setw(5) << right << fixed << setprecision(3) << pt2.getZ()
             << "]" << "   " << line3d.getScalarValue();
    
        return os;
    }

//----------------Overload operator Method--------------------------------------------

bool Line3D::operator==(const Line3D &obj) const
{
    return (pt1 == obj.getPt1() && pt2 == obj.getPt2());
}
bool Line3D::operator<(const Line3D &obj) const
{
    return (length < obj.getScalarValue());
}
bool Line3D::operator>(const Line3D &obj) const
{
    return (length > obj.getScalarValue());
}
