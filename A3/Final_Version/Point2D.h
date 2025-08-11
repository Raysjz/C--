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

    // Static methods for comparing Point2D objects
    static bool compareXasc(const Point2D& x1, const Point2D& x2);
    static bool compareXdsc(const Point2D& x1, const Point2D& x2);
    static bool compareYasc(const Point2D& x1, const Point2D& x2);
    static bool compareYdsc(const Point2D& x1, const Point2D& x2);
    static bool compareDistAsc(const Point2D& x1, const Point2D& x2);
    static bool compareDistDsc(const Point2D& x1, const Point2D& x2);

    // Overload the == operator for Point2D
    bool operator==(const Point2D& obj) const;
    // Overloads the < operator for Point2D
    bool operator<(const Point2D& obj) const;
    // Overloads the > operator for Point2D
    bool operator>(const Point2D& obj) const;
    
    // Friend function to overload the << operator for output
    friend ostream& operator<<(ostream& os, const Point2D& point2d);

};

#endif

