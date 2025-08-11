/*
UOW ID:8466385
Name: Raydon See Jing Zhou
Program Name : Line Origin System C++11
*/
#include <iostream>   // For standard input and output
#include <vector>     // For vector container
#include <fstream>    // For file operations
#include <iostream>   // For standard input and output
#include <limits>     // For numeric limits
#include <string>     // For string operations
#include <algorithm>  // For find function
#include <iomanip>    // For io manipulation

// Header Files
#include "Point2D.h"
#include "Line2D.h"
#include "Point3D.h"
#include "Line3D.h"

//Global variables
int filter_index = 0;  // Defaults to "Point2D"
int sort_index = 0;    // Defaults to "x-ordinate"
int order_index = 0;   // Defaults to "ASC"

// Respective record counter for outputting (calculated during processing)
int p2dCounter = 0;
int p3dCounter = 0;
int l2dCounter = 0;
int l3dCounter = 0;

// Vectors to store collections of data
vector<string> allRecords;
vector<string> uniqueRecords;
vector<string> outputVector;  // Stores output for file output when printing sorted order

// 4 class containers vectors
vector<Point2D> p2dVector;
vector<Line2D> l2dVector;
vector<Point3D> p3dVector;
vector<Line3D> l3dVector;

// Arrays storing values for filtering, sorting criteria, and sorting order
string filter_mode[] = {"Point2D", "Point3D", "Line2D", "Line3D"};
string sort_mode[] = {"x-ordinate",     "y-ordinate", "z-ordinate",
                      "Dist.Fr Origin", "Pt.1",       "Pt.2",
                      "Length"};
string order_mode[] = {"ASC", "DSC"};

//--------------------------------------------------------------------------
//                          Function Prototype
//--------------------------------------------------------------------------

vector<string> tokenizeString(string input, string delimiter);

// Trim function to remove spacing
string trimLeft(const string& str);
string trimRight(const string& str);
string trim(const string& str);

//------------------------------Menu------------------------------------------
void displayMenu(string filterCriteria, string sortCriteria, string sortOrder);
void filterMenu(int& filter_index);
void sortMenu(int filter_index, int& sort_index);
void orderMenu(int& order_index);
void waitForEnter();
//----------------------------Processing--------------------------------------
void readInput();
void processingUniqueRecords();

//------------------------Display and Output---------------------------------
void SortAndDisplay(string filterCriteria, string sortCriteria,
                    string sortOrder);

void storeOutputVector(string filterCriteria, string sortCriteria,
                       string sortOrder, vector<string>& outputVector);

void writeVectorToFile(vector<string>& outputVector, string& filename);

using namespace std;  // Use the standard namespace to avoid prefixing std::


int main() { // Start of main...
  int choice;
  bool bEnd = false;  // Boolean Flag to end program

  while (!bEnd) {
    displayMenu(filter_mode[filter_index], sort_mode[sort_index],
                order_mode[order_index]);
    cin >> choice;
    cout << endl;

    switch (choice) {
      case 1:
        // Read in Data
        readInput();
        processingUniqueRecords();
        waitForEnter();
        break;
      case 2:
        // Specify filtering criteria
        filterMenu(filter_index);
        waitForEnter();
        break;
      case 3:
        // Specify sorting criteria
        sortMenu(filter_index, sort_index);
        waitForEnter();
        break;
      case 4:
        // Specify sorting order
        orderMenu(order_index);
        waitForEnter();
        break;
      case 5:
        // View data
        SortAndDisplay(filter_mode[filter_index], sort_mode[sort_index],
                       order_mode[order_index]);
        waitForEnter();
        break;
      case 6:
        // Store data
        storeOutputVector(filter_mode[filter_index], sort_mode[sort_index],
                          order_mode[order_index], outputVector);
        waitForEnter();
        break;
      case 7:
        // Quit the program
        bEnd = true; // Flag to end program
        cout << endl;
        cout << "Thank you for using Assn3 program, have a nice day!" << endl;
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

  return 0;
} // end of main ...

vector<string> tokenizeString(string input, string delimiter) {
  size_t pos = 0;
  string token;
  vector<string> result;

  while ((pos = input.find(delimiter)) != string::npos) {
    token = input.substr(0, pos);
    result.push_back(token);
    input.erase(0, pos + delimiter.length());
  }

  result.push_back(input);

  return (result);
}

// Trim leading spaces
string trimLeft(const string& str) {
  size_t start = str.find_first_not_of(" \t\n\r\f\v");
  return (start == string::npos) ? "" : str.substr(start);
}

// Trim trailing spaces
string trimRight(const string& str) {
  size_t end = str.find_last_not_of(" \t\n\r\f\v");
  return (end == string::npos) ? "" : str.substr(0, end + 1);
}

// Trims both leading and trailing spaces
string trim(const string& str) { return trimRight(trimLeft(str)); }

//----------------Start of menu--------------------------------

void filterMenu(int& filter_index) {
  if (allRecords.empty()) {
    cout << endl;
    cout << "[No Records to filter, records is empty]" << endl;
    return;  // Exits the function early
  }

  char choice;

  cout << "[ Specifying filtering criteria "
       << "(current : " << filter_mode[filter_index] << ") ]\n\n";
  cout << "\ta)\tPoint2D records" << endl;
  cout << "\tb)\tPoint3D records" << endl;
  cout << "\tc)\tLine2D records" << endl;
  cout << "\td)\tLine3D records\n" << endl;

  cout << "\tPlease enter your criteria (a - d): ";
  cin >> choice;

  switch (choice) {
    case 'a':
      // Filter criteria to Point2D records
      filter_index = 0;  // Resets overall selection to Point2D , X-ordinate and Asc
      sort_index = 0;
      order_index = 0;
      break;
    case 'b':
      // Filter criteria to Point3D records
      filter_index = 1;  // Resets overall selection to Point3D , X-ordinate and Asc
      sort_index = 0;
      order_index = 0;
      break;
    case 'c':
      // Filter criteria to Line2D records
      filter_index = 2; // Resets overall selection to Line2D , Pt.1 and Asc
      sort_index = 4;
      order_index = 0;
      break;
    case 'd':
      // Filter criteria to Line3D records
      filter_index = 3; // Resets overall selection to Line3D , Pt.1 and Asc
      sort_index = 4;
      order_index = 0;
      break;
    default:
     // Default sets to Point2D if user enters any char other than a - d
      filter_index = 0;
      sort_index = 0;
      order_index = 0;
      cin.clear();
      break;
  }
  cout << "\tFilter criteria successfully set to "
       << "'" << filter_mode[filter_index] << "'!\n";
}

void sortMenu(int filter_index, int& sort_index) {
  if (allRecords.empty()) {
    cout << endl;
    cout << "[No Records to filter, records is empty]" << endl;
    return;  // Exits the function early
  }

  char choice;
  if (filter_mode[filter_index] == "Point2D") {
    cout << "[ Specifying sorting criteria "
         << "(current : " << sort_mode[sort_index] << ") ]\n\n";
    cout << "\ta)\tX ordinate value" << endl;
    cout << "\tb)\tY ordinate value" << endl;
    cout << "\tc)\tDist. Fr Origin value\n" << endl;

    cout << "\tPlease enter your criteria (a - c): ";
    cin >> choice;

    switch (choice) {
      case 'a':
        sort_index = 0;      // x-ordinate selection
        break;
      case 'b':
        sort_index = 1;      // y-ordinate selection
        break;
      case 'c':
        sort_index = 3;      // Dist.Fr Origin selection
        break;
      default:
        sort_index = 0;
        cin.clear();
        break;
    }
  } else if (filter_mode[filter_index] == "Point3D") {
    cout << "[ Specifying sorting criteria "
         << "(current : " << sort_mode[sort_index] << ") ]\n\n";
    cout << "\ta)\tX ordinate value" << endl;
    cout << "\tb)\tY ordinate value" << endl;
    cout << "\tc)\tZ ordinate value" << endl;
    cout << "\td)\tDist. Fr Origin value\n" << endl;

    cout << "\tPlease enter your criteria (a - d): ";
    cin >> choice;

    switch (choice) {
      case 'a':
        sort_index = 0;      // x-ordinate selection
        break;
      case 'b':
        sort_index = 1;      // y-ordinate selection
        break;
      case 'c':
        sort_index = 2;      // z-oordinate selection
        break;
      case 'd':
        sort_index = 3;      // Dist.Fr Origin
        break;
      default:
        sort_index = 0;
        cin.clear();
        break;
    }
  } else if (filter_mode[filter_index] == "Line2D") {
    cout << "[ Specifying sorting criteria "
         << "(current : " << sort_mode[sort_index] << ") ]\n\n";
    cout << "\ta)\tPt. 1's (x, y) values" << endl;
    cout << "\tb)\tPt. 2's (x, y) values" << endl;
    cout << "\tc)\tLength value\n" << endl;

    cout << "\tPlease enter your criteria (a - c): ";
    cin >> choice;

    switch (choice) {
      case 'a':
        sort_index = 4;     // Pt.1 selection
        break;
      case 'b':
        sort_index = 5;     // Pt.2 selection
        break;
      case 'c':
        sort_index = 6;     // Length selection
        break;
      default:
        sort_index = 4;
        cin.clear();
        break;
    }
  } else if (filter_mode[filter_index] == "Line3D") {
    cout << "[ Specifying sorting criteria "
         << "(current : " << sort_mode[sort_index] << ") ]\n\n";
    cout << "\ta)\tPt. 1's (x, y) values" << endl;
    cout << "\tb)\tPt. 2's (x, y) values" << endl;
    cout << "\tc)\tLength value\n" << endl;

    cout << "\tPlease enter your criteria (a - c): ";
    cin >> choice;

    switch (choice) {
      case 'a':
        sort_index = 4;     // Pt 1 selection
        break;
      case 'b':
        sort_index = 5;     // Pt 2 selection
        break;
      case 'c':
        sort_index = 6;     // Length selection
        break;
      default:
        sort_index = 4;
        cin.clear();
        break;
    }
  }
  cout << "\tSort criteria successfully set to "
       << "'" << sort_mode[sort_index] << "'!\n";
}

void orderMenu(int& order_index) {
  if (allRecords.empty()) {
    cout << endl;
    cout << "[No Records to filter, records is empty]" << endl;
    return;  // Exits the function early
  }

  char choice;

  cout << "[ Specifying sorting order "
       << "(current : " << order_mode[order_index] << ") ]\n\n";
  cout << "\ta)\tASC (Ascending order)" << endl;
  cout << "\tb)\tDSC (Descending order)\n" << endl;

  cout << "\tPlease enter your criteria (a - b): ";
  cin >> choice;

  switch (choice) {
    case 'a':
      // Select sort order to Ascending
      order_index = 0;
      break;
    case 'b':
      // Select sort order to Descending
      order_index = 1;
      break;
    default:
      order_index = 0;
      cin.clear();
      break;
  }
  cout << "\tSorting order successfully set to "
       << "'" << order_mode[order_index] << "'!\n";
}

// Displays Menu
void displayMenu(string filterCriteria, string sortCriteria, string sortOrder) {
  // Menu Display
  cout << endl;
  cout << "Student ID\t: abc" << endl;
  cout << "Student Name\t: 3344" << endl;
  cout << "-----------------------------------------------" << endl;
  cout << "Welcome to Assn3 program!\n" << endl;
  cout << "1)\tRead in data" << endl;
  cout << "2)\tSpecify filtering criteria (current: "
       << filter_mode[filter_index] << ")" << endl;
  cout << "3)\tSpecify sorting criteria   (current: " << sort_mode[sort_index]
       << ")" << endl;
  cout << "4)\tSpecify sorting order      (current: " << order_mode[order_index]
       << ")" << endl;
  cout << "5)\tView data" << endl;
  cout << "6)\tStore data" << endl;
  cout << "7)\tQuit\n" << endl;
  cout << "Please enter your choice: ";
}

void waitForEnter() {
  cout << endl;
  cout << "Press <Enter> to go back to the main menu ...";
  cin.ignore(numeric_limits<streamsize>::max(),
             '\n');  // Discard any remaining input
  cin.clear();       // Clear input stream state
  cin.get();         // Wait for user to press Enter
}

//----------------------End of menu--------------------------------------------


//---------------------Start of Processing--------------------------------------

void readInput() {
  string inputFilename;
  string temps;
  string temps2;
  string temps3;
  string temps4;
  string temps5;
  string temps6;
  string temps7;
  vector<string> tempStr;
  string aLine;

  uniqueRecords.clear();  // Clear uniqueRecords to start fresh
  allRecords.clear();  // Clear allRecords to start fresh
  int counter = 0;       // Counter for total records processed

  cout << "Please enter filename: ";
  cin >> inputFilename;
  inputFilename += ".txt";  // Appending .txt to fileName for // enhanced user experience

  ifstream inputFile(inputFilename.c_str());
  if (!inputFile) {
    cerr << "Failed to open " << inputFilename << endl;
    return;
  }

  // cout << endl;
  while (getline(inputFile, aLine)) {
    if (!aLine.empty()) { // Checks for End-Of-File
      // cout << aLine << endl;

      tempStr = tokenizeString(aLine, ",");

      temps = tempStr[0]; // Splits string of type to Point2D , Point3D , Line2D , Line3D

      if (tempStr[0] == "Point2D") { // Point2D
        if (tempStr.size() == 3) { // Process based on size of string
          temps = tempStr[0];       // Type Label
          temps2 = tempStr[1];      // x-oordinate
          temps3 = tempStr[2];      // y-oordinate

          temps2 = temps2.substr(2, temps2.length());
          temps3 = trim(temps3.substr(0, temps3.length() - 1));

          counter++;
          p2dCounter++;

          // Concatenate the values into a single string and push to the records
          // vector
          string record = temps + "," + temps2 + "," + temps3;
          allRecords.push_back(record);
        }
      } else if (tempStr[0] == "Line2D") { // Line2D
        if (tempStr.size() == 5) { // Process based on size of string
          temps = tempStr[0];       // Type Label
          temps2 = tempStr[1];      // x1-oordinate
          temps3 = tempStr[2];      // y1-oordinate
          temps4 = tempStr[3];      // x2-oordinate
          temps5 = tempStr[4];      // y2-oordinate

          temps2 = temps2.substr(2, temps2.length());
          temps3 = trim(temps3.substr(0, temps3.length() - 1));
          temps4 = temps4.substr(2, temps4.length());
          temps5 = trim(temps5.substr(0, temps5.length() - 1));

          counter++;
          l2dCounter++;

          // Concatenate the values into a single string and push to the records
          // vector
          string record =
              temps + "," + temps2 + "," + temps3 + "," + temps4 + "," + temps5;
          allRecords.push_back(record);
        }
      } else if (tempStr[0] == "Point3D") { // Point3D
        if (tempStr.size() == 4) { // Process based on size of string
          temps = tempStr[0];       // Type Label
          temps2 = tempStr[1];      // x-oordinate
          temps3 = tempStr[2];      // y-oordinate
          temps4 = tempStr[3];      // z-oordinate

          temps2 = temps2.substr(2, temps2.length());
          temps3 = trim(temps3);
          temps4 = trim(temps4.substr(0, temps4.length() - 1));

          counter++;
          p3dCounter++;

          // Concatenate the values into a single string and push to the records
          // vector
          string record = temps + "," + temps2 + "," + temps3 + "," + temps4;
          allRecords.push_back(record);
        }
      } else if (tempStr[0] == "Line3D") { // Line3D
        if (tempStr.size() == 7) { // Process based on size of string
          temps = tempStr[0];       // Type Label
          temps2 = tempStr[1];      // x1-oordinate
          temps3 = tempStr[2];      // y1-oordinate
          temps4 = tempStr[3];      // z1-oordinate
          temps5 = tempStr[4];      // x2-oordinate
          temps6 = tempStr[5];      // y2-oordinate
          temps7 = tempStr[6];      // z2-oordinate

          temps2 = temps2.substr(2, temps2.length());
          temps3 = trim(temps3);
          temps4 = trim(temps4.substr(0, temps4.length() - 1));
          temps5 = temps5.substr(2, temps5.length());
          temps6 = trim(temps6);
          temps7 = trim(temps7.substr(0, temps7.length() - 1));

          counter++;
          l3dCounter++;

          // Concatenate the values into a single string and push to the records
          // vector
          string record = temps + "," + temps2 + "," + temps3 + "," + temps4 +
                          "," + temps5 + "," + temps6 + "," + temps7;
          allRecords.push_back(record);
        }
      }
    }
  }
  cout << endl;

  cout << counter << " records read in successfully!" << endl << endl;

  cout << "Going back to main menu ...\n" << endl;

  /*
// For debugging purposes, print allRecords
cout << "\nAll Records:\n";
for (string record : allRecords) {
  cout << record << endl;
}
  cout << endl;
  */
}

void processingUniqueRecords() {

  // Iterate through all records
  for (string record : allRecords) {
    // Check if the record is already in uniqueRecords
    if (find(uniqueRecords.begin(), uniqueRecords.end(), record) ==
        uniqueRecords.end()) {
      // Record is not found in uniqueRecords, then add it in
      uniqueRecords.push_back(record);
    }
  }

  /* For debugging purposes, print uniqueRecords
  cout << "\nUnique Records:\n";
for (string record : uniqueRecords) {
  cout << record << endl;
}
  cout << endl;
  */

  // Set 3 decimal points for output
  cout << fixed << setprecision(3);

  // Iterate through unique records
  for (string records : uniqueRecords) {
    vector<string> classToken =
        tokenizeString(records, ",");  // Use UniqueRecords for tokenization

    if (classToken.size() > 0) {
      string type = trim(classToken[0]);  // Trim spaces from the type string
      // cout << endl;

      // Print the extracted type for debugging
      // cout << "Extracted type: '" << type << "'" << endl;

      if (type == "Point2D") {
        if (classToken.size() == 3) {
          string x1 = trim(classToken[1]);
          string y1 = trim(classToken[2]);

          // Convert x and y to integers
          int v1 = stoi(x1);
          int v2 = stoi(y1);

          p2dVector.push_back(Point2D(v1, v2));

          // cout << "\nProcessing Point2D with x: " << x1 << ", y: " << y1 <<
          // endl;
        }
      } else if (type == "Line2D") {
        if (classToken.size() == 5) {
          string x1 = trim(classToken[1]);
          string y1 = trim(classToken[2]);
          string x2 = trim(classToken[3]);
          string y2 = trim(classToken[4]);

          // Convert x and y to integers
          int v1 = stoi(x1);
          int v2 = stoi(y1);
          int v3 = stoi(x2);
          int v4 = stoi(y2);

          l2dVector.push_back(Line2D(Point2D(v1, v2), Point2D(v3, v4)));

          // Process Line2D record
          // cout << "Processing Line2D with points (" << x1 << ", " << y1 << ")
          // and ("<< x2 << ", " << y2 << ")" << endl;
        }
      } else if (type == "Point3D") {
        if (classToken.size() == 4) {
          string x1 = trim(classToken[1]);
          string y1 = trim(classToken[2]);
          string z1 = trim(classToken[3]);

          // Convert x, y and z to integers
          int v1 = stoi(x1);
          int v2 = stoi(y1);
          int v3 = stoi(z1);

          p3dVector.push_back(Point3D(v1, v2, v3));

          // cout << "\nProcessing point3D with x: " << x1 << ", y: " << y1 <<
          // ", z: " << z1 << endl;
        }
      } else if (type == "Line3D") {
        if (classToken.size() == 7) {
          string x1 = classToken[1];
          string y1 = classToken[2];
          string z1 = classToken[3];
          string x2 = classToken[4];
          string y2 = classToken[5];
          string z2 = classToken[6];

          // Convert x, y and z to integers
          int v1 = stoi(x1);
          int v2 = stoi(y1);
          int v3 = stoi(z1);
          int v4 = stoi(x2);
          int v5 = stoi(y2);
          int v6 = stoi(z2);

          l3dVector.push_back(Line3D(Point3D(v1, v2, v3), Point3D(v4, v5, v6)));

          // Process Line3D record
          // cout << "Processing Line3D with points (" << x1 << ", " << y1 << ",
          // " << z1 << ") and ("<< x2 << ", " << y2 << ", " << z2 << ")" <<
          // endl;
        }
      } else {
        cout << "Unknown record type: " << type << endl;
      }
    }
  }
}


//---------------------End of Processing--------------------------------------

void SortAndDisplay(string filterCriteria, string sortCriteria,
                    string sortOrder) {
  cout << "[ Viewing Data ... ]" << endl;
  cout << "filtering criteria : " << filter_mode[filter_index] << endl;
  cout << "sorting criteria : " << sort_mode[sort_index] << endl;
  cout << "sorting order : " << order_mode[order_index] << endl;
  cout << endl;

  if (filterCriteria == "Point2D") {
    if (p2dVector.empty()) {
      cout << "[No available Point2D records to display]" << endl;
      return;  // Exit function early as records is empty
    } else {
      if (sortCriteria == "x-ordinate") {
        if (sortOrder == "ASC") {
          sort(p2dVector.begin(), p2dVector.end(),Point2D::compareXasc);
        } else {  // Descending order 
          sort(p2dVector.begin(), p2dVector.end(),Point2D::compareXdsc);
        }
      } else if (sortCriteria == "y-ordinate") {
        if (sortOrder == "ASC") {
          sort(p2dVector.begin(), p2dVector.end(),Point2D::compareYasc);
        } else {  // Descending order 
          sort(p2dVector.begin(), p2dVector.end(),Point2D::compareYdsc);
        }
      } else if (sortCriteria == "Dist.Fr Origin") {
        if (sortOrder == "ASC") {
          sort(p2dVector.begin(), p2dVector.end(),Point2D::compareDistAsc);
        } else {  // Descending order 
          sort(p2dVector.begin(), p2dVector.end(),Point2D::compareDistDsc);
        }
      }
      cout << setw(5) << right << "X" << setw(6) << right << "Y"
           << "    Dist. Fr Origin" << endl
           << "- - - - - - - - - - - - - - - - - - -" << endl;
      for (auto& point2d : p2dVector) {
        cout << point2d << endl;
      }
    }
  } else if (filterCriteria == "Point3D") {
    if (p3dVector.empty()) {
      cout << "[No available Point3D records to display]" << endl;
      return;
    } else {
      if (sortCriteria == "x-ordinate") {
        if (sortOrder == "ASC") {
          sort(p3dVector.begin(), p3dVector.end(),Point3D::compareXasc);;
        } else {  // Descending order 
          sort(p3dVector.begin(), p3dVector.end(),Point3D::compareXdsc);
        }
      } else if (sortCriteria == "y-ordinate") {
        if (sortOrder == "ASC") {
          sort(p3dVector.begin(), p3dVector.end(),Point3D::compareYasc);
        } else {  // Descending order 
          sort(p3dVector.begin(), p3dVector.end(),Point3D::compareYdsc);
        }
      } else if (sortCriteria == "z-ordinate") {
        if (sortOrder == "ASC") {
          sort(p3dVector.begin(), p3dVector.end(),Point3D::compareZasc);
        } else {  // Descending order 
          sort(p3dVector.begin(), p3dVector.end(),Point3D::compareZdsc);
        }
      } else if (sortCriteria == "Dist.Fr Origin") {
        if (sortOrder == "ASC") {
          sort(p3dVector.begin(), p3dVector.end(),Point3D::compareDistAsc);
        } else {  // Descending order 
          sort(p3dVector.begin(), p3dVector.end(),Point3D::compareDistDsc);
        }
      }
      cout << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6)
           << right << "Z"
           << "    Dist. Fr Origin" << endl
           << "- - - - - - - - - - - - - - - - - - -" << endl;
      for (auto& point3d : p3dVector) {
        cout << point3d << endl;
      }
    }
  } else if (filterCriteria == "Line2D") {
    if (l2dVector.empty()) {
      cout << "[No available Line2D records to display]" << endl;
      return;
    } else {
      if (sortCriteria == "Pt.1") {
        if (sortOrder == "ASC") {
          sort(l2dVector.begin(), l2dVector.end(),Line2D::compareP1asc);
        } else {  // Descending order 
          sort(l2dVector.begin(), l2dVector.end(),Line2D::compareP1dsc);
        }
      } else if (sortCriteria == "Pt.2") {
        if (sortOrder == "ASC") {
          sort(l2dVector.begin(), l2dVector.end(),Line2D::compareP2asc);
        } else {  // Descending order 
          sort(l2dVector.begin(), l2dVector.end(),Line2D::compareP2dsc);
        }
      } else if (sortCriteria == "Length") {
        if (sortOrder == "ASC") {
          sort(l2dVector.begin(), l2dVector.end(),Line2D::compareLengthAsc);
        } else {  // Descending order 
          sort(l2dVector.begin(), l2dVector.end(),Line2D::compareLengthDsc);
        }
      }
      cout << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y"
           << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y"
           << "    Length" << endl
           << "- - - - - - - - - - - - - - - - - - -" << endl;
      for (auto& line2d : l2dVector) {
        cout << line2d << endl;
      }
    }

  } else if (filterCriteria == "Line3D") {
    if (l3dVector.empty()) {
      cout << "[No available Line3D records to display]" << endl;
      return;
    } else {
      if (sortCriteria == "Pt.1") {
        if (sortOrder == "ASC") {
          sort(l3dVector.begin(), l3dVector.end(),Line3D::compareP1asc);
        } else {  // Descending order 
          sort(l3dVector.begin(), l3dVector.end(),Line3D::compareP1dsc);
        }
      } else if (sortCriteria == "Pt.2") {
        if (sortOrder == "ASC") {
          sort(l3dVector.begin(), l3dVector.end(),Line3D::compareP2asc);
        } else {  // Descending order 
          sort(l3dVector.begin(), l3dVector.end(),Line3D::compareP2dsc);
        }
      } else if (sortCriteria == "Length") {
        if (sortOrder == "ASC") {
          sort(l3dVector.begin(), l3dVector.end(),Line3D::compareLengthAsc);
        } else {  // Descending order 
          sort(l3dVector.begin(), l3dVector.end(),Line3D::compareLengthDsc);
        }
      }
    }
    cout << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(6)
         << right << "P1-Z" << setw(9) << right << "P2-X" << setw(6) << right
         << "P2-Y" << setw(6) << right << "P2-Z"
         << "    Length" << endl
         << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    for (auto& line3d : l3dVector) {
      cout << line3d << endl;
    }
  }
}

void storeOutputVector(string filterCriteria, string sortCriteria,
                       string sortOrder, vector<string>& outputVector) {
    
  outputVector.clear(); // Clear outputVector to allow user to output another file
  string outputFilename;
  cout << "Please enter filename :";
  cin >> outputFilename;
  outputFilename += ".txt";

  // Create a string stream to format the output
  ostringstream oss;

  if (filterCriteria == "Point2D") {
    if (p2dVector.empty()) {
      cout << "[No available Point2D records to output]" << endl;
      return;  // Exit function early as records is empty
    } else {
      if (sortCriteria == "x-ordinate") {
        if (sortOrder == "ASC") {
          sort(p2dVector.begin(), p2dVector.end(),Point2D::compareXasc);
        } else {  // Descending order 
          sort(p2dVector.begin(), p2dVector.end(),Point2D::compareXdsc);
        }
      } else if (sortCriteria == "y-ordinate") {
        if (sortOrder == "ASC") {
          sort(p2dVector.begin(), p2dVector.end(),Point2D::compareYasc);
        } else {  // Descending order 
          sort(p2dVector.begin(), p2dVector.end(),Point2D::compareYdsc);
        }
      } else if (sortCriteria == "Dist.Fr Origin") {
        if (sortOrder == "ASC") {
          sort(p2dVector.begin(), p2dVector.end(),Point2D::compareDistAsc);
        } else {  // Descending order 
          sort(p2dVector.begin(), p2dVector.end(),Point2D::compareDistDsc);
        }
      }
      oss << setw(5) << right << "X" << setw(6) << right << "Y"
          << "    Dist. Fr Origin" << endl
          << "- - - - - - - - - - - - - - - - - - -" << endl;
      for (auto& point2d : p2dVector) {
        oss << point2d << endl;
      }

      // Store the formatted string in the output vector
      outputVector.push_back(oss.str());

      writeVectorToFile(outputVector, outputFilename);
      cout << endl;
      cout << p2dCounter << " records output succesfully!\n" << endl;
    }
  } else if (filterCriteria == "Point3D") {
    if (p3dVector.empty()) {
      cout << "[No available Point3D records to output]" << endl;
      return;
    } else {
      if (sortCriteria == "x-ordinate") {
        if (sortOrder == "ASC") {
          sort(p3dVector.begin(), p3dVector.end(),Point3D::compareXasc);;
        } else {  // Descending order 
          sort(p3dVector.begin(), p3dVector.end(),Point3D::compareXdsc);
        }
      } else if (sortCriteria == "y-ordinate") {
        if (sortOrder == "ASC") {
          sort(p3dVector.begin(), p3dVector.end(),Point3D::compareYasc);
        } else {  // Descending order 
          sort(p3dVector.begin(), p3dVector.end(),Point3D::compareYdsc);
        }
      } else if (sortCriteria == "z-ordinate") {
        if (sortOrder == "ASC") {
          sort(p3dVector.begin(), p3dVector.end(),Point3D::compareZasc);
        } else { // Descending order 
          sort(p3dVector.begin(), p3dVector.end(),Point3D::compareZdsc);
        }
      } else if (sortCriteria == "Dist.Fr Origin") {
        if (sortOrder == "ASC") {
          sort(p3dVector.begin(), p3dVector.end(),Point3D::compareDistAsc);
        } else { // Descending order 
          sort(p3dVector.begin(), p3dVector.end(),Point3D::compareDistDsc);
        }
      }
      
      oss << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6)
          << right << "Z"
          << "    Dist. Fr Origin" << endl
          << "- - - - - - - - - - - - - - - - - - -" << endl;
      for (auto& point3d : p3dVector) {
        oss << point3d << endl;
      }

      // Store the formatted string in the output vector
      outputVector.push_back(oss.str());

      writeVectorToFile(outputVector, outputFilename);
      cout << endl;
      cout << p3dCounter << " records output succesfully!\n" << endl;
    }
  } else if (filterCriteria == "Line2D") {
    if (l2dVector.empty()) {
      cout << "[No available Line2D records to output]" << endl;
      return;
    } else {
      if (sortCriteria == "Pt.1") {
        if (sortOrder == "ASC") {
          sort(l2dVector.begin(), l2dVector.end(),Line2D::compareP1asc);
        } else { // Descending order 
          sort(l2dVector.begin(), l2dVector.end(),Line2D::compareP1dsc);
        }
      } else if (sortCriteria == "Pt.2") {
        if (sortOrder == "ASC") {
          sort(l2dVector.begin(), l2dVector.end(),Line2D::compareP2asc);
        } else { // Descending order 
          sort(l2dVector.begin(), l2dVector.end(),Line2D::compareP2dsc);
        }
      } else if (sortCriteria == "Length") {
        if (sortOrder == "ASC") {
          sort(l2dVector.begin(), l2dVector.end(),Line2D::compareLengthAsc);
        } else { // Descending order 
          sort(l2dVector.begin(), l2dVector.end(),Line2D::compareLengthDsc);
        }
      }
      oss << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(9)
          << right << "P2-X" << setw(6) << right << "P2-Y"
          << "    Length" << endl
          << "- - - - - - - - - - - - - - - - - - -" << endl;
      for (auto& line2d : l2dVector) {
        oss << line2d << endl;
      }

      // Store the formatted string in the output vector
      outputVector.push_back(oss.str());

      writeVectorToFile(outputVector, outputFilename);
      cout << endl;
      cout << l2dCounter << " records output succesfully!\n" << endl;
    }

  } else if (filterCriteria == "Line3D") {
    if (l3dVector.empty()) {
      cout << "[No available Line3D records to output]" << endl;
      return;
    } else {
      if (sortCriteria == "Pt.1") {
        if (sortOrder == "ASC") { 
          sort(l3dVector.begin(), l3dVector.end(),Line3D::compareP1asc);
        } else { // Descending order 
          sort(l3dVector.begin(), l3dVector.end(),Line3D::compareP1dsc);
        }
      } else if (sortCriteria == "Pt.2") {
        if (sortOrder == "ASC") {
          sort(l3dVector.begin(), l3dVector.end(),Line3D::compareP2asc);
        } else { // Descending order 
          sort(l3dVector.begin(), l3dVector.end(),Line3D::compareP2dsc);
        }
      } else if (sortCriteria == "Length") {
        if (sortOrder == "ASC") {
          sort(l3dVector.begin(), l3dVector.end(),Line3D::compareLengthAsc);
        } else { // Descending order 
          sort(l3dVector.begin(), l3dVector.end(),Line3D::compareLengthDsc);
        }
      }
    }
    oss << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(6)
        << right << "P1-Z" << setw(9) << right << "P2-X" << setw(6) << right
        << "P2-Y" << setw(6) << right << "P2-Z"
        << "    Length" << endl
        << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    for (auto& line3d : l3dVector) {
      oss << line3d << endl;
    }

    // Store the formatted string in the output vector
    outputVector.push_back(oss.str());

    writeVectorToFile(outputVector, outputFilename);
    cout << endl;
    cout << l3dCounter << " records output succesfully!\n" << endl;
  }
  cout << "Going back to main menu ...\n";
}

void writeVectorToFile(vector<string>& outputVector, string& filename) {
  ofstream outFile(filename); // Filestream for filename
  if (outFile.is_open()) {
    for (const string& line : outputVector) {
      outFile << line;      // Writes string from oss in vector to file
    }
    outFile.close();        // Close filestream file
    outputVector.clear();   // Clears outputVector for fresh output
  } else {
    cerr << "Error opening file for writing" << endl;
  }
}
