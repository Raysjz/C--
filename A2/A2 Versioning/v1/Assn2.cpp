/*
UOW ID:8466385
Name: Raydon See Jing Zhou
Program Name : Assn2 Shapes Program C++11
*/

// Assn2.cpp

#include <iostream>  // For standard input and output
#include <limits>    // For numeric limits
#include <string>    // For string operations
#include <vector>    // For vector container
#include <algorithm> // For algorithms like sort
#include <cctype>    // For toUpper case
#include <fstream>  // For file operations

// Header Files
#include "Circle.h"
#include "Cross.h"
#include "Rectangle.h"
#include "ShapeTwoD.h"
#include "Square.h"

//----------------- Function Prototypes

// Menu
void displayMenu();
void processOption(int choice);
void waitForEnter();

// Function to make String Uppercase
string stringToUpper(string &sInput);

// Shapes
void inputSensorData();
void computeArea();
void printShapesReport();
void displaySortmenu();

void sortAscending(vector<ShapeTwoD *> Shapes);
void sortDescending(vector<ShapeTwoD *> Shapes);
void sortType(vector<ShapeTwoD *> Shapes);

// Delete Array
void deallocateMemory();

// Additional Feature
void displayOutputmenu();
void outputToFile(vector<ShapeTwoD *> Shapes, string filename);
void outputShapes(vector<ShapeTwoD *> Shapes, string filename);


// Global variables
int shapeCounter = 0;         // Counter for each Shape added to Array
ShapeTwoD *shapesArray[100];  // Set size of array to store 100 shapes

using namespace std;

int main() {
  int choice;

  do {
    displayMenu();
    cin >> choice;

    // Clear input buffer in case of invalid input
    if (cin.fail()) {
      cin.clear();  // Clear the error flag
      cin.ignore(numeric_limits<streamsize>::max(),
                 '\n');  // Discard invalid input
      choice = 0;        // Set choice to 0 to prompt user again
    }

    processOption(choice);

    if (choice >= 1 && choice <= 3) {
      waitForEnter();
    }

  } while (choice != 6);

  return 0;
}

// Displays Menu
void displayMenu() {
  // Menu Display
  cout << endl;
  cout << "Student ID\t: See Jing Zhou Raydon" << endl;
  cout << "Student Name\t: 8466385" << endl;
  cout << "-----------------------------------------------" << endl;
  cout << "Welcome to Assn2 program!\n" << endl;
  cout << "1)        Input sensor data" << endl;
  cout << "2)        Compute area(for all records)" << endl;
  cout << "3)        Print shapes report" << endl;
  cout << "4)        Sort shapes data" << endl;
  cout << "5)        Output shapes data to txt file" << endl;
  cout << "6)        Quit\n" << endl;
  cout << "Please enter your choice: ";
}

// Option Processor
void processOption(int choice) {
  switch (choice) {
    case 1:
      // Call function to input sensor data
      inputSensorData();
      break;
    case 2:
      // Call function to compute area
      computeArea();
      break;
    case 3:
      // Prints shapes report
      printShapesReport();
      break;
    case 4:
      // Sort shapes data
      displaySortmenu();
      break;
    case 5:
      // Output sorted shapes data file
      displayOutputmenu();
      break;
    case 6:
      // Quit the program
      deallocateMemory();
      cout << endl;
      cout << "Thank you for using Shapes program, have a nice day!" << endl;
      break;
    default:
      cout << "[Invalid input]\n"
           << endl;  // Outputs this if invalid input is keyed
      cin.clear();   // Clear input stream state
      break;
  }
}
void waitForEnter() {
  cout << endl;
  cout << "Press<Enter> to go back to the main menu...";
  cin.ignore(numeric_limits<streamsize>::max(),
             '\n');  // Discard any remaining input
  cin.clear();       // Clear input stream state
  cin.get();         // Wait for user to press Enter
}

string stringToUpper(string &sInput)  // Makes all string uppercase to make it
// easier for readability and consistency
{
  string sOutput = sInput;  // Make a copy of the input string
  transform(sOutput.begin(), sOutput.end(), sOutput.begin(), ::toupper);
  return sOutput;
}

// function to read in user input and append the shape to the shape array
void inputSensorData() {
  string shapeName;
  string tempShape;
  string specialType;
  bool containWarpSpace;

  // Prompt user for name of shape
  cout << "Please enter name of shape: ";
  cin >> shapeName;
  tempShape = stringToUpper(shapeName);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  // Prompt the user for special type with validation
  while (true) {
    cout << "Please enter special type (WS or NS): ";
    cin >> specialType;
    specialType = stringToUpper(specialType);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (specialType == "WS" || specialType == "NS") {
      containWarpSpace = (specialType == "WS");
      break;  // Exit loop if valid input
    } else {
      cout << "Invalid special type. Please enter 'WS/ws' or 'NS/ns'." << endl;
    }
  }

  ShapeTwoD *newShape = nullptr;

  //  Creates the appropriate shape based on user input
  if (tempShape == "SQUARE") {
    newShape = new Square(shapeName, containWarpSpace, shapeCounter);
  } else if (tempShape == "RECTANGLE") {
    newShape = new Rectangle(shapeName, containWarpSpace, shapeCounter);
  } else if (tempShape == "CIRCLE") {
    newShape = new Circle(shapeName, containWarpSpace, shapeCounter);
  } else if (tempShape == "CROSS") {
    newShape = new Cross(shapeName, containWarpSpace, shapeCounter);
  }

  // For every newShape created is added, it is incremented in shapeCounter of
  // ShapeArray
  if (newShape) {
    shapesArray[shapeCounter++] = newShape;
    cout << endl;
    cout << "Record successfully stored. Going back to main menu....." << endl;
  } else {
    cout << endl;
    cout << "Invalid shape name, exiting to menu" << endl << endl;
  }

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Computes Area
void computeArea() {
  for (int i = 0; i < shapeCounter; i++) {
    // Iterate over the shape array
    shapesArray[i]
        ->setArea();  // Call setArea to compute the area for each shape
  }

  cout << endl;
  cout << "Computation completed! (" << shapeCounter << " records were updated)"
       << endl;
}

void printShapesReport() {
  cout << endl;
  cout << "Total no. of records available = " << shapeCounter << endl << endl;

  for (int i = 0; i < shapeCounter; i++) {
    // iterates the shape array calling the toString function
    cout << shapesArray[i]->toString() << endl << endl;
  }
}

// Display subMenu for sorting
void displaySortmenu() {
  // get the array stored into a local vector to preserve the original shape
  // order by id
  vector<ShapeTwoD *> Shapes;
  for (int i = 0; i < shapeCounter; i++) {
    Shapes.push_back(shapesArray[i]);
  }

  char choice;
  cout << "    a)      Sort by area (ascending)" << endl;
  cout << "    b)      Sort by area (descending)" << endl;
  cout << "    c)      Sort by special type and area" << endl;
  cout << endl;

  cout << "Please select sort option ('q' to go main menu): ";
  cin >> choice;
  cout << endl;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  // switch statement for each sort type
  switch (choice) {
    case 'a':
      // Sort by Ascending
      cout << "Sort by area(smallest to largest) ... " << endl << endl;
      sortAscending(Shapes);
      cout << endl;
      break;
    case 'b':
      // Sort by Descending
      cout << "Sort by area(largest to smallest) ... " << endl << endl;
      sortDescending(Shapes);
      cout << endl;
      break;
    case 'c':
      // Sort by Special type and Area
      cout << "Sort by Special Type(largest to smallest) ..." << endl << endl;
      sortType(Shapes);
      cout << endl;
    case 'q':
      cout << "Going back to main menu." << endl << endl;
      break;
  }
}

// Ascending sort using comparator of lambda
void sortAscending(vector<ShapeTwoD *> Shapes)
{
  sort(Shapes.begin(), Shapes.end(), [](ShapeTwoD *lhs, ShapeTwoD *rhs) {
    return lhs->getArea() < rhs->getArea();
  });
  for (int i = 0; i < Shapes.size(); i++) {
    cout << Shapes[i]->toString() << endl << endl;
  }
}

// Descending sort using comparator of lambda
void sortDescending(vector<ShapeTwoD *> Shapes) {
  sort(Shapes.begin(), Shapes.end(), [](ShapeTwoD *lhs, ShapeTwoD *rhs) {
    return lhs->getArea() > rhs->getArea();
  });
  for (int i = 0; i < Shapes.size(); i++) {
    cout << Shapes[i]->toString() << endl << endl;
  }
}

// Special sort, priority given to WS type then NS type followed by largest
// area to smallest area
void sortType(vector<ShapeTwoD *> Shapes) {
  vector<ShapeTwoD *> specialNS;  // vector to store shapes with NS type
  vector<ShapeTwoD *> specialWS;  // vector to store shapes with WS type
  // get all NS type
  for (int i = 0; i < Shapes.size(); i++) {
    if (Shapes[i]->getContainsWarpSpace() == false) {
      specialNS.push_back(Shapes[i]);
    } else {
      specialWS.push_back(Shapes[i]);
    }
  }

  // Sort each category in descending order by area
  sortDescending(specialWS);
  sortDescending(specialNS);
}

// Output sorted shapes
void displayOutputmenu() {
  // get the array stored into a local vector to preserve the original shape
  // order by id
  vector<ShapeTwoD *> Shapes;
  for (int i = 0; i < shapeCounter; i++) {
    Shapes.push_back(shapesArray[i]);
  }
  string outputFile;
  char choice;
  cout << "    a)      Outputs Shapes to output file" << endl;
  cout << endl;

  cout << "Please select sort option ('q' to go main menu): ";
  cin >> choice;
  cout << endl;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  // switch statement for each sort type
  switch (choice) {
    case 'a':
      // Outputs file
      cout << "Please enter filename of txt: " << endl;
      cin >> outputFile;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Outputting Shapes to file ... " << endl
           << endl;
      outputShapes(Shapes, outputFile);
      cout << endl;
      break;
    case 'q':
      cout << "Going back to main menu." << endl << endl;
      break;
  }
}


void outputToFile(vector<ShapeTwoD *> Shapes, string filename) {
  ofstream outputFile(filename);
  if (outputFile.is_open()) {
    for (auto shape : Shapes) {
      outputFile << shape->toString() << endl << endl;
    }
    outputFile.close();
  } else {
    cerr << "Error: Unable to open file " << filename << " for writing."
         << endl;
  }
  
}

// Output Shapes
void outputShapes(vector<ShapeTwoD *> Shapes, string filename) {
  for (auto Shape : Shapes) {
    cout << Shape->toString() << endl << endl;
    outputToFile(Shapes, filename);  // Output the file
  }
  cout << "Shapes Array have been successfully written to " << filename << ".txt" << endl;
}

// Deletes Dynamic Memory
void deallocateMemory() {
  for (int i = 0; i < shapeCounter; i++) {
    delete shapesArray[i];
    shapesArray[i] = nullptr;  // Set pointer to nullptr for safety
  }
}