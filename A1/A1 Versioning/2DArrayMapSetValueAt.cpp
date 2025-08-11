#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

string** array2D = 0;
bool isArrayInitialized = false; // Track if the array is initialized

void init2DArray(int, int);
void populate2DArray(int, int);
void display2DArray(int, int);
void safelyDeallocateMemory(int, int);
void readConfig();
vector<string> tokenizeString (string input, string delimiter);
void setValueAt(int, int, const string&);

int x = 0;
int y = 0;

int main() {
    readConfig();
    if (x > 0 && y > 0) {
        init2DArray(x, y);
        populate2DArray(x, y);
        isArrayInitialized = true; // Mark array as initialized
        
    /* //SC , MC , BC
        // Set specific values
        setValueAt(1, 1, "3");
        setValueAt(1, 2, "3");
        setValueAt(1, 3, "3");
        setValueAt(2, 1, "3");
        setValueAt(2, 2, "3");
        setValueAt(2, 3, "3");
        setValueAt(2, 7, "2");
        setValueAt(2, 8, "2");
        setValueAt(3, 1, "3");
        setValueAt(3, 2, "3");
        setValueAt(3, 3, "3");
        setValueAt(3, 7, "3");
        setValueAt(3, 8, "3");
        setValueAt(7, 7, "1");
    */
    
        setValueAt(2, 8, "1");
        setValueAt(2, 2, "2");
        setValueAt(2, 3, "2");
        setValueAt(3, 2, "2");
        setValueAt(3, 3, "2");
        setValueAt(6, 8, "3");
        setValueAt(6, 9, "3");
        setValueAt(6, 10, "3");
        setValueAt(7, 8, "3");
        setValueAt(7, 9, "3");
        setValueAt(7, 10, "3");
        setValueAt(8, 8, "3");
        setValueAt(8, 9, "3");
        setValueAt(8, 10, "3");
        setValueAt(7, 2, "4");
		

        display2DArray(x, y);
        safelyDeallocateMemory(x, y);
        isArrayInitialized = false; // Mark array as deallocated
    } else {
        cout << "Invalid dimensions for the array." << endl;
    }

    cout << endl;
    return 0;
}

/* O.G Array init
void init2DArray(int col, int row) {
    array2D = new string*[row];
    for (int i = 0; i < row; i++) {
        array2D[i] = new string[col];
    }
}
*/

void init2DArray(int col, int row) {
  array2D = new string * [row];
  for (int i = 0; i < row; i++) {
    array2D[i] = new string[col];
  }

  // No default values needed
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      array2D[i][j] = ""; // Initialize with empty strings
    }
  }
}

void populate2DArray(int col, int row) {
    for (int i = (row - 1); i >= 0; i--) {
        for (int j = 0; j < col; j++) {
            ostringstream oss;
            oss << j + 1 << i + 1;
            //array2D[i][j] = oss.str();
        }
    }
}

void setValueAt(int row, int col, const string& value) {
    if (row >= 0 && row < y && col >= 0 && col < x) {
        array2D[row][col] = value;
    } else {
        cerr << "Error: Index out of bounds when setting value at (" << row << ", " << col << ")." << endl;
    }
}

void display2DArray(int col, int row) {
  if (!isArrayInitialized) {
    cout << endl;
    cout << "<----Array not initialized. Cannot display---->" << endl;
    return;
  }

  // Print top border
  cout << setw(5) << " # ";
  for (int i = 0; i < col; ++i) {
    cout << " # ";
  }
  cout << setw(3) << " # ";
  cout << endl;

  // Print row borders and values
  for (int i = (row - 1); i >= 0; i--) {
    cout << setw(2) << i << " # ";
    for (int j = 0; j < col; j++) {
      cout << setw(2) << (array2D[i][j].empty() ? "." : array2D[i][j]) << " ";
    }
    cout << " # " << endl;
  }

  // Print bottom border
  cout << setw(5) << " # ";
  for (int i = 0; i < col; ++i) {
    cout << " # ";
  }
  cout << setw(3) << " # ";
  cout << endl;

  // Print Horizontal header
  cout << "     ";
  for (int i = 0; i < col; ++i) {
    cout << setw(2) << i << " ";
  }
  cout << endl;
}

void safelyDeallocateMemory(int col, int row) {
    if (array2D) {
        for (int i = 0; i < row; i++) {
            delete[] array2D[i];
        }
        delete[] array2D;
        array2D = nullptr;
    }
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

void readConfig() {
    cout << endl;
    cout << "----------------------------------------------" << endl;
    cout << "[Read in and process a configuration file]\n";
    cout << "----------------------------------------------" << endl;
    cout << endl;
    cout << "Please enter the configuration file name (e.g., config): ";

    string inputFilename;
    cin >> inputFilename;
    inputFilename += ".txt";

    ifstream inputFile(inputFilename.c_str());
    if (!inputFile) {
        cerr << "Failed to open " << inputFilename << endl;
        return;
    }

    string aLine;
    vector<string> tempStr;
    vector<string> tempStr2;
    string temps;

    cout << endl;
    while (getline(inputFile, aLine)) {
        cout << aLine << endl;

        tempStr = tokenizeString(aLine, "=");
        if (tempStr.size() < 2) continue;

        if (tempStr[0] == "GridX_IdxRange") {
            temps = tempStr[1];
            tempStr2 = tokenizeString(temps, "-");
            x = stoi(tempStr2[1]) + 1;
            cout << "Reading in x variables: " << tempStr[1] << "... done!" << endl;
        } else if (tempStr[0] == "GridY_IdxRange") {
            temps = tempStr[1];
            tempStr2 = tokenizeString(temps, "-");
            y = stoi(tempStr2[1]) + 1;
            cout << "Reading in y variables: " << tempStr[1] << "... done!" << endl;
        }
    }
}


