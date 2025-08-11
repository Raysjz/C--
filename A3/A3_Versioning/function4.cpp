/*
Doing Point 2D Line
*/
#include <iostream>
#include <vector>
#include <fstream>    // For file operations
#include <iostream>   // For standard input and output
#include <limits>     // For numeric limits
#include <string>     // For string operations
#include <algorithm>  // For find function
#include <iomanip>    // For io manipulation

using namespace std;

#include "Point2D.h"
#include "Line2D.h"

// Vector Records
vector<string> allRecords;
vector<string> uniqueRecords;

//2 containers for each class
vector<Point2D> p2dVector;
vector<Line2D> l2dVector;
    

vector<string> tokenizeString (string input, string delimiter);
string trimLeft(const string& str);
string trimRight(const string& str);
string trim(const string& str);
void readInput();
void displayPoint2D();
void displayLine2D();


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
			cout << endl;

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
                    
                    cout << "\nProcessing Point2D with x: " << x1 << ", y: " << y1 << endl;
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
						cout << "Processing Line2D with points (" << x1 << ", " << y1 << ") and ("
							<< x2 << ", " << y2 << ")" << endl;
					}
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





int main ()
{ 	
	readInput();
	processingUniqueRecords();
	displayPoint2D();
	displayLine2D();

	
	return (0);
}


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
	vector<string> tempStr;
	string aLine;

	int counter = 0;

	cout << "Please enter filename: ";
	//cin >> inputFilename;
	inputFilename += "messy1.txt"; //Appending .txt to fileName for enhanced user experience

	//cout << inputFilename << endl; //output only when key in input
	cout << "\n" << inputFilename; //output for debug

	ifstream inputFile(inputFilename.c_str());
	if (!inputFile) {
		cerr << "Failed to open " << inputFilename << endl;
		return;
	}

    cout << endl;
    while (getline (inputFile, aLine))
	{
		
		if (!aLine.empty()) {
			//cout << aLine << endl;

			tempStr = tokenizeString(aLine, ",");
			cout << endl;
			temps = tempStr[0];

			if(tempStr[0] == "Point2D"){
				cout << "After removing ',' "<< endl;	
				if(tempStr.size() == 3){
					temps  = tempStr[0];
					temps2 = tempStr[1];
					temps3 = tempStr[2];

					temps2 = temps2.substr(2,temps2.length());
					temps3 = trim(temps3.substr(0,temps3.length()-1));

					cout << "After trimming and removing []" << endl;
					cout << "temps: "<< temps << endl;
					cout << "temps2: "<< temps2 << endl;
					cout << "temps3: "<< temps3 << endl;
					counter ++;


					// Concatenate the values into a single string and push to the records vector
                    string record = temps + "," + temps2 + "," + temps3;
                    allRecords.push_back(record);
				}
			}else if(tempStr[0] == "Line2D"){
				cout << "After removing ',' "<< endl;	
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

					cout << "After trimming and removing []" << endl;
					cout << "temps: "<< temps << endl;
					cout << "temps2: "<< temps2 << endl;
					cout << "temps3: "<< temps3 << endl;
					cout << "temps4: "<< temps4 << endl;
					cout << "temps5: "<< temps5 << endl;

					counter ++;

					// Concatenate the values into a single string and push to the records vector
                    string record = temps + "," + temps2 + "," + temps3 + "," + temps4 + "," + temps5 ;
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