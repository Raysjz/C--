// ShapeTwoD.cpp

// Header Files
#include "ShapeTwoD.h"
using namespace std;

// Mutator Method
void ShapeTwoD::setName(string name) { this->name = name; }

void ShapeTwoD::setContainsWarpSpace(bool containsWarpSpace) {
  this->containsWarpSpace = containsWarpSpace;
}

// Accessor Method

// Gets Name
string ShapeTwoD::getName() { return name; }

// Gets WarpSpace
bool ShapeTwoD::getContainsWarpSpace() { return containsWarpSpace; }