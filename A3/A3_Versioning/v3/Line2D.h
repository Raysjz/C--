// Line2D.h
#ifndef LINE2D_H
#define LINE2D_H

// Header Files
#include "Point2D.h"

#include <cmath> // For sqrt function
#include <iostream>   // For standard input and output
#include <iomanip>    // For io manipulation
#include <vector>     // For vector container

class Line2D {
protected:
    Point2D pt1;    // First coordinate point
    Point2D pt2;    // Second coordinate point  
    double length;  // Length of the line

    virtual void setLength(); // Method to calculate the length of the line

public:
    // Default Constructors with default values of x , y and z
    Line2D(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0);

    // Constructor with Point2D parameters
    Line2D(Point2D p1, Point2D p2);

    // Accessor Methods
    Point2D getPt1() const;
    Point2D getPt2() const;
    double getScalarValue() const; // Get length of the line

    // Mutator Methods
    void setPt1(int x, int y);
    void setPt2(int x, int y);

    // Friend function for outputting Point2D objects
    friend ostream& operator<<(ostream& os, const Line2D& line2d);
};

#endif
