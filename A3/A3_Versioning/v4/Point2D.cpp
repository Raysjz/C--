// Point2D.cpp

// Header Files
#include "Point2D.h"

// Point2D Constructor
Point2D::Point2D(int x, int y) : x(x), y(y) {
    setDistFrOrigin();
}

// Calculate and set the distance from the origin
void Point2D::setDistFrOrigin() {
    distFrOrigin = sqrt(x * x + y * y);
}

//---------------- Accessor Method--------------------

int Point2D::getX() const {
    return x;
}

int Point2D::getY() const {
    return y;
}

double Point2D::getScalarValue() const {
    return distFrOrigin;
}

//------------------- Mutator Method-------------------

void Point2D::setX(int x) {
    this->x = x;
    setDistFrOrigin(); // Recalculates the distance from origin
}

void Point2D::setY(int y) {
    this->y = y;
    setDistFrOrigin(); // Recalculates the distance from origin
}

//------------------- Static Boolean Method-------------------

// Static method to compare two Point2D objects based on two coordinates 
bool Point2D::compareXasc(const Point2D& x1, const Point2D& x2){    // X Ascending Order
    return x1.getX() < x2.getX(); 
}
bool Point2D::compareXdsc(const Point2D& x1, const Point2D& x2){    // X Descending Order
    return x1.getX() > x2.getX(); 
}

bool Point2D::compareYasc(const Point2D& x1, const Point2D& x2){    // Y Ascending Order
    return x1.getY() < x2.getY(); 
}

bool Point2D::compareYdsc(const Point2D& x1, const Point2D& x2){    // Y Descending Order
    return x1.getY() > x2.getY(); 
}

// Static method to compare two Point2D objects based on distance from origin in ascending order
bool Point2D::compareDistAsc(const Point2D& x1, const Point2D& x2) {
    return x1.getScalarValue() < x2.getScalarValue();
}

// Static method to compare two Point2D objects based on distance from origin in descending order
bool Point2D::compareDistDsc(const Point2D& x1, const Point2D& x2) {
    return x1.getScalarValue() > x2.getScalarValue();
}

//---------------Display and Output Stream Method------------------------

// Friend function to overload the << operator for output
    ostream& operator<<(ostream& os, const Point2D& point2d) {
        os << "[" << setw(4) << right << fixed << setprecision(3) << point2d.getX() << "," 
                    << setw(5) << right << fixed << setprecision(3) << point2d.getY() << "]" 
                    << "   " << fixed << setprecision(3) << point2d.getScalarValue();
        return os;
    }

//----------------Overload Method----------------------

// Overloads the < operator to compare points based on x, then y coordinates
bool Point2D::operator<(const Point2D& other) const { //const ensures its not modified while comparing
    if (x == other.x) {
        return y < other.y;  // If x-coordinates are the same, compare y-coordinates
    }
    return x < other.x;  // Otherwise, compare x-coordinates
}

// Overloads the > operator to compare points based on x, then y coordinates
bool Point2D::operator>(const Point2D& other) const { //const ensures its not modified while comparing
    if (x == other.x) {
        return y > other.y;  // If x-coordinates are the same, compare y-coordinates
    }
    return x > other.x;  // Otherwise, compare x-coordinates
}