/*
all 4
*/
#include <vector>     // For vector container
#include <fstream>    // For file operations
#include <iostream>   // For standard input and output
#include <limits>     // For numeric limits
#include <string>     // For string operations
#include <algorithm>  // For find function
#include <iomanip>    // For io manipulation

using namespace std;

#include "Point2D.h"
#include "Line2D.h"
#include "Point3D.h"
#include "Line3D.h"

// Vector Records
vector<string> allRecords;
vector<string> uniqueRecords;
vector<string> outputVector;

// 4 class containers
vector<Point2D> p2dVector;
vector<Line2D> l2dVector;
vector<Point3D> p3dVector;
vector<Line3D> l3dVector;

// Respective record counter for outputting (calculated during processing)
int p2dCounter = 0;
int p3dCounter = 0;
int l2dCounter = 0;
int l3dCounter = 0;
    

vector<string> tokenizeString (string input, string delimiter);
string trimLeft(const string& str);
string trimRight(const string& str);
string trim(const string& str);
void displayMenu(string filterCriteria, string sortCriteria, string sortOrder);
void waitForEnter();
void readInput();
void processingUniqueRecords();

void filterMenu(int& filter_index);
void sortMenu(int filter_index , int& sort_index);
void orderMenu(int& order_index);
void sortAndDisplay(vector<Point2D>& p2dVector, string sortCriteria, string sortOrder);

void writeVectorToFile(vector<string>& outputVector, string& filename);


// Arrays for filtering, sorting criteria, and sorting order
string filter_mode[] = {"Point2D", "Point3D", "Line2D", "Line3D"};
string sort_mode[] = {"x-ordinate", "y-ordinate", "z-ordinate", "Dist.Fr Origin", "Pt.1", "Pt.2", "Length"};
string order_mode[] = {"ASC", "DSC"};


// Default selection for global variable
    int filter_index = 0;  // Defaults to "Point2D"
    int sort_index = 0;    // Defaults to "x-ordinate"
    int order_index = 0;   // Defaults to "ASC"

void filterMenu(int& filter_index)
{
  if (allRecords.empty()){
    cout << endl;
    cout << "[No Records to filter, records is empty]" << endl;
    return;  // Exits the function early
  }

  char choice;
 
  cout << "[ Specifying filtering criteria " << "(current : " << filter_mode[filter_index] << ") ]\n\n";
  cout << "\ta)\tPoint2D records" << endl;
  cout << "\tb)\tPoint3D records" << endl;
  cout << "\tc)\tLine2D records" << endl;
  cout << "\td)\tLine3D records\n" << endl;

  cout << "\tPlease enter your criteria (a - d): ";
  cin >> choice;

  switch(choice)
  {
    case 'a':
    //Filter criteria to Point2D records
   	filter_index = 0;
	sort_index = 0;   
    break;
    case 'b':
    //Filter criteria to Point3D records
    filter_index = 1;
	sort_index = 0;   
    break;
    case 'c':
    //Filter criteria to Line2D records
    filter_index = 2;
	sort_index = 4;
    break;
    case 'd':
    //Filter criteria to Line3D records
    filter_index = 3;
	sort_index = 4;
    break;
    default :
    filter_index = 0;
	sort_index = 0;   
    cin.clear();
    break;
  }
  cout << "\tFilter criteria successfully set to " << "'" << filter_mode[filter_index] << "'!\n"; 

}

void sortMenu(int filter_index , int& sort_index)
{
  if (allRecords.empty()){
    cout << endl;
    cout << "[No Records to filter, records is empty]" << endl;
    return;  // Exits the function early
  }

  char choice;
  if (filter_mode[filter_index] == "Point2D"){
	cout << "[ Specifying sorting criteria " << "(current : " << sort_mode[sort_index] << ") ]\n\n";
	cout << "\ta)\tX ordinate value" << endl;
	cout << "\tb)\tY ordinate value" << endl;
	cout << "\tc)\tDist. Fr Origin value\n" << endl;

  	cout << "\tPlease enter your criteria (a - c): ";
	cin >> choice;

	switch(choice)
	{
		case 'a':
		sort_index = 0; // x
		break;
		case 'b':
		sort_index = 1; // y
		break;
		case 'c':
		sort_index = 3; // Dist Fr Origin
		break;
		default :
		sort_index = 0;
		cin.clear();
		break;
	}
  }else if (filter_mode[filter_index] == "Point3D"){
	cout << "[ Specifying sorting criteria " << "(current : " << sort_mode[sort_index] << ") ]\n\n";
	cout << "\ta)\tX ordinate value" << endl;
	cout << "\tb)\tY ordinate value" << endl;
	cout << "\tc)\tZ ordinate value" << endl;
	cout << "\td)\tDist. Fr Origin value\n" << endl;

  	cout << "\tPlease enter your criteria (a - d): ";
	cin >> choice;

	switch(choice)
	{
		case 'a':
		sort_index = 0; // x
		break;
		case 'b':
		sort_index = 1; // y
		break;
		case 'c':
		sort_index = 2; // z
		break;
		case 'd':
		sort_index = 3; // Dist Fr Origin
		break;
		default :
		sort_index = 0;
		cin.clear();
		break;
	}
  }else if (filter_mode[filter_index] == "Line2D"){
	cout << "[ Specifying sorting criteria " << "(current : " << sort_mode[sort_index] << ") ]\n\n";
	cout << "\ta)\tPt. 1's (x, y) values" << endl;
	cout << "\tb)\tPt. 2's (x, y) values" << endl;
	cout << "\tc)\tLength value\n" << endl;

  	cout << "\tPlease enter your criteria (a - c): ";
	cin >> choice;

	switch(choice)
	{
		case 'a':
		sort_index = 4;
		break;
		case 'b':
		sort_index = 5;
		break;
		case 'c':
		sort_index = 6;
		break;
		default :
		sort_index = 4;
		cin.clear();
		break;
	}
  }else if (filter_mode[filter_index] == "Line3D"){
	cout << "[ Specifying sorting criteria " << "(current : " << sort_mode[sort_index] << ") ]\n\n";
	cout << "\ta)\tPt. 1's (x, y) values" << endl;
	cout << "\tb)\tPt. 2's (x, y) values" << endl;
	cout << "\tc)\tLength value\n" << endl;

  	cout << "\tPlease enter your criteria (a - c): ";
	cin >> choice;

	switch(choice)
	{
		case 'a':
		sort_index = 4;
		break;
		case 'b':
		sort_index = 5;
		break;
		case 'c':
		sort_index = 6;
		break;
		default :
		sort_index = 4;
		cin.clear();
		break;
	}
  }
  cout << "\tSort criteria successfully set to " << "'" << sort_mode[sort_index] << "'!\n"; 

}

void orderMenu(int& order_index)
{
  if (allRecords.empty()){
    cout << endl;
    cout << "[No Records to filter, records is empty]" << endl;
    return;  // Exits the function early
  }

  char choice;
 
  cout << "[ Specifying sorting order " << "(current : " << order_mode[order_index] << ") ]\n\n";
  cout << "\ta)\tASC (Ascending order)" << endl;
  cout << "\tb)\tDSC (Descending order)\n" << endl;

  cout << "\tPlease enter your criteria (a - b): ";
  cin >> choice;

  switch(choice)
  {
    case 'a':
    //Select sort order to Ascending
   	order_index = 0;
    break;
    case 'b':
     //Select sort order to Descending
    order_index = 1;
    break;
    default :
    order_index = 0;
    cin.clear();
    break;
  }
  cout << "\tSorting order successfully set to " << "'" <<  order_mode[order_index] << "'!\n"; 

}

void sortAndDisplay(vector<Point2D>& p2dVector, string sortCriteria, string sortOrder) {
    if (p2dVector.empty()) {
        cout << "[No Point2D records to sort, list is empty]" << endl;
        return;
    }

    if (sortCriteria == "x-ordinate") {
        if (sortOrder == "ASC") {
            sort(p2dVector.begin(), p2dVector.end(), [](Point2D& lhs, Point2D& rhs) {
                return lhs.getX() < rhs.getX();
            });
        } else {
            sort(p2dVector.begin(), p2dVector.end(), [](Point2D& lhs, Point2D& rhs) {
                return lhs.getX() > rhs.getX();
            });
        }
    } else if (sortCriteria == "y-ordinate") {
        if (sortOrder == "ASC") {
            sort(p2dVector.begin(), p2dVector.end(), [](Point2D& lhs, Point2D& rhs) {
                return lhs.getY() < rhs.getY();
            });
        } else {
            sort(p2dVector.begin(), p2dVector.end(), [](Point2D& lhs, Point2D& rhs) {
                return lhs.getY() > rhs.getY();
            });
        }
    } else if (sortCriteria == "Dist.Fr Origin") {
        if (sortOrder == "ASC") {
            sort(p2dVector.begin(), p2dVector.end(), [](Point2D& lhs, Point2D& rhs) {
                return lhs.getScalarValue() < rhs.getScalarValue();
            });
        } else {
            sort(p2dVector.begin(), p2dVector.end(), [](Point2D& lhs, Point2D& rhs) {
                return lhs.getScalarValue() > rhs.getScalarValue();
            });
        }
    }

    // Print the sorted vector
    cout << "[ Viewing Data ... ]" << endl;
    cout << "filtering criteria : " << filter_mode[filter_index] << endl;
    cout << "sorting criteria : " << sort_mode[sort_index] << endl;
    cout << "sorting order : " << order_mode[order_index] << endl;
	cout << endl;
	cout << setw(5) << right << "X" 
         << setw(6) << right << "Y"
         << "    Dist. Fr Origin" << endl
         << "- - - - - - - - - - - - - - - - - - -" << endl;
    for (auto& point2d : p2dVector) {
        cout << point2d << endl;
    }
}

void sortAndDisplay(vector<Point3D>& p3dVector, string sortCriteria, string sortOrder) {
    if (p3dVector.empty()) {
        cout << "[No Point3D records to sort, list is empty]" << endl;
        return;
    }

    if (sortCriteria == "x-ordinate") {
        if (sortOrder == "ASC") {
            sort(p3dVector.begin(), p3dVector.end(), [](Point3D& lhs, Point3D& rhs) {
                return lhs.getX() < rhs.getX();
            });
        } else {
            sort(p3dVector.begin(), p3dVector.end(), [](Point3D& lhs, Point3D& rhs) {
                return lhs.getX() > rhs.getX();
            });
        }
    }else if (sortCriteria == "y-ordinate") {
        if (sortOrder == "ASC") {
            sort(p3dVector.begin(), p3dVector.end(), [](Point3D& lhs, Point3D& rhs) {
                return lhs.getY() < rhs.getY();
            });
        } else {
            sort(p3dVector.begin(), p3dVector.end(), [](Point3D& lhs, Point3D& rhs) {
                return lhs.getY() > rhs.getY();
            });
        }
    }else if (sortCriteria == "z-ordinate") {
        if (sortOrder == "ASC") {
            sort(p3dVector.begin(), p3dVector.end(), [](Point3D& lhs, Point3D& rhs) {
                return lhs.getZ() < rhs.getZ();
            });
        } else {
            sort(p3dVector.begin(), p3dVector.end(), [](Point3D& lhs, Point3D& rhs) {
                return lhs.getZ() < rhs.getZ();
            });
        }
    } else if (sortCriteria == "Dist.Fr Origin") {
        if (sortOrder == "ASC") {
            sort(p3dVector.begin(), p3dVector.end(), [](Point3D& lhs, Point3D& rhs) {
                return lhs.getScalarValue() < rhs.getScalarValue();
            });
        } else {
            sort(p3dVector.begin(), p3dVector.end(), [](Point3D& lhs, Point3D& rhs) {
                return lhs.getScalarValue() > rhs.getScalarValue();
            });
        }
    }

    // Print the sorted vector
    cout << "[ Viewing Data ... ]" << endl;
    cout << "filtering criteria : " << filter_mode[filter_index] << endl;
    cout << "sorting criteria : " << sort_mode[sort_index] << endl;
    cout << "sorting order : " << order_mode[order_index] << endl;
	cout << endl;
	cout << setw(5) << right << "X" 
         << setw(6) << right << "Y" 
         << setw(6) << right << "Z"
         <<"    Dist. Fr Origin" << endl
         << "- - - - - - - - - - - - - - - - - - -" << endl;
    for (auto& point3d : p3dVector) {
        cout << point3d << endl;
    }
}

void sortAndDisplay(vector<Line2D>& l2dVector, string sortCriteria, string sortOrder) {
    if (l2dVector.empty()) {
        cout << "[No Line2D records to sort, list is empty]" << endl;
        return;
    }

    if (sortCriteria == "Pt.1") {
        if (sortOrder == "ASC") {
            sort(l2dVector.begin(), l2dVector.end(), [](Line2D& lhs, Line2D& rhs) {
                return lhs.getPt1() < rhs.getPt1();
            });
        } else {
            sort(l2dVector.begin(), l2dVector.end(), [](Line2D& lhs, Line2D& rhs) {
                return lhs.getPt1() > rhs.getPt1();
            });
        }
    }else if (sortCriteria == "Pt.2") {
        if (sortOrder == "ASC") {
            sort(l2dVector.begin(), l2dVector.end(), [](Line2D& lhs, Line2D& rhs) {
                return lhs.getPt2() < rhs.getPt2();
            });
        } else {
            sort(l2dVector.begin(), l2dVector.end(), [](Line2D& lhs, Line2D& rhs) {
                return lhs.getPt2() < rhs.getPt2();
            });
        }
    }else if (sortCriteria == "Length") {
        if (sortOrder == "ASC") {
            sort(l2dVector.begin(), l2dVector.end(), [](Line2D& lhs, Line2D& rhs) {
                return lhs.getScalarValue() < rhs.getScalarValue();
            });
        } else {
            sort(l2dVector.begin(), l2dVector.end(), [](Line2D& lhs, Line2D& rhs) {
                return lhs.getScalarValue() > rhs.getScalarValue();
            });
        }
    }

    // Print the sorted vector
    cout << "[ Viewing Data ... ]" << endl;
    cout << "filtering criteria : " << filter_mode[filter_index] << endl;
    cout << "sorting criteria : " << sort_mode[sort_index] << endl;
    cout << "sorting order : " << order_mode[order_index] << endl;
    cout << endl;
    cout << setw(5) << right << "P1-X" 
         << setw(6) << right << "P1-Y" 
         << setw(9) << right << "P2-X" 
         << setw(6) << right << "P2-Y"
         << "    Length" << endl
         << "- - - - - - - - - - - - - - - - - - -" << endl;
    for (auto& line2d : l2dVector) {
		cout << line2d << endl;
    }
}

void sortAndDisplay(vector<Line3D>& l3dVector, string sortCriteria, string sortOrder) {
    if (l3dVector.empty()) {
        cout << "[No Line3D records to sort, list is empty]" << endl;
        return;
    }

    if (sortCriteria == "Pt.1") {
        if (sortOrder == "ASC") {
            sort(l3dVector.begin(), l3dVector.end(), [](Line3D& lhs, Line3D& rhs) {
                return lhs.getPt1() < rhs.getPt1();
            });
        } else {
            sort(l3dVector.begin(), l3dVector.end(), [](Line3D& lhs, Line3D& rhs) {
                return lhs.getPt1() > rhs.getPt1();
            });
        }
    }else if (sortCriteria == "Pt.2") {
        if (sortOrder == "ASC") {
            sort(l3dVector.begin(), l3dVector.end(), [](Line3D& lhs, Line3D& rhs) {
                return lhs.getPt2() < rhs.getPt2();
            });
        } else {
            sort(l3dVector.begin(), l3dVector.end(), [](Line3D& lhs, Line3D& rhs) {
                return lhs.getPt2() < rhs.getPt2();
            });
        }
    }else if (sortCriteria == "Length") {
        if (sortOrder == "ASC") {
            sort(l3dVector.begin(), l3dVector.end(), [](Line3D& lhs, Line3D& rhs) {
                return lhs.getScalarValue() < rhs.getScalarValue();
            });
        } else {
            sort(l3dVector.begin(), l3dVector.end(), [](Line3D& lhs, Line3D& rhs) {
                return lhs.getScalarValue() > rhs.getScalarValue();
            });
        }
    }
    

    // Print the sorted vector
    cout << "[ Viewing Data ... ]" << endl;
    cout << "filtering criteria : " << filter_mode[filter_index] << endl;
    cout << "sorting criteria : " << sort_mode[sort_index] << endl;
    cout << "sorting order : " << order_mode[order_index] << endl;
	cout << endl;
    cout << setw(5) << right << "P1-X" 
         << setw(6) << right << "P1-Y" 
         << setw(6) << right << "P1-Z" 
         << setw(9) << right << "P2-X" 
         << setw(6) << right << "P2-Y" 
         << setw(6) << right << "P2-Z"
         << "    Length" << endl
         << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    for (auto& line3d : l3dVector) {
		cout << line3d << endl;
    }
}

void storeOutputToVector(const vector<Point2D>& p2dVector, vector<string>& outputVector)
{   
    string outputFilename;
    cout << "Please enter filename :";
    cin >> outputFilename;
    outputFilename += ".txt";

    // Create a string stream to format the output
    ostringstream oss;
    
    // Add header
    oss << setw(5) << right << "X" 
         << setw(6) << right << "Y"
         << "    Dist. Fr Origin" << endl
         << "- - - - - - - - - - - - - - - - - - -" << endl;
    
    // Add each point to the output vector
    for (auto& point2d : p2dVector) {
        // Assuming the `<<` operator is overloaded to format Point2D objects
        oss << point2d << endl;
    }
    
    // Store the formatted string in the output vector
    outputVector.push_back(oss.str());

    writeVectorToFile(outputVector, outputFilename);
    cout << endl;
    cout << p2dCounter << " records output succesfully!\n" << endl;

    cout << "Going back to main menu ...\n";

}

void storeOutputToVector(const vector<Point3D>& p3dVector, vector<string>& outputVector)
{   
    string outputFilename;
    cout << "Please enter filename :";
    cin >> outputFilename;
    outputFilename += ".txt";

    // Create a string stream to format the output
    ostringstream oss;
    
    // Add header
    oss << setw(5) << right << "X" 
         << setw(6) << right << "Y" 
         << setw(6) << right << "Z"
         <<"    Dist. Fr Origin" << endl
         << "- - - - - - - - - - - - - - - - - - -" << endl;
    
    // Add each point to the output vector
    for (auto& point3d : p3dVector) {
        // Assuming the `<<` operator is overloaded to format Point2D objects
        oss << point3d << endl;
    }
    
    // Store the formatted string in the output vector
    outputVector.push_back(oss.str());

    writeVectorToFile(outputVector, outputFilename);
    cout << endl;
    cout << p3dCounter << " records output succesfully!\n" << endl;

    cout << "Going back to main menu ...\n";

}

void storeOutputToVector(const vector<Line2D>& l2dVector, vector<string>& outputVector)
{   
    string outputFilename;
    cout << "Please enter filename :";
    cin >> outputFilename;
    outputFilename += ".txt";

    // Create a string stream to format the output
    ostringstream oss;
    
    // Add header
    oss  << setw(5) << right << "P1-X" 
         << setw(6) << right << "P1-Y" 
         << setw(9) << right << "P2-X" 
         << setw(6) << right << "P2-Y"
         << "    Length" << endl
         << "- - - - - - - - - - - - - - - - - - -" << endl;
    
    // Add each point to the output vector
    for (auto& line2d : l2dVector) {
        // Assuming the `<<` operator is overloaded to format Point2D objects
        oss << line2d << endl;
    }
    
    // Store the formatted string in the output vector
    outputVector.push_back(oss.str());

    writeVectorToFile(outputVector, outputFilename);
    cout << endl;
    cout << l2dCounter << " records output succesfully!\n" << endl;

    cout << "Going back to main menu ...\n";

}

void storeOutputToVector(const vector<Line3D>& l3dVector, vector<string>& outputVector)
{   
    string outputFilename;
    cout << "Please enter filename :";
    cin >> outputFilename;
    outputFilename += ".txt";

    // Create a string stream to format the output
    ostringstream oss;
    
    // Add header
    oss  << setw(5) << right << "P1-X" 
         << setw(6) << right << "P1-Y" 
         << setw(6) << right << "P1-Z" 
         << setw(9) << right << "P2-X" 
         << setw(6) << right << "P2-Y" 
         << setw(6) << right << "P2-Z"
         << "    Length" << endl
         << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    
    // Add each point to the output vector
    for (auto& line3d : l3dVector) {
        // Assuming the `<<` operator is overloaded to format Point2D objects
        oss << line3d << endl;
    }
    
    // Store the formatted string in the output vector
    outputVector.push_back(oss.str());

    writeVectorToFile(outputVector, outputFilename);
    cout << endl;
    cout << l3dCounter << " records output succesfully!\n" << endl;

    cout << "Going back to main menu ...\n";

}

void writeVectorToFile(vector<string>& outputVector, string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const string& line : outputVector) {
            outFile << line;
        }
        outFile.close();
        outputVector.clear();
    } else {
        cerr << "Error opening file for writing" << endl;
    }
}



int main ()
{

  int choice;
  bool bEnd = false; //Boolean Flag to end program
  

  while(!bEnd){

     displayMenu(filter_mode[filter_index], sort_mode[sort_index], order_mode[order_index]);
     cin >> choice;
     cout <<endl;

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
		if (filter_mode[filter_index] == "Point2D"){
			sortAndDisplay(p2dVector, sort_mode[sort_index] , order_mode[order_index]);
		}else if (filter_mode[filter_index] == "Point3D"){
			sortAndDisplay(p3dVector, sort_mode[sort_index] , order_mode[order_index]);
		}else if (filter_mode[filter_index] == "Line2D"){
			sortAndDisplay(l2dVector, sort_mode[sort_index] , order_mode[order_index]);
		}else if (filter_mode[filter_index] == "Line3D"){
			sortAndDisplay(l3dVector, sort_mode[sort_index] , order_mode[order_index]);
		}
        waitForEnter();
        break;
      case 6:
        // Store data
        if (filter_mode[filter_index] == "Point2D"){
			storeOutputToVector(p2dVector, outputVector);
		}else if (filter_mode[filter_index] == "Point3D"){
			storeOutputToVector(p3dVector, outputVector);
		}else if (filter_mode[filter_index] == "Line2D"){
			storeOutputToVector(l2dVector, outputVector);
		}else if (filter_mode[filter_index] == "Line3D"){
			storeOutputToVector(l3dVector, outputVector);
		}
		
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
    string temps6;
	string temps7;
	vector<string> tempStr;
	string aLine;

	int counter = 0;

	cout << "Please enter filename: ";
	//cin >> inputFilename;
	inputFilename += "messy1Edited.txt"; //Appending .txt to fileName for enhanced user experience

	//cout << inputFilename << endl; //output only when key in input
	//cout << "\n" << inputFilename; //output for debug

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

					counter ++;
                    p2dCounter++;

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

					counter ++;
                    l2dCounter ++;

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

					counter ++;
                    p3dCounter ++;

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

					counter ++;
                    l3dCounter ++;

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
  cout << "2)\tSpecify filtering criteria (current: " << filter_mode[filter_index] << ")" << endl;
  cout << "3)\tSpecify sorting criteria   (current: " << sort_mode[sort_index] << ")" << endl;
  cout << "4)\tSpecify sorting order      (current: " << order_mode[order_index] << ")" << endl;
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