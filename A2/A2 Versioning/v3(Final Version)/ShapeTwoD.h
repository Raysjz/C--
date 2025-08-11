// ShapeTwoD.h
#ifndef SHAPETWOD_H
#define SHAPETWOD_H

#include <iostream> // For standard input and output operations
#include <limits>   // For defining numeric limits
#include <string>   // For string operations
#include <sstream>  // For string stream operations
#include <iomanip>  // For input/output manipulation
#include <cmath>    // For mathematical functions
#include <cstdlib>  // For general utilities

using namespace std; // Use the standard namespace to avoid prefixing std::

class ShapeTwoD  // abstract class
{
 protected:
  string name;
  bool containsWarpSpace;
  int id;

 public:
  // default constructor
  ShapeTwoD(string name = "", bool containsWarpSpace = false){};

  void setName(string name);

  // Accessor Methods
  string getName();
  virtual double getArea() = 0;
  bool getContainsWarpSpace();

  // presets
  virtual double computeArea() = 0;
  virtual bool isPointInShape(int x, int y) = 0;
  virtual bool isPointOnShape(int x, int y) = 0;

  // Mutator method
  void setContainsWarpSpace(bool containsWarpSpace);
  virtual void setArea() = 0;
  virtual void setCoord() = 0;

  // toString method
  virtual string toString() = 0;

  // virtual deconstructor
  virtual ~ShapeTwoD() = default;  // virtual destructor to prevent mem leaks
};

#endif
