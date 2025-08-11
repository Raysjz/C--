// Point3D.cpp
#include "Point3D.h"
#include <cmath> // For sqrt function

// Constructor
Point3D::Point3D(int x, int y, int z) : Point2D(x, y), z(z) {
    setDistFrOrigin(); // Initialize distance from origin
}

// Accessor Methods
int Point3D::getZ() const {
    return z;
}

// Mutator Methods
void Point3D::setZ(int z) {
    this->z = z;
    setDistFrOrigin(); // Recalculate distance from origin
}

// Override setDistFrOrigin
void Point3D::setDistFrOrigin() {
    distFrOrigin = sqrt(getX() * getX() + getY() * getY() + z * z);
}

//---------------Display Method------------------------

// Friend function to overload the << operator for output
    ostream& operator<<(ostream& os, const Point3D& point3d) {
        os << "[" << setw(4) << right << fixed << setprecision(3) << point3d.getX() << "," 
                << setw(5) << right << fixed << setprecision(3) << point3d.getY() << "," 
                << setw(5) << right << fixed << setprecision(3) << point3d.getZ() << "]" 
                << "   " << fixed << setprecision(3) << point3d.getScalarValue();
        return os;
    }

//----------------Overload Method----------------------

// Overloads the < operator to compare points based on x, y, then z coordinates
bool Point3D::operator<(const Point3D& other) const { //const ensures it's not modified while comparing
    if (x == other.x) {
        if (y == other.y) {
            return z < other.z;  // If y-coordinates are the same, compare z-coordinates
        }
        return y < other.y;  // If x-coordinates are the same, compare y-coordinates
    }
    return x < other.x;  // Otherwise, compare x-coordinates
}

// Overloads the > operator to compare points based on x, y, then z coordinates
bool Point3D::operator>(const Point3D& other) const { //const ensures it's not modified while comparing
    if (x == other.x) {
        if (y == other.y) {
            return z > other.z;  // If y-coordinates are the same, compare z-coordinates
        }
        return y > other.y;  // If x-coordinates are the same, compare y-coordinates
    }
    return x > other.x;  // Otherwise, compare x-coordinates
}