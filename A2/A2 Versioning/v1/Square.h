// Square.h
#ifndef SQUARE_H
#define SQUARE_H

#include <iostream> // For standard input and output operations
#include <limits>   // For defining numeric limits
#include <string>   // For string operations
#include <sstream>  // For string stream operations
#include <iomanip>  // For input/output manipulation
#include <cmath>    // For mathematical functions

using namespace std;

// Header Files
#include "ShapeTwoD.h"

class Square : public ShapeTwoD {
 private:
  // Private characteristics of Square
  int xCoord[4];  // 4 pair of coordinates
  int yCoord[4];
  int area = 0;
  int xMin = INT_MAX;
  int yMin = INT_MAX;
  int xMax = 0;
  int yMax = 0;

 public:
  // default constructor
  Square(string name, bool containsWarpSpace, int id);

  // Accessor Methods
  double getArea();

  // presets
  double computeArea();
  bool isPointInShape(int x, int y);
  bool isPointOnShape(int x, int y);

  // toString
  string toString();

  // Mutator method
  void setCoord();
  void setArea();
};

#endif