// Rectangle.cpp

// Header Files
#include "Rectangle.h"
#include "ShapeTwoD.h"

// Rectangle Constructor
Rectangle::Rectangle(string name, bool containsWarpSpace, int id) {
  this->name = name;
  this->containsWarpSpace = containsWarpSpace;
  this->id = id;
  this->setCoord();  // Initialize coordinates and bounds
}

// Get the area of the rectangle
double Rectangle::getArea() { return this->area; }

// Compute the area of the rectangle using the Shoelace formula
double Rectangle::computeArea() {
  double recArea = 0;
  int j = 3;  // Initialize to the last vertex for area calculation

  // Calculate area using the vertices
  for (int i = 0; i < 4; i++) {
    recArea += (xCoord[j] + xCoord[i]) * (yCoord[j] - yCoord[i]);
    j = i;  // Update previous vertex
  }

  recArea = abs(recArea) / 2;  // Compute absolute value and divide by 2
  return recArea;
}

// Check if a point is inside the rectangle
bool Rectangle::isPointInShape(int x, int y) {
  return (x > this->xMin && x < this->xMax && y > this->yMin && y < this->yMax);
}

// Check if a point is on the perimeter of the rectangle
bool Rectangle::isPointOnShape(int x, int y) {
  return (x == this->xMin && y >= this->yMin && y <= this->yMax) ||
         (y == this->yMax && x >= this->xMin && x <= this->xMax) ||
         (x == this->xMax && y >= this->yMin && y <= this->yMax) ||
         (y == this->yMin && x >= this->xMin && x <= this->xMax);
}

// Generate a string representation of the rectangle
string Rectangle::toString() {
  bool nonVertex = false;
  string specType = (this->containsWarpSpace) ? "WS" : "NS";
  ostringstream oss;

  // Add shape details
  oss << "Shape[" << this->id << "]\n";
  oss << "Name  : " << this->name << "\n";
  oss << "Special Type : " << specType << "\n";
  oss << "Area : " << this->area << " units square\n";
  oss << "Vertices : \n";

  // Add vertices
  for (int i = 0; i < 4; i++) {
    oss << "Point[" << i << "] : (" << xCoord[i] << ", " << yCoord[i] << ")\n";
  }

  // Add points on perimeter
  int ptOnShapeCounter = 0;
  oss << "Points on Perimeter : ";
  for (int i = xMin; i <= xMax; i++) {
    for (int j = yMin; j <= yMax; j++) {
      nonVertex = false;  // Reset nonVertex flag for each point check
      for (int k = 0; k < 4; k++) {
        if (xCoord[k] == i && yCoord[k] == j) {
          nonVertex = true;
          break;  // Exit loop if point is a vertex
        }
      }

      if (isPointOnShape(i, j) && !nonVertex) {
        oss << "(" << i << ", " << j << "), ";
        ptOnShapeCounter++;
      }
    }
  }

  if (ptOnShapeCounter == 0) {
    oss << "None!";
  } else {
    oss.seekp(-2, ios_base::end);  // Remove trailing comma and space
    oss << "  ";
  }

  // Add points within the shape
  int ptInShapeCounter = 0;
  oss << "\n\nPoints within shape : ";
  for (int i = xMin; i <= xMax; i++) {
    for (int j = yMin; j <= yMax; j++) {
      if (isPointInShape(i, j)) {
        oss << "(" << i << ", " << j << "), ";
        ptInShapeCounter++;
      }
    }
  }

  if (ptInShapeCounter == 0) {
    oss << "None!";
  } else {
    oss.seekp(-2, ios_base::end);  // Remove trailing comma and space
    oss << "  ";
  }

  return oss.str();
}

// Set the coordinates and bounds of the rectangle
void Rectangle::setCoord() {
  for (int i = 0; i < 4; i++) {
    // Validate x-coordinate input
    while (true) {
      cout << "Please enter x-ordinate of point " << i + 1 << " : ";
      cin >> this->xCoord[i];
      if (cin.fail()) {
        cin.clear();  // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(),
                   '\n');  // Ignore the invalid input
        cout << "Invalid input! Please enter an integer value.\n";
      } else {
        break;
      }
    }

    // Validate y-coordinate input
    while (true) {
      cout << "Please enter y-ordinate of point " << i + 1 << " : ";
      cin >> this->yCoord[i];
      if (cin.fail()) {
        cin.clear();  // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(),
                   '\n');  // Ignore the invalid input
        cout << "Invalid input! Please enter an integer value.\n";
      } else {
        break;
      }
    }

    // Update bounds
    if (i == 0) {
      this->xMin = this->xCoord[i];
      this->yMin = this->yCoord[i];
    }

    if (this->xCoord[i] < xMin) this->xMin = this->xCoord[i];
    if (this->yCoord[i] < yMin) this->yMin = this->yCoord[i];
    if (this->xCoord[i] > xMax) this->xMax = this->xCoord[i];
    if (this->yCoord[i] > yMax) this->yMax = this->yCoord[i];
  }
}

// Set the area of the rectangle
void Rectangle::setArea() { this->area = computeArea(); }