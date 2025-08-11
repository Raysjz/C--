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


// Define the CityData struct before using it
struct CityData {
    int xCord;
    int yCord;
    int size;
    string name;
};

vector<CityData> cities; // Vector to store CityData structs
CityData parseCityData(const string& input);

int x = 0;
int y = 0;
int counter = 0; // Initialize counter
string value;

void init2DArray(int, int);
void populate2DArray(int, int);
void display2DArray(int, int);
void safelyDeallocateMemory(int, int);
void readConfig();
vector<string> tokenizeString(string input, string delimiter);
void setValueAt(int row, int col, const int& value);
void readAFile(const string&, int);
void updateArrayWithCityData(const vector<CityData>& cities);

int main() { 
    readConfig(); // This will read the configuration file and initialize x, y, etc.

    init2DArray(x, y); // Initialize the 2D array with dimensions x and y
    populate2DArray(x, y); // Populate the 2D array with default values

    // Call updateArrayWithCityData with the cities vector
    updateArrayWithCityData(cities); // Pass the vector of CityData objects to the function

    isArrayInitialized = true; // Mark array as initialized

    display2DArray(x, y); // Display the contents of the 2D array
    safelyDeallocateMemory(x, y); // Deallocate memory

    cout << endl;
    return 0;
}


CityData parseCityData(const string& input) {
    CityData data;
    vector<string> parts = tokenizeString(input, "-");

    if (parts.size() == 3) {
        string coordinates = parts[0];
        string value = parts[1];
        string city_name = parts[2];

        // Remove brackets from coordinates
        coordinates = coordinates.substr(1, coordinates.size() - 2);
        vector<string> coordinate_parts = tokenizeString(coordinates, ",");

        data.xCord = stoi(coordinate_parts[0]);
        data.yCord = stoi(coordinate_parts[1]);
        data.size = stoi(value);
        data.name = city_name;
    } else {
        cerr << "Unexpected format." << endl;
    }

    return data;
}

void init2DArray(int col, int row) {
    array2D = new string*[row];
    for (int i = 0; i < row; i++) {
        array2D[i] = new string[col];
    }

    cout << "Array initialized to " << row << " x " << col << endl; // Debugging output
}

void populate2DArray(int col, int row) {
    for (int i = (row - 1); i >= 0; i--) {
        for (int j = 0; j < col; j++) {
            //ostringstream oss;
           // oss << "x" << j + 1 << "y" << i + 1; // Use labels or default values
           // array2D[i][j] = oss.str();
        }
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
    for (int i = 0; i < row; ++i) {
        cout << setw(2) << (row - i - 1) << " # ";
        for (int j = 0; j < col; ++j) {
            cout << setw(2) << " . ";
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

    return result;
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

    string cLine;
    fstream inputFile1(inputFilename.c_str(), fstream::in); // Second file stream to find all the lines that end in .txt for value mapping
    while (getline(inputFile1, cLine)) {
        cout << cLine << endl;
        size_t pos = cLine.find(".txt");

        if (pos != string::npos) {
            readAFile(cLine, counter); // Function that reads the filename from within a file and stores it into our 3D array
            counter++;
        }
    }

    cout << endl;
    cout << "All records successfully stored. Going back to main menu" << endl << endl;
}

void readAFile(const string& filename, int counter) {
    string aLine;

    ifstream inputFile(filename.c_str()); // Use the filename parameter
    if (!inputFile) {
        cerr << "Failed to open " << filename << endl;
        return;
    }

    while (getline(inputFile, aLine)) {
        if (!aLine.empty()) {
            CityData city = parseCityData(aLine);
            // Check if the city coordinates are within bounds
            if (city.xCord >= 0 && city.xCord < x && city.yCord >= 0 && city.yCord < y) {
                cities.push_back(city); // Store each CityData struct in the vector
            } else {
                cerr << "Error: City coordinates (" << city.xCord << ", " << city.yCord << ") are out of bounds." << endl;
            }
        }
    }

    inputFile.close(); // Close the file after reading

    // Use the new function to update the array
    updateArrayWithCityData(cities);
}

void setValueAt(int row, int col, const string& value) {
    if (row >= 0 && row < y && col >= 0 && col < x) {
        if (array2D ==0) {
            cout << "Setting value at (" << row << ", " << col << "): " << value << endl; // Debug output
            array2D[row][col] = value; // Set the value in the 2D array
        } else {
            cerr << "Error: Array is not initialized." << endl;
        }
    } else {
        cerr << "Error: Index out of bounds when setting value at (" << row << ", " << col << ")." << endl;
    }
}



void updateArrayWithCityData(const vector<CityData>& cities) {

    for (size_t i = 0; i < cities.size(); ++i) {
        const CityData& city = cities[i]; // Access each CityData object
        
        cout << "Processing city data for index " << i << endl;
        cout << "x: " << city.xCord << endl;
        cout << "y: " << city.yCord << endl;
        cout << "Size: " << city.size << endl;
        cout << "City Name: " << city.name << endl;
        cout << "--------------------" << endl;

        // Set value in the 2D array
        setValueAt(city.yCord, city.xCord, city.size);
    }
}

