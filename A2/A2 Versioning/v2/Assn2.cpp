/*
UOW ID:8466385
Name: Raydon See Jing Zhou
Program Name : Assn2 Shapes Program C++11
*/

// Assn2.cpp
#include <algorithm>  // For algorithms like sort
#include <cctype>     // For toUpper case
#include <fstream>    // For file operations
#include <iostream>   // For standard input and output
#include <limits>     // For numeric limits
#include <string>     // For string operations
#include <vector>     // For vector container

// Header Files
#include "Circle.h"
#include "Cross.h"
#include "Rectangle.h"
#include "ShapeTwoD.h"
#include "Square.h"

using namespace std;  // Use the standard namespace to avoid prefixing std::

// Global variables
int shapeCounter = 0;         // Counter for each Shape added to Array
ShapeTwoD *shapesArray[100];  // Set size of array to store 100 shapes
string outputFile;

//--------------------------------------------------------------------------
//                          Function Prototype
//--------------------------------------------------------------------------



//---------------------------------Menu-------------------------------------------------------
void displayMenu();
void processOption(int choice);
void waitForEnter();

//-------------------------------Shapes-------------------------------------------------------

// Function to make String Uppercase
string stringToUpper(string &sInput);

//Inputs & Outputs
void inputSensorData();
void computeArea();
void printShapesReport();

// Display Sort menu
void displaySortmenu();

// Sorting
void sortAscending(vector<ShapeTwoD *> Shapes);
void sortDescending(vector<ShapeTwoD *> Shapes);
void sortType(vector<ShapeTwoD *> Shapes);

//-------------------------------Additional Feature--------------------------------------------

// Display Output menu
void displayExportmenu();

// Outputs Files
void inputFilename(string &outputFile);
void exportToFile(vector<ShapeTwoD *> Shapes, string filename);
void exportAscending(vector<ShapeTwoD *> Shapes, string filename);
void exportDescending(vector<ShapeTwoD *> Shapes, string filename);
void exportType(vector<ShapeTwoD *> Shapes, string filename);

//-------------------------------Delete Array--------------------------------------------------
void deallocateMemory();

int main() {  //------------Start of Main--------------------------------------------------------

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

    if (choice >= 2 && choice <= 3) { //only prompts choice 2 and 3 to exit menu as they are view only
      waitForEnter();
    }

  } while (choice != 6);

  return 0;
} //-------------------------------------End of Main------------------------------------------------


//------------------------------------Start of Menu ------------------------------------------------

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
  cout << "5)        Export Shapes Data to txt" << endl;
  cout << "6)        Quit\n" << endl;
  cout << "Please enter your choice: ";
}

// Option Processor
void processOption(int choice) {
  switch (choice) {
    case 1:
      // Call function to input sensor data
      cout << endl;
      cout << "[ Input sensor data ]" << endl;
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
      displayExportmenu();
      break;
    case 6:
      // Quit the program
      deallocateMemory();
      cout << endl;
      cout << "Thank you for using Assn2 program, have a nice day!" << endl;
      cout << endl;
      break;
    default:
      cout << endl;
      cout << "[Invalid Input]\n"
           << endl;  // Outputs this if invalid input is keyed
      cin.clear();   // Clear input stream state
      break;
  }
}

void waitForEnter() {
  cout << endl;
  cout << "Press <Enter> to go back to the main menu ...";
  cin.ignore(numeric_limits<streamsize>::max(),
             '\n');  // Discard any remaining input
  cin.clear();       // Clear input stream state
  cin.get();         // Wait for user to press Enter
}

//----------------------End of menu -----------------------------------------------------------------


//------------------------------Start of Shapes-------------------------------------------------------

string stringToUpper(string &sInput)  // Makes all string uppercase to make it
// easier for readability and consistency in the appropriate shape function
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
  cout << "Please enter special type (WS or NS): ";
  cin >> specialType;
  specialType = stringToUpper(specialType);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');


  ShapeTwoD *newShape = nullptr;

  //  Creates the appropriate shape based on user input
  if (tempShape == "SQUARE") {
    shapeName = "Square"; //setting ShapeName to Square for consistency
    newShape = new Square(shapeName, containWarpSpace, shapeCounter);
  } else if (tempShape == "RECTANGLE") {
    shapeName = "Rectangle"; //setting for visibility
    newShape = new Rectangle(shapeName, containWarpSpace, shapeCounter);
  } else if (tempShape == "CIRCLE") {
    shapeName = "Circle"; //setting for visibility
    newShape = new Circle(shapeName, containWarpSpace, shapeCounter);
  } else if (tempShape == "CROSS") {
    shapeName = "Cross"; //setting for visibility
    newShape = new Cross(shapeName, containWarpSpace, shapeCounter);
  }

  // For every newShape created is added, it is incremented in shapeCounter of
  // ShapeArray
  if (newShape) {
    shapesArray[shapeCounter++] = newShape;
    cout << endl;
    cout << "Record successfully stored. Going back to main menu ..." << endl;
  } else {
    cout << endl;
    cout << "[Invalid Input] , press <Enter> to exit to main menu ..." << endl << endl;
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
  cout << "Computation completed! ( " << shapeCounter << " records were updated )"
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
  bool validInput = false;  // Flag to check if valid input is provided

  while (!validInput) {
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
        validInput = true;  // Set flag to true to exit loop
        break;
      case 'b':
        // Sort by Descending
        cout << "Sort by area(largest to smallest) ... " << endl << endl;
        sortDescending(Shapes);
        cout << endl;
        validInput = true;  // Set flag to true to exit loop
        break;
      case 'c':
        // Sort by Special type and Area
        cout << "Sort by Special Type(largest to smallest) ..." << endl << endl;
        sortType(Shapes);
        cout << endl;
        validInput = true;  // Set flag to true to exit loop
        break;
      case 'q':
        cout << "Going back to main menu." << endl << endl;
        validInput = true;  // Set flag to true to exit loop
        break;
      default:
        cout << "[Invalid input]\n" << endl;  // Outputs this if invalid input is keyed
        cin.clear();                         // Clear input stream state
        break;
    }
  }
}

// Ascending sort using comparator of lambda
void sortAscending(vector<ShapeTwoD *> Shapes) {
  if (Shapes.empty()) {
    cout << "No shapes to sort. The list is empty." << endl;
    return;  // Exits the function early
  }

  sort(Shapes.begin(), Shapes.end(), [](ShapeTwoD *lhs, ShapeTwoD *rhs) {
    return lhs->getArea() < rhs->getArea();
  });
  for (int i = 0; i < Shapes.size(); i++) {
    cout << Shapes[i]->toString() << endl << endl;
  }
}

// Descending sort using comparator of lambda
void sortDescending(vector<ShapeTwoD *> Shapes) {
  if (Shapes.empty()) {
    cout << "No shapes to sort. The list is empty." << endl;
    return;  // Exits the function early
  }

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
  if (Shapes.empty()) {
    cout << "No shapes to sort. The list is empty." << endl;
    return;  // Exits the function early
  }

  vector<ShapeTwoD *> specialNS;  // vector to store shapes with NS type
  vector<ShapeTwoD *> specialWS;  // vector to store shapes with WS type
  // gets all WS or NS types
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

//-----------------------------End of Shapes-------------------------------------------------------

//-----------------------------Start of Additional Feature-----------------------------------------

// Output sorted shapes
void displayExportmenu() {
  // get the array stored into a local vector to preserve the original shape
  // order by id
  vector<ShapeTwoD *> Shapes;
  for (int i = 0; i < shapeCounter; i++) {
    Shapes.push_back(shapesArray[i]);
  }

  char choice;
  bool validInput = false;  // Flag to check if valid input is provided

  while (!validInput) {
    cout << "    a)      Export Shapes to txt.File sorted by area (ascending)" << endl;
    cout << "    b)      Export Shapes to txt.File sorted by area (descending)" << endl;
    cout << "    c)      Export Shapes to txt.File sorted by special type and area" << endl;
    cout << endl;

    cout << "Please select sort option ('q' to go main menu): ";
    cin >> choice;
    cout << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // switch statement for each sort type
    switch (choice) {
      case 'a':
        // Sort by Ascending
        cout << "Export file sorted by area(smallest to largest) ... " << endl << endl;
        inputFilename(outputFile);
        exportAscending(Shapes, outputFile);
        cout << endl;
        validInput = true;  // Set flag to true to exit loop
        break;
      case 'b':
        // Sort by Descending
        cout << "Export file sorted by area(largest to smallest) ... " << endl << endl;
        inputFilename(outputFile);
        exportDescending(Shapes, outputFile);
        cout << endl;
        validInput = true;  // Set flag to true to exit loop
        break;
      case 'c':
        // Sort by Special type and Area
        cout << "Export file sorted by Special Type(largest to smallest) ..." << endl << endl;
        inputFilename(outputFile);
        exportType(Shapes, outputFile);
        cout << endl;
        validInput = true;  // Set flag to true to exit loop
        break;
      case 'q':
        cout << "Going back to main menu." << endl << endl;
        validInput = true;  // Set flag to true to exit loop
        break;
      default:
        cout << "[Invalid input]\n" << endl;  // Outputs this if invalid input is keyed
        cin.clear();  // Clear input stream state
        break;
    }
  }
}


void inputFilename(string &outputFile) {  // Bypass reference for filename
  cout << "Please enter filename of txt: ";
  cin >> outputFile;
  outputFile += ".txt";  // Appends txt file straight
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void exportToFile(vector<ShapeTwoD *> Shapes, string filename) {
  if (Shapes.empty()) {
    cout << endl;
    cout << "No shapes to export. The list is empty." << endl;
    return;  // Exits the function early
  }

  ofstream outputFile(filename);
  if (outputFile.is_open()) {
    for (auto shape : Shapes) {
      outputFile << shape->toString() << endl << endl;
    }
    outputFile.close();
  } else {
    cerr << "Error: Unable to open file " << filename << " for writing." << endl;
  }
  cout << endl;
  cout << "Shapes output saved to ... " << filename << endl;
}

// Output Ascending
void exportAscending(vector<ShapeTwoD *> Shapes, string filename) {
  vector<ShapeTwoD *> tempShapes = Shapes;  // Create a temporary vector

  sort(tempShapes.begin(), tempShapes.end(),
       [](ShapeTwoD *lhs, ShapeTwoD *rhs) {
         return lhs->getArea() < rhs->getArea();
       });
  // Debug
  /*
    for (int i = 0; i < tempShapes.size(); i++) {
      cout << tempShapes[i]->toString() << endl << endl;
    }
  */

  exportToFile(tempShapes,
               filename);  // Output the ascending sorted shapes to a file
}

// Output Descending
void exportDescending(vector<ShapeTwoD *> Shapes, string filename) {
  vector<ShapeTwoD *> tempShapes = Shapes;  // Create a temporary vector

  sort(tempShapes.begin(), tempShapes.end(),
       [](ShapeTwoD *lhs, ShapeTwoD *rhs) {
         return lhs->getArea() > rhs->getArea();
       });
  // Debug
  /*
    for (int i = 0; i < tempShapes.size(); i++) {
      cout << tempShapes[i]->toString() << endl << endl;
    }
  */

  exportToFile(tempShapes,
               filename);  // Output the descending sorted shapes to a file
}

// Output WS type then NS Type
void exportType(vector<ShapeTwoD *> Shapes, string filename) {
  vector<ShapeTwoD *> combined;   // vector to combine both NS and WS type
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

  sort(specialWS.begin(), specialWS.end(), [](ShapeTwoD *lhs, ShapeTwoD *rhs) {
    return lhs->getArea() > rhs->getArea();
  });

  sort(specialNS.begin(), specialNS.end(), [](ShapeTwoD *lhs, ShapeTwoD *rhs) {
    return lhs->getArea() > rhs->getArea();
  });

  // Combines NS and WS to a single vector for outputting
  combined.insert(combined.end(), specialWS.begin(), specialWS.end());
  combined.insert(combined.end(), specialNS.begin(), specialNS.end());

  // Debug
  /*
   for (int i = 0; i < combined.size() ; i++){
    cout << combined[i]->toString() << endl << endl;
   }
  */
  exportToFile(combined,
               filename);  // Output the WS then NS sorted shapes to a file
}

//-----------------------------End of Additional Feature--------------------------------------------

//-------------------------------Delete Array-------------------------------------------------------

// Deletes Dynamic Memory
void deallocateMemory() {
  for (int i = 0; i < shapeCounter; i++) {
    delete shapesArray[i];
    shapesArray[i] = nullptr;  // Set pointer to nullptr for safety
  }
}