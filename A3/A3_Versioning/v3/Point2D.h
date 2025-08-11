// Point2D.h
#ifndef POINT2D_H
#define POINT2D_H

#include <cmath>      // For sqrt function
#include <iostream>   // For standard input and output
#include <iomanip>    // For io manipulation
#include <vector>     // For vector container

using namespace std; // Use the standard namespace to avoid prefixing std::

// Definition of the Point2D class
class Point2D
{
protected:
    int x;                 // The x-coordinate of the point
    int y;                 // The y-coordinate of the point
    double distFrOrigin;   // Distance from the origin

    virtual void setDistFrOrigin(); // Calculate the distance from the origin

public:
    // Default Constructor with default values of x and y 
    Point2D(int x = 0, int y = 0);

    // Accessor Methods
    int getX() const;
    int getY() const;
    double getScalarValue() const;

    // Mutator Methods
    void setX(int x);
    void setY(int y);

    // Friend function for outputting Point2D objects
    friend ostream& operator<<(ostream& os, const Point2D& point2d);

    // Overloads the < operator to compare points based on x, then y coordinates
    bool operator<(const Point2D& other) const;

    // Overloads the > operator to compare points based on x, then y coordinates
    bool operator>(const Point2D& other) const;
};

#endif

