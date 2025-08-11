// Point3D.h
#ifndef POINT3D_H
#define POINT3D_H

// Header Files
#include "Point2D.h"

#include <cmath> // For sqrt function
#include <iostream>   // For standard input and output
#include <iomanip>    // For io manipulation
#include <vector>     // For vector container

using namespace std; // Use the standard namespace to avoid prefixing std::

// Definition of Point3D class
class Point3D : public Point2D 
{
protected:
    int z; 
    void setDistFrOrigin() override;  // Method to calculate distance from origin
    
public:
    // Default Constructor with default values of x , y and z
    Point3D(int x = 0 , int y = 0 , int z = 0); 

    // Accessor Methods
    int getZ() const;

    // Mutator Methods
    void setZ(int z);

    // Static methods for comparing Point3D objects
    static bool compareXasc(const Point3D& x1, const Point3D& x2);
    static bool compareXdsc(const Point3D& x1, const Point3D& x2);
    static bool compareYasc(const Point3D& x1, const Point3D& x2);
    static bool compareYdsc(const Point3D& x1, const Point3D& x2);
    static bool compareZasc(const Point3D& x1, const Point3D& x2);
    static bool compareZdsc(const Point3D& x1, const Point3D& x2);
    static bool compareDistAsc(const Point3D& x1, const Point3D& x2);
    static bool compareDistDsc(const Point3D& x1, const Point3D& x2);

    // Overload the == operator for Point3D
    bool operator==(const Point3D& obj) const;
    // Overloads the < operator for Point3D
    bool operator<(const Point3D& obj) const;
    // Overloads the > operator for Point3D
    bool operator>(const Point3D& obj) const;

    // Friend function to overload the << operator for output
    friend ostream& operator<<(ostream& os, const Point3D& point3d);

};

#endif