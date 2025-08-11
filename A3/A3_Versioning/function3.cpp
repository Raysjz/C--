/*
Doing Point 3D Vector
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

#include "Point3D.h"

// Vector Records
vector<string> allRecords;
vector<string> uniqueRecords;

//1 containers for each class
vector<Point3D> p3dVector;
    

vector<string> tokenizeString (string input, string delimiter);
string trimLeft(const string& str);
string trimRight(const string& str);
string trim(const string& str);
void readInput();
void displayPoint3D();


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

			if (type == "Point3D") {
                if (classToken.size() == 4) {
                    string x1 = trim(classToken[1]);
                    string y1 = trim(classToken[2]);
					string z1 = trim(classToken[3]);

                    // Convert x and y to integers
                    int x = stoi(x1);
                    int y = stoi(y1);
					int z = stoi(z1);

                    // Create a point3D object and add it to the points vector
                    //p3dVector.emplace_back(x, y);
					p3dVector.push_back(Point3D(x,y,z));
                    
                    cout << "\nProcessing point3D with x: " << x << ", y: " << y << ", z: " << z << endl;
                } else {
                    cout << "Incorrect number of fields for point3D record" << endl;
                }
            } else {
                cout << "Unknown record type: " << type << endl;
            }
        }
    }

    /*
	// For debugging purposes, print points
    cout << "\nPoints:\n";
    for (auto& point3d : p3dVector) {
        cout << "Point(" << point3d.getX() << ", " << point3d.getY() << ") - Distance from Origin: " << point3d.getScalarValue() << endl;
    }
	*/
}



int main ()
{ 	
	readInput();
	processingUniqueRecords();
	displayPoint3D();

	
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
	vector<string> tempStr;
	string aLine;

	int counter = 0;

	cout << "Please enter filename: ";
	//cin >> inputFilename;
	inputFilename += "ownMessy.txt"; //Appending .txt to fileName for enhanced user experience

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

			if(tempStr[0] == "Point3D"){
				cout << "After removing ',' "<< endl;	
				if(tempStr.size() == 4){
					temps  = tempStr[0];
					temps2 = tempStr[1];
					temps3 = tempStr[2];
					temps4 = tempStr[3];

					temps2 = temps2.substr(2,temps2.length());
					temps3 = trim(temps3);
					temps4 = trim(temps4.substr(0,temps4.length()-1));

					cout << "After trimming and removing []" << endl;
					cout << "temps: "<< temps << endl;
					cout << "temps2: "<< temps2 << endl;
					cout << "temps3: "<< temps3 << endl;
					cout << "temps4: "<< temps4 << endl;

					counter ++;

					// Concatenate the values into a single string and push to the records vector
                    string record = temps + "," + temps2 + "," + temps3 + "," + temps4;
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

void displayPoint3D(){
	cout << endl;
	cout << setw(5) << right << "X" << setw(6) << right << "Y"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;
    for (auto& point3d : p3dVector) {
        cout << "[\t" << point3d.getX() << ",\t" << point3d.getY() << ",\t" << point3d.getZ() << "]\t" << point3d.getScalarValue() << endl;
    }
}