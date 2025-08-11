// Point3D.cpp

// Header Files
#include "Point3D.h"

// Point3D Constructor
Point3D::Point3D(int x, int y, int z) : Point2D(x, y), z(z) {
    setDistFrOrigin(); // Initialize distance from origin
}

//---------------- Accessor Method--------------------

int Point3D::getZ() const {
    return z;
}

//------------------- Mutator Method-------------------

void Point3D::setZ(int z) {
    this->z = z;
    setDistFrOrigin(); // Recalculate distance from origin
}

// Override setDistFrOrigin
void Point3D::setDistFrOrigin() {
    distFrOrigin = sqrt(getX() * getX() + getY() * getY() + z * z);
}

//------------------- Static Boolean Method-------------------

// Static method to compare two Point3D objects based on two coordinates 
bool Point3D::compareXasc(const Point3D& x1, const Point3D& x2) {    // X Ascending Order  
    return x1.getX() < x2.getX(); 
}

bool Point3D::compareXdsc(const Point3D& x1, const Point3D& x2){     // X Descending Order
    return x1.getX() > x2.getX(); 
}

bool Point3D::compareYasc(const Point3D& x1, const Point3D& x2){     // Y Ascending Order
    return x1.getY() < x2.getY(); 
}


bool Point3D::compareYdsc(const Point3D& x1, const Point3D& x2){     // Y Descending Order
    return x1.getY() > x2.getY(); 
}

bool Point3D::compareZasc(const Point3D& x1, const Point3D& x2){     // Z Ascending Order
    return x1.getZ() < x2.getZ(); 
}


bool Point3D::compareZdsc(const Point3D& x1, const Point3D& x2){     // Z Descending Order
    return x1.getZ() > x2.getZ(); 
}

// Static method to compare two Point3D objects based on distance from origin in ascending order
bool Point3D::compareDistAsc(const Point3D& x1, const Point3D& x2) {
    return x1.getScalarValue() < x2.getScalarValue();
}

// Static method to compare two Point3D objects based on distance from origin in descending order
bool Point3D::compareDistDsc(const Point3D& x1, const Point3D& x2) {
    return x1.getScalarValue() > x2.getScalarValue();
}


//---------------Display and Output Stream Method------------------------

// Friend function to overload the << operator for output
    ostream& operator<<(ostream& os, const Point3D& point3d) {
        os << "[" << setw(4) << right << fixed << setprecision(3) << point3d.getX() << "," 
                << setw(5) << right << fixed << setprecision(3) << point3d.getY() << "," 
                << setw(5) << right << fixed << setprecision(3) << point3d.getZ() << "]" 
                << "   " << fixed << setprecision(3) << point3d.getScalarValue();
        return os;
    }

//----------------Overload operator Method--------------------------------------------

bool Point3D::operator==(const Point3D &obj) const
{
    return (this->x == obj.getX() && this->y == obj.getY() && this->z == obj.getZ());
}
bool Point3D::operator<(const Point3D &obj) const
{
    return (distFrOrigin < obj.getScalarValue());
}
bool Point3D::operator>(const Point3D &obj) const
{
    return (distFrOrigin > obj.getScalarValue());
}
