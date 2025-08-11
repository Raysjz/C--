// Line3D.h
#ifndef LINE3D_H
#define LINE3D_H

// Header Files
#include "Point2D.h"
#include "Line2D.h"
#include "Point3D.h"

#include <cmath>      // For sqrt function
#include <iostream>   // For standard input and output
#include <iomanip>    // For io manipulation
#include <vector>     // For vector container

using namespace std;

class Line3D : public Line2D
{
protected:
    // Override the method to calculate the length of the line in 3D
    void setLength() override;

private:
    Point3D pt1; // First point in 3D
    Point3D pt2; // Second point in 3D


public:
    // Default Constructor
    Line3D(int x1 = 0, int y1 = 0, int z1 = 0, int x2 = 0, int y2 = 0, int z2 = 0);

    // Constructor with Point3D parameters
    Line3D(Point3D p1, Point3D p2);

    // Accessor Methods
    Point3D getPt1() const;
    Point3D getPt2() const;
    double getScalarValue() const; // Get length of the line

    // Mutator Methods
    void setPt1(Point3D p1);
    void setPt2(Point3D p2);

    // Static methods for comparing Line3D objects
    static bool compareP1asc(Line3D l1, Line3D l2);
    static bool compareP1dsc(Line3D l1, Line3D l2);
    static bool compareP2asc(Line3D l1, Line3D l2);
    static bool compareP2dsc(Line3D l1, Line3D l2);

    // Overload the equality operator
    bool operator==(const Line3D& other) const {
        return pt1 == other.pt1 && pt2 == other.pt2;
    }
    // Static methods for comparing length with scalar distance
    static bool compareLengthAsc(const Line3D& l1, const Line3D& l2);
    static bool compareLengthDsc(const Line3D& l1, const Line3D& l2);

    // Friend function for outputting Line3D objects
    friend ostream& operator<<(ostream& os, const Line3D& line3d);
};

#endif
