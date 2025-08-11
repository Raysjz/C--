// Cross.h
#ifndef CROSS_H
#define CROSS_H


#include <iostream> // For standard input and output operations
#include <limits>   // For defining numeric limits
#include <string>   // For string operations
#include <sstream>  // For string stream operations
#include <iomanip>  // For input/output manipulation
#include <cmath>    // For mathematical functions

using namespace std; // Use the standard namespace to avoid prefixing std::

// Header Files
#include "ShapeTwoD.h"

class Cross : public ShapeTwoD {
 private:
  // Private characteristics of Cross
  int xCoord[12];  // 12 pair of coordinates
  int yCoord[12];
  int area = 0;
  int xMin = INT_MAX;
  int yMin = INT_MAX;
  int xMax = 0;
  int yMax = 0;

 public:
  // default constructor
  Cross(string name, bool containsWarpSpace, int id);

  // Accessor Methods
  double getArea();

  // presets
  double computeArea();
  bool isPointInShape(int x, int y);
  bool isPointOnShape(int x, int y);

  // Additional Preset
  bool isPointaVertex(int x, int y);
  int pnpoly(int nvert, int *vertx, int *verty, int testx, int testy);

  // Mutator method
  void setCoord();
  void setArea();

  // toString method
  string toString();
};

#endif