#include <iostream>
#include <vector>
#include <fstream>    // For file operations
#include <iostream>   // For standard input and output
#include <limits>     // For numeric limits
#include <string>     // For string operations
#include <algorithm>  // For find function

using namespace std;

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

vector<string> allRecords;
vector<string> uniqueRecords;


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
	string temps8;
	vector<string> tempStr;
	string aLine;

	int counter = 0;

	cout << "Please enter filename: ";
	//cin >> inputFilename;
	inputFilename += "messy.txt"; //Appending .txt to fileName for enhanced user experience

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
			cout << aLine << endl;

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
			}                     
			else if(tempStr[0] == "Line2D"){
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
			else if(tempStr[0] == "Point3D"){
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
			else if(tempStr[0] == "Line3D"){
				cout << "After removing ',' "<< endl;	
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

					cout << "After trimming and removing []" << endl;
					cout << "temps: "<< temps << endl;
					cout << "temps2: "<< temps2 << endl;
					cout << "temps3: "<< temps3 << endl;
					cout << "temps4: "<< temps4 << endl;
					cout << "temps5: "<< temps5 << endl;
					cout << "temps6: "<< temps6 << endl;
					cout << "temps7: "<< temps7 << endl;

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

	/*
  // For debugging purposes, print allRecords
    cout << "\nAll Records:\n";
    for (string record : allRecords) {
        cout << record << endl;
    }
	cout << endl;
	*/
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
						string x = classToken[1];
						string y = classToken[2];
						// Process Point2D record
						cout << "Processing Point2D with x: " << x << ", y: " << y << endl;
					}
				} else if (type == "Line2D") {
					if (classToken.size() == 5) {
						string x1 = classToken[1];
						string y1 = classToken[2];
						string x2 = classToken[3];
						string y2 = classToken[4];
						// Process Line2D record
						cout << "Processing Line2D with points (" << x1 << ", " << y1 << ") and ("
							<< x2 << ", " << y2 << ")" << endl;
					}
				} else if (type == "Point3D") {
					if (classToken.size() == 4) {
						string x = classToken[1];
						string y = classToken[2];
						string z = classToken[3];
						// Process Point3D record
						cout << "Processing Point3D with x: " << x << ", y: " << y << ", z: " << z << endl;
					}
				} else if (type == "Line3D") {
					if (classToken.size() == 7) {
						string x1 = classToken[1];
						string y1 = classToken[2];
						string z1 = classToken[3];
						string x2 = classToken[4];
						string y2 = classToken[5];
						string z2 = classToken[6];
						// Process Line3D record
						cout << "Processing Line3D with points (" << x1 << ", " << y1 << ", " << z1 << ") and ("
							<< x2 << ", " << y2 << ", " << z2 << ")" << endl;
					}
				} else {
					cout << "Unknown record type: " << type << endl;
				}
        }
    }

}					


int main ()
{ 	
	readInput();
	processingUniqueRecords();

	
	return (0);
}



