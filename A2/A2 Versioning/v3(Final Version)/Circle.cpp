// Circle.cpp

// Header Files
#include "Circle.h"
#include "ShapeTwoD.h"

// Circle Constructor
Circle::Circle(string name, bool containsWarpSpace, int id) {
  this->name = name;
  this->containsWarpSpace = containsWarpSpace;
  this->id = id;
  this->setCoord();  // Initialize circle's coordinates and radius
}

// Destructor implementation
Circle::~Circle() {
   // cout << "Circle destructor called" << endl;
}

// Get the area of the circle
double Circle::getArea() { return this->area; }

// Compute the area of the circle using the formula PI *R^2
double Circle::computeArea() { return M_PI * (this->radius * this->radius); }

// Check if a point is on the perimeter of the circle
bool Circle::isPointOnShape(int x, int y) {
  // Check if the point is exactly on the cardinal points of the circle's
  // perimeter
  if (x == xCoord && y == yCoord + radius)  // North
    return true;
  else if (x == xCoord + radius && y == yCoord)  // East
    return true;
  else if (x == xCoord && y == yCoord - radius)  // South
    return true;
  else if (x == xCoord - radius && y == yCoord)  // West
    return true;
  else
    return false;
}

// Check if a point is inside the circle
bool Circle::isPointInShape(int x, int y) {
  // Check if the point is within the circle using the distance formula
  return pow((x - this->xCoord), 2) + pow((y - this->yCoord), 2) <
         this->radius * this->radius;
}

// Generate a string representation of the circle
string Circle::toString() {
  string specType = (this->containsWarpSpace) ? "WS" : "NS";
  ostringstream output;
  ostringstream areaStream;

  // Add shape details
  output << "Shape[" << this->id << "]\n";
  output << "Name  : " << this->name << "\n";
  output << "Special Type : " << specType << "\n";

  // Format the area to 2 decimal places
  areaStream << fixed << setprecision(2) << this->area;
  output << "Area : " << areaStream.str() << " units Circle\n";

  // Add center point information (only vertex for circle)
  output << "Vertices : \n";
  output << "Point[0] : (" << this->xCoord << ", " << this->yCoord << ")\n";

  // Add points on the perimeter of the circle
  output << "Points on Perimeter : ";
  for (int i = xCoord - radius; i <= xCoord + radius; i++) {
    for (int j = yCoord - radius; j <= yCoord + radius; j++) {
      if (isPointOnShape(i, j)) {
        output << "(" << i << ", " << j << "), ";
      }
    }
  }

  // Remove trailing comma and space
  if (output.str().back() == ' ') {
    output.seekp(-2,
                 ios_base::end);  // Move the put pointer back by 2 positions
    output << ' ';                // Overwrite the trailing comma
  }

  // Add points within the circle
  if (this->radius == 1) {
    output << "\n\nPoints within shape : None!";
  } else {
    output << "\n\nPoints within shape : ";
    for (int i = xCoord - radius; i < xCoord + radius; i++) {
      for (int j = yCoord - radius; j < yCoord + radius; j++) {
        if (i == xCoord && j == yCoord) {
          continue;  // Skip the center point
        }

        if (isPointInShape(i, j)) {
          output << "(" << i << ", " << j << "), ";
        }
      }
    }

    // Remove trailing comma and space
    if (output.str().back() == ' ') {
      output.seekp(-2,
                   ios_base::end);  // Move the put pointer back by 2 positions
      output << ' ';                // Overwrite the trailing comma
    }
  }

  return output.str();
}

// Set the coordinates and radius of the circle
void Circle::setCoord() {
  // Validate x-coordinate input
  while (true) {
    cout << "Please enter x-ordinate of center : ";
    cin >> this->xCoord;
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
    cout << "Please enter y-ordinate of center : ";
    cin >> this->yCoord;
    if (cin.fail()) {
      cin.clear();  // Clear the error flag
      cin.ignore(numeric_limits<streamsize>::max(),
                 '\n');  // Ignore the invalid input
      cout << "Invalid input! Please enter an integer value.\n";
    } else {
      break;
    }
  }

  // Validate radius input
  while (true) {
    cout << "Please enter radius (units) : ";
    cin >> this->radius;
    if (cin.fail()) {
      cin.clear();  // Clear the error flag
      cin.ignore(numeric_limits<streamsize>::max(),
                 '\n');  // Ignore the invalid input
      cout << "Invalid input! Please enter an integer value.\n";
    } else {
      break;
    }
  }
}

// Set the area of the circle
void Circle::setArea() { this->area = computeArea(); }
