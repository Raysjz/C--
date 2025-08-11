// ShapeTwoD.h
#ifndef SHAPETWOD_H
#define SHAPETWOD_H

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

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
