// Circle.h
#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream> // For standard input and output operations
#include <limits>   // For defining numeric limits
#include <string>   // For string operations
#include <sstream>  // For string stream operations
#include <iomanip>  // For input/output manipulation
#include <cmath>    // For mathematical functions

using namespace std; // Use the standard namespace to avoid prefixing std::

// Header Files
#include "ShapeTwoD.h"

class Circle : public ShapeTwoD {
 private:
  // Private characteristics of Circle
  int xCoord;  // 1 pair coordinate
  int yCoord;
  int radius;
  double area = 0;

 public:
  // default constructor
  Circle(string name, bool containsWarpSpace, int id);

  // Accessor Methods
  double getArea();

  // presets
  double computeArea();
  bool isPointInShape(int x, int y);
  bool isPointOnShape(int x, int y);

  // Mutator method
  void setCoord();
  void setArea();

  // toString method
  string toString();
};

#endif