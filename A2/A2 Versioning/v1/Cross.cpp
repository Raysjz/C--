// Cross.cpp

// Header Files
#include "Cross.h"
#include "ShapeTwoD.h"

// Cross Constructor
Cross::Cross(string name, bool containsWarpSpace, int id) {
  this->name = name;
  this->containsWarpSpace = containsWarpSpace;
  this->id = id;
  this->setCoord();  // Initialize coordinates and calculate bounding box
}

// Get area of the cross shape
double Cross::getArea() { return this->area; }

// Compute the area of the cross shape using the Shoelace formula
double Cross::computeArea() {
  double crArea = 0;  // Accumulates area
  int j = 11;         // Start with the last vertex

  for (int i = 0; i < 12; i++) {
    crArea += (xCoord[j] + xCoord[i]) * (yCoord[j] - yCoord[i]);
    j = i;  // Update j to the current vertex
  }

  crArea = crArea / 2;
  crArea = abs(crArea);  // Take the absolute value of the area
  return crArea;
}

// Check if a point is inside the cross shape
bool Cross::isPointInShape(int x, int y) {
  return pnpoly(12, this->xCoord, this->yCoord, x, y);
}

// Determine if a point is within a polygon using the Ray Casting algorithm
int Cross::pnpoly(int nvert, int *vertx, int *verty, int testx, int testy) {
  int i, j, c = 0;
  for (i = 0, j = nvert - 1; i < nvert; j = i++) {
    // Check if the test point's y-coordinate is between the y-coordinates of
    // the vertices of the edge
    if (((verty[i] > testy) != (verty[j] > testy)) &&
        // Check if the test point's x-coordinate is to the left of the
        // intersection of the edge with the horizontal line
        (testx <
         (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) +
             vertx[i])) {
      c = !c;  // Toggle the flag for each intersection
    }
  }
  return c;  // Return 1 if inside, 0 if outside

  // This is the Ray Casting algorithm. It takes an (x, y) point and extends a
  // horizontal line to the right infinitely. If this line crosses any of the
  // edges of the polygon an odd number of times, the point is inside the
  // polygon. If it crosses an even number of times, the point is outside the
  // polygon.
}

// Check if a point is on the boundary of the cross shape
bool Cross::isPointOnShape(int x, int y) {
  for (int i = 0; i < 11; i++) {
    int ax = max(xCoord[i], xCoord[i + 1]);
    int bx = min(xCoord[i], xCoord[i + 1]);
    int ay = min(yCoord[i], yCoord[i + 1]);
    int by = max(yCoord[i], yCoord[i + 1]);

    if (ax == bx && x == ax && y > ay && y < by) {
      return true;
    }

    if (by == ay && y == by && x > bx && x < ax) {
      return true;
    }
  }

  // Check the final edge (connecting the last and first vertices)
  int ax = max(xCoord[11], xCoord[0]);
  int bx = min(xCoord[11], xCoord[0]);
  int ay = min(yCoord[11], yCoord[0]);
  int by = max(yCoord[11], yCoord[0]);

  if (ax == bx && x == ax && y > ay && y < by) {
    return true;
  }

  if (by == ay && y == by && x > bx && x < ax) {
    return true;
  }

  return false;
}

// Check if a point is one of the vertices of the cross shape
bool Cross::isPointaVertex(int x, int y) {
  for (int i = 0; i < 12; i++) {
    if (x == xCoord[i] && y == yCoord[i]) {
      return true;
    }
  }

  return false;
}

// Generate a string representation of the cross shape
string Cross::toString() {
  bool isCord = false;
  string specType = (this->containsWarpSpace) ? "WS" : "NS";
  ostringstream output;  // Stream to build the output string
  ostringstream pointStream;

  // Add shape details
  output << "Shape[" << this->id << "]\n";
  output << "Name  : " << this->name << "\n";
  output << "Special Type : " << specType << "\n";
  output << "Area : " << fixed << setprecision(2) << this->area
         << " units square\n";
  output << "Vertices : \n";

  // Add vertices
  for (int i = 0; i < 12; i++) {
    output << "Point[" << i << "] : (" << xCoord[i] << ", " << yCoord[i]
           << ")\n";
  }

  // Add points on the perimeter
  output << "\n\nPoints on Perimeter : ";
  int ptOnShapeCounter = 0;
  for (int i = xMin; i <= xMax; i++) {
    for (int j = yMin; j <= yMax; j++) {
      if (isPointOnShape(i, j)) {
        output << "(" << i << ", " << j << "), ";
        ptOnShapeCounter++;
      }
    }
  }

  if (ptOnShapeCounter == 0) {
    output << "None!";
  } else {
    string str = output.str();
    if (str.back() == ' ') {
      output.seekp(-2, ios_base::end);  // Remove trailing comma and space
      output << ' ';                    // Overwrite the trailing comma
    }
  }

  // Add points within the shape
  int ptsInShapeCounter = 0;
  output << "\n\nPoints within shape : ";
  for (int i = xMin + 1; i < xMax; i++) {
    for (int j = yMin + 1; j < yMax; j++) {
      if (isPointInShape(i, j) && !isPointOnShape(i, j) &&
          !isPointaVertex(i, j)) {
        output << "(" << i << ", " << j << "), ";
        ptsInShapeCounter++;
      }
    }
  }

  if (ptsInShapeCounter == 0) {
    output << "None!";
  } else {
    string str = output.str();
    if (str.back() == ' ') {
      output.seekp(-2, ios_base::end);  // Remove trailing comma and space
      output << ' ';                    // Overwrite the trailing comma
    }
  }

  return output.str();
}

// Set coordinates and calculate bounding box
void Cross::setCoord() {
  for (int i = 0; i < 12; i++) {
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

// Calculate the area of the cross shape
void Cross::setArea() { this->area = computeArea(); }