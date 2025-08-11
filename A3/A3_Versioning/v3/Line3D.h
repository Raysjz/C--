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
    Point3D pt1; // First point in 3D
    Point3D pt2; // Second point in 3D

    // Override the method to calculate the length of the line in 3D
    void setLength() override;

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

    // Friend function for outputting Point2D objects
    friend ostream& operator<<(ostream& os, const Line3D& line3d);
};

#endif
