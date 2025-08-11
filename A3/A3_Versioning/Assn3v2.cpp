#include<iostream>   // For standard input and output
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

//--------------------------------------------------------------------------
//                          Function Prototype
//--------------------------------------------------------------------------
void displayMenu();
void waitForEnter();
void readInput();
void processingUniqueRecords();
void displayPoint2D();
void displayLine2D();
void displayPoint3D();
void displayLine3D();
void viewDisplay();
void storeData();

// Function to tokenize a string based on a delimiter
vector<string> tokenizeString(string input, string delimiter);

// Trim function to remove spacing
string trimLeft(const string& str);
string trimRight(const string& str);
string trim(const string& str);

// Vectors to store collections of data
vector<string> allRecords;
vector<string> uniqueRecords;
vector<Point2D> p2dVector;
vector<Line2D> l2dVector;
vector<Point3D> p3dVector;
vector<Line3D> l3dVector;

using namespace std;  // Use the standard namespace to avoid prefixing std::

//Global variables
const string twoD = "Point2D";
const string threeD = "Point3D";
const string linetwoD = "Line2D";
const string linethreeD = "Line3D";
string sortCrit = twoD;
string sortOrd;

void filterMenu()
{
  if (allRecords.empty()){
    cout << endl;
    cout << "[No Records to filter, records is empty]" << endl;
    return;  // Exits the function early
  }

  char choice;
 
  cout << "[ Specifying filtering criteria " << "(current : " << sortCrit << ") ]\n\n";
  cout << "\ta)\tPoint2D records" << endl;
  cout << "\tb)\tPoint3D records" << endl;
  cout << "\tc)\tLine2D records" << endl;
  cout << "\td)\tLine3D records\n" << endl;

  cout << "\tPlease enter your criteria (a - d): ";
  cin >> choice;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  switch(choice)
  {
    case 'a':
    //Filter criteria to Point2D records
    sortCrit = twoD;
    break;
    case 'b':
    //Filter criteria to Point3D records
    sortCrit = threeD;
    break;
    case 'c':
    sortCrit = linetwoD;
    break;
    case 'd':
    sortCrit = linethreeD;
    break;
    default :
    sortCrit = twoD;
    cin.clear();
    break;
  }
  cout << "\tFilter criteria successfully set to " << "'" << sortCrit << "'!\n"; 

}

void viewDisplay()
{
  if (allRecords.empty()){
    cout << endl;
    cout << "[No Records to display, records is empty]" << endl;
    return;  // Exits the function early
  }

  cout << "[ Viewing Data ... ]" << endl;
  cout << "filtering criteria : " << sortCrit << endl;
  cout << "sorting criteria : " << "Length" << endl;
  cout << "sorting order : " << "DSC" << endl;

  if(sortCrit == twoD){
    displayPoint2D();
  }else if (sortCrit == threeD){
     displayPoint3D();
  }else if (sortCrit == linetwoD){
    displayLine2D();
  }else if (sortCrit == linethreeD){
    displayLine3D();
  }
}

void storeData(){
  if (allRecords.empty()){
    cout << endl;
    cout << "[No Records to output, records is empty]" << endl;
    return;  // Exits the function early
  }
  
}

int main() {  //------------Start of Main--------------------------------------------------------

  int choice;
  bool bEnd = false; //Flag to end program
  

  while(!bEnd){

     displayMenu();
     cin >> choice;

    switch (choice) {
      case 1:
        // Read in Data
        readInput();
        processingUniqueRecords();
        waitForEnter();
        break;
      case 2:
        // Specify filtering criteria
        filterMenu();
        break;
      case 3:
        // Specify sorting criteria
        break;
      case 4:
        // Specify sorting order
        break;
      case 5:
        // View data
        viewDisplay();
        waitForEnter();
        break;
      case 6:
        // Store data
        storeData();
        waitForEnter();
        break;
      case 7:
        // Quit the program
        bEnd = true;
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
} //-------------------------------------End of Main------------------------------------------------



//------------------------------------Start of Menu ------------------------------------------------

// Displays Menu
void displayMenu() {
  // Menu Display
  cout << endl;
  cout << "Student ID\t: abc" << endl;
  cout << "Student Name\t: 3344" << endl;
  cout << "-----------------------------------------------" << endl;
  cout << "Welcome to Assn3 program!\n" << endl;
  cout << "1)\tRead in data" << endl;
  cout << "2)\tSpecify filtering criteria (current: " << sortCrit << ")" << endl;
  cout << "3)\tSpecify sorting criteria   (current: " << "x-ordinate"<< ")" << endl;
  cout << "4)\tSpecify sorting order      (current: " << "ASC" << ")" << endl;
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

//----------------------End of menu -----------------------------------------------------------------

vector<string> tokenizeString (string input, string delimiter)
{
	size_t pos = 0;
	string token;
	vector<string> result;

	while ((pos = input.find(delimiter)) != string::npos) 
	{
    	token = input.substr(0, pos);
    	result.push_back (token);
		input.erase(0, pos + delimiter.length());
	}

	result.push_back (input);

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

// Trim both leading and trailing spaces
string trim(const string& str) {
    return trimRight(trimLeft(str));
}

void readInput()
{
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

	int counter = 0;

  cout << endl;
	cout << "Please enter filename: ";
	cin >> inputFilename;
	inputFilename += ".txt"; //Appending .txt to fileName for enhanced user experience
  
	//cout << inputFilename << endl; //debug filename

	ifstream inputFile(inputFilename.c_str());
	if (!inputFile) {
		cerr << "Failed to open " << inputFilename << endl;
		return;
	}

    //cout << endl;
    while (getline (inputFile, aLine))
	{
		
		if (!aLine.empty()) {
			//cout << aLine << endl;

			tempStr = tokenizeString(aLine, ",");
			//cout << endl;
			temps = tempStr[0];

			if(tempStr[0] == "Point2D"){
				if(tempStr.size() == 3){
					temps  = tempStr[0];
					temps2 = tempStr[1];
					temps3 = tempStr[2];

					temps2 = temps2.substr(2,temps2.length());
					temps3 = trim(temps3.substr(0,temps3.length()-1));

					//cout << "temps: "<< temps << endl;
					//cout << "temps2: "<< temps2 << endl;
					//cout << "temps3: "<< temps3 << endl;
					counter ++;


					// Concatenate the values into a single string and push to the records vector
                    string record = temps + "," + temps2 + "," + temps3;
                    allRecords.push_back(record);
				}
			}else if(tempStr[0] == "Line2D"){
				if(tempStr.size() == 5){
					temps  = tempStr[0];
					temps2 = tempStr[1];
					temps3 = tempStr[2];
					temps4 = tempStr[3];
					temps5 = tempStr[4];

					temps2 = temps2.substr(2,temps2.length());
					temps3 = trim(temps3.substr(0,temps3.length()-1));
					temps4 = temps4.substr(2,temps4.length());
					temps5 = trim(temps5.substr(0,temps5.length()-1));

					//cout << "temps: "<< temps << endl;
					//cout << "temps2: "<< temps2 << endl;
					//cout << "temps3: "<< temps3 << endl;
					//cout << "temps4: "<< temps4 << endl;
					//cout << "temps5: "<< temps5 << endl;

					counter ++;

					// Concatenate the values into a single string and push to the records vector
                    string record = temps + "," + temps2 + "," + temps3 + "," + temps4 + "," + temps5 ;
                    allRecords.push_back(record);
				}
			}else if(tempStr[0] == "Point3D"){
				if(tempStr.size() == 4){
					temps  = tempStr[0];
					temps2 = tempStr[1];
					temps3 = tempStr[2];
					temps4 = tempStr[3];

					temps2 = temps2.substr(2,temps2.length());
					temps3 = trim(temps3);
					temps4 = trim(temps4.substr(0,temps4.length()-1));

					//cout << "temps: "<< temps << endl;
					//cout << "temps2: "<< temps2 << endl;
					//cout << "temps3: "<< temps3 << endl;
					//cout << "temps4: "<< temps4 << endl;

					counter ++;

					// Concatenate the values into a single string and push to the records vector
                    string record = temps + "," + temps2 + "," + temps3 + "," + temps4;
                    allRecords.push_back(record);
				}
			}else if(tempStr[0] == "Line3D"){
				if(tempStr.size() == 7){
					temps  = tempStr[0];
					temps2 = tempStr[1];
					temps3 = tempStr[2];
					temps4 = tempStr[3];
					temps5 = tempStr[4];
					temps6 = tempStr[5];
					temps7 = tempStr[6];

					temps2 = temps2.substr(2,temps2.length());
					temps3 = trim(temps3);
					temps4 = trim(temps4.substr(0,temps4.length()-1));
					temps5 = temps5.substr(2,temps5.length());
					temps6 = trim(temps6);
					temps7 = trim(temps7.substr(0,temps7.length()-1));

					//cout << "temps: "<< temps << endl;
					//cout << "temps2: "<< temps2 << endl;
					//cout << "temps3: "<< temps3 << endl;
					//cout << "temps4: "<< temps4 << endl;
					//cout << "temps5: "<< temps5 << endl;
					//cout << "temps6: "<< temps6 << endl;
					//cout << "temps7: "<< temps7 << endl;

					counter ++;

					// Concatenate the values into a single string and push to the records vector
                    string record = temps + "," + temps2 + "," + temps3 + "," + temps4 + "," + temps5 + "," + temps6 + "," + temps7;
                    allRecords.push_back(record);
				}
			}                 
			
		}
	}
  cout << endl;

  cout << counter << " records read in successfully!" << endl << endl;

  cout << "Going back to main menu ...\n" << endl;
}

void processingUniqueRecords()
{
	uniqueRecords.clear(); // Clear uniqueRecords to start fresh

	//Iterate through all records
	for (string record : allRecords ){
        // Check if the record is already in uniqueRecords
        if (find(uniqueRecords.begin(), uniqueRecords.end(), record) == uniqueRecords.end()) {
            // Record is not found in uniqueRecords, so add it
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

	//Iterate through unique records
	for (string records : uniqueRecords ){

		vector<string> classToken = tokenizeString(records, ","); // Use record for tokenization

        if (classToken.size() > 0) {
            string type = trim(classToken[0]); // Trim spaces from the type string
			//cout << endl;

            // Print the extracted type for debugging
            //cout << "Extracted type: '" << type << "'" << endl;

			if (type == "Point2D") {
					if (classToken.size() == 3) {
					string x1 = trim(classToken[1]);
                    string y1 = trim(classToken[2]);

                    // Convert x and y to integers
                    int v1 = stoi(x1);
                    int v2 = stoi(y1);

                    // Create a Point2D object and add it to the points vector
                    //p2dVector.emplace_back(x, y);
					p2dVector.push_back(Point2D(v1,v2));
                    
                    //cout << "\nProcessing Point2D with x: " << x1 << ", y: " << y1 << endl;
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

						l2dVector.push_back(Line2D(Point2D(v1,v2), Point2D(v3,v4)));

						// Process Line2D record
						//cout << "Processing Line2D with points (" << x1 << ", " << y1 << ") and ("<< x2 << ", " << y2 << ")" << endl;
					}
				}else if (type == "Point3D") {
                    if (classToken.size() == 4) {
                        string x1 = trim(classToken[1]);
                        string y1 = trim(classToken[2]);
                        string z1 = trim(classToken[3]);

                        // Convert x and y to integers
                        int v1 = stoi(x1);
                        int v2 = stoi(y1);
                        int v3 = stoi(z1);

                        // Create a point3D object and add it to the points vector
                        //p3dVector.emplace_back(x, y);
                        p3dVector.push_back(Point3D(v1,v2,v3));
                        
                        //cout << "\nProcessing point3D with x: " << x1 << ", y: " << y1 << ", z: " << z1 << endl;
                    }
        	    } else if (type == "Line3D") {
					if (classToken.size() == 7) {
						string x1 = classToken[1];
						string y1 = classToken[2];
						string z1 = classToken[3];
						string x2 = classToken[4];
						string y2 = classToken[5];
						string z2 = classToken[6];

						 // Convert x and y to integers
						int v1 = stoi(x1);
						int v2 = stoi(y1);
						int v3 = stoi(z1);
						int v4 = stoi(x2);
						int v5 = stoi(y2);
						int v6 = stoi(z2);

						// Create a point3D object and add it to the points vector
						//p3dVector.emplace_back(x, y);
						l3dVector.push_back(Line3D(Point3D(v1,v2,v3),Point3D(v4,v5,v6)));


						// Process Line3D record
						//cout << "Processing Line3D with points (" << x1 << ", " << y1 << ", " << z1 << ") and ("<< x2 << ", " << y2 << ", " << z2 << ")" << endl;
					}
				} else {
					cout << "Unknown record type: " << type << endl;
				}

        }
    }

    /*
	// For debugging purposes, print points
    cout << "\nPoints:\n";
    for (auto& point2d : p2dVector) {
        cout << "Point(" << point2d.getX() << ", " << point2d.getY() << ") - Distance from Origin: " << point2d.getScalarValue() << endl;
    }
	*/
}

void displayPoint2D(){
	cout << endl;
	cout << setw(5) << right << "X" << setw(6) << right << "Y"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;
    for (auto& point2d : p2dVector) {
        cout << "[\t" << point2d.getX() << ",\t" << point2d.getY() << "]\t" << point2d.getScalarValue() << endl;
    }
}

void displayLine2D() {
    if (l2dVector.empty()) {
        cout << "No Line2D objects to display." << endl;
        return;
    }
    
    cout << endl;
    cout << setw(10) << right << "P1-X" << setw(10) << right << "P1-Y"
         << setw(10) << right << "P2-X" << setw(10) << right << "P2-Y"
         << setw(20) << right << "Length" << endl
         << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;

    for (auto& line : l2dVector) {
        Point2D pt1 = line.getPt1();
        Point2D pt2 = line.getPt2();
        cout << setw(10) << right << pt1.getX()
             << setw(10) << right << pt1.getY()
             << setw(10) << right << pt2.getX()
             << setw(10) << right << pt2.getY()
             << setw(20) << right << fixed << setprecision(3) << line.getScalarValue() << endl;
    }
}

void displayPoint3D(){
	cout << endl;
	cout << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;
    for (auto& point3d : p3dVector) {
        cout << "[\t" << point3d.getX() << ",\t" << point3d.getY() << ",\t" << point3d.getZ() << "]\t" << point3d.getScalarValue() << endl;
    }
}

void displayLine3D() {
    cout << endl;
    cout << setw(10) << right << "Pt1 X" << setw(10) << right << "Pt1 Y" << setw(10) << right << "Pt1 Z"
         << setw(10) << right << "Pt2 X" << setw(10) << right << "Pt2 Y" << setw(10) << right << "Pt2 Z"
         << setw(15) << right << "Length" << endl
         << "- - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;

    for (auto& line : l3dVector) { // Assuming l3dVector is a vector of Line3D objects
        Point3D pt1 = line.getPt1();
        Point3D pt2 = line.getPt2();
        cout << setw(10) << right << pt1.getX()
             << setw(10) << right << pt1.getY()
             << setw(10) << right << pt1.getZ()
             << setw(10) << right << pt2.getX()
             << setw(10) << right << pt2.getY()
             << setw(10) << right << pt2.getZ()
             << setw(15) << right << fixed << setprecision(3) << line.getScalarValue() << endl;
    }
}


