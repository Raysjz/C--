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
    double length;  // Length of the line

    virtual void setLength(); // Method to calculate the length of the line

private :
    Point2D pt1;    // First coordinate point
    Point2D pt2;    // Second coordinate point


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

    // Static methods for comparing Line2D objects using Point2D methods
    static bool compareP1asc(Line2D l1, Line2D l2);
    static bool compareP1dsc(Line2D l1, Line2D l2);
    static bool compareP2asc(Line2D l1, Line2D l2);
    static bool compareP2dsc(Line2D l1, Line2D l2);
    // Static methods for comparing length with scalar distance
    static bool compareLengthAsc(const Line2D& l1, const Line2D& l2);
    static bool compareLengthDsc(const Line2D& l1, const Line2D& l2);

    // Overload the == operator for Line2D
    bool operator==(const Line2D& obj) const;
    // Overloads the < operator for Line2D
    bool operator<(const Line2D& obj) const;
    // Overloads the > operator for Line2D
    bool operator>(const Line2D& obj) const;
    
    // Friend function for outputting Line2D objects
    friend ostream& operator<<(ostream& os, const Line2D& line2d);
};

#endif
