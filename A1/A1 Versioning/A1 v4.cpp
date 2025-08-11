#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

// Global variables
string ** array2D = 0;
bool isArrayInitialized = false; // Track if the array is initialized
int x;
int y;
int counter = 0; // Initialize counter
string value;
string cLine;

// Define the CityData struct before using it
struct CityData {
    int xCord;
    int yCord;
    int size;
    string name;
};

// Function Prototype
vector < string > tokenizeString(string input, string delimiter);
vector<CityData> cities; // Vector to store CityData structs
CityData parseCityData(const string& input);
void setValueAt(int row, int col, const int& value);
void updateArrayWithCityData(const vector<CityData>& cities);
void readAFile(string& filename , int counter);
void displayMenu();
void readConfig();
void init2DArray(int, int);
void populate2DArray(int, int);
void display2DArray(int, int);
void safelyDeallocateMemory(int, int);
void displayMapData();

int main() { //main

  bool bEnd = false; // Control loop termination

  // Main Menu Display
  while (!bEnd) {
    displayMenu();
    

    // Get user input
    int userInput;
    cin >> userInput;

    switch (userInput) {
    case 1: {
      readConfig();
      cin.ignore(numeric_limits < streamsize > ::max(), '\n'); // Removes remaining text in buffer
      init2DArray(x, y); // Initialize the 2D array with dimensions x and y
      populate2DArray(x, y); // Populate the 2D array with default values

      // Call updateArrayWithCityData with the cities vector
      updateArrayWithCityData(cities); // Pass the vector of CityData objects to the function

      isArrayInitialized = true; // Mark array as initialized

      break;
    }
    case 2: {
      cout << "----------------------------------------------" << endl;
      cout << "[Displaying city map]" << endl;
      cout << "----------------------------------------------" << endl;

      display2DArray(x, y);
      safelyDeallocateMemory(x, y); // Deallocate memory
      isArrayInitialized = false;
      cin.ignore(numeric_limits < streamsize > ::max(), '\n'); // Removes remaining text in buffer

      break;
    }
    case 3: {
      cout << "[Displaying cloud coverage map (cloudiness index)]" << endl;
      // Add your code for displaying the cloud coverage map (cloudiness index)
      break;
    }
    case 4: {
      cout << "[Displaying cloud coverage map (LHM symbols)]" << endl;
      // Add your code for displaying the cloud coverage map (LHM symbols)
      break;
    }
    case 5: {
      cout << "[Displaying atmospheric pressure map (pressure index)]" << endl;
      // Add your code for displaying the atmospheric pressure map (pressure index)
      break;
    }
    case 6: {
      cout << "[Displaying atmospheric pressure map (LHM symbols)]" << endl;
      // Add your code for displaying the atmospheric pressure map (LHM symbols)
      break;
    }
    case 7: {
      cout << "[Showing weather forecast summary report]" << endl;
      // Add your code for showing the weather forecast summary report
      break;
    }
    case 8: {
      cout << "Thank you for using Weather Information Processing System, have a nice day!" << endl;
      bEnd = true; // Set to true to end the loop
      break;
    }
    default: {
      cout << "[Invalid input]\n" << endl; // Outputs this if invalid input is keyed
      cin.clear(); // Clear input stream state
      cin.ignore(numeric_limits < streamsize > ::max(), '\n'); // Removes remaining text in buffer
      safelyDeallocateMemory(x, y);
      break;
    }
    }
  }

  return 0;
} //end of main 

void displayMenu() { // Menu Display 
  cout << endl;
  cout << "Student ID\t: 550" << endl;
  cout << "Student Name\t: Unknown" << endl;
  cout << "-----------------------------------------------" << endl;
  cout << "Welcome to Weather Information Processing System!\n" << endl;
  cout << "1) Read in and process a configuration file" << endl;
  cout << "2) Display city map" << endl;
  cout << "3) Display cloud coverage map (cloudiness index)" << endl;
  cout << "4) Display cloud coverage map (LHM symbols)" << endl;
  cout << "5) Display atmospheric pressure map (pressure index)" << endl;
  cout << "6) Display atmospheric pressure map (LHM symbols)" << endl;
  cout << "7) Show weather forecast summary report" << endl;
  cout << "8) Quit\n" << endl;
  cout << "Please enter your choice: ";
}

vector < string > tokenizeString(string input, string delimiter) {
  size_t pos = 0;
  string token;
  vector < string > result;

  while ((pos = input.find(delimiter)) != string::npos) {
    token = input.substr(0, pos);
    result.push_back(token);
    input.erase(0, pos + delimiter.length());
  }
  result.push_back(input);

  return result;
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

    // No default values needed
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            array2D[i][j] = ""; // Initialize with empty strings
        }
    }
}

// You might not need populate2DArray if it adds unnecessary default values
void populate2DArray(int col, int row) {
    // You can remove this or modify it if not needed
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
    for (int i =(row-1); i >=0 ; i--) {
        cout << setw(2) << i << " # ";
        for(int j=0; j<col ; j++) {
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


    fstream inputFile1(inputFilename.c_str(), fstream::in); // Second file stream to find all the lines that end in .txt for value mapping
    while (getline(inputFile1, cLine)) {
        //cout << cLine << endl;
        size_t pos = cLine.find(".txt");

        if (pos != string::npos) {
            readAFile(cLine, counter);
            counter++;
            cout << counter << " " << cLine << endl;
        }
    }

    cout << endl;
    cout << "All records successfully stored. Going back to main menu" << endl << endl;
}

void readAFile(string& filename, int counter) {
    string aLine;

    ifstream inputFile(filename.c_str()); // Use the filename parameter
    if (!inputFile) {
        cerr << "Failed to open " << filename << endl;
        return;
    }
    if (counter == 0){
    while (getline(inputFile, aLine)) 
        {   
               if (!aLine.empty()) {
                    cout << " inside citylocation.txt" << endl;
                    CityData city = parseCityData(aLine);
                    // Check if the city coordinates are within bounds
                    if (city.xCord >= 0 && city.xCord < x && city.yCord >= 0 && city.yCord < y) {
                        cities.push_back(city); // Store each CityData struct in the vector
                    } else {
                        cerr << "Error: City coordinates (" << city.xCord << ", " << city.yCord << ") are out of bounds." << endl;
                    }
                }
        }
    }else if (counter == 1){
                cout << " inside cloudcover.txt" << endl;
    }
    else if (counter == 2){
                cout << " inside pressure.txt" << endl;
    }else{
        inputFile.close(); // Close the file after reading
        // Use the new function to update the array
        updateArrayWithCityData(cities);
    }

    
    
    
    
}

void setValueAt(int row, int col, const int& value) {
    if (row >= 0 && row < y && col >= 0 && col < x) {
        if (array2D) {
            array2D[row][col] = to_string(value); // Convert integer to string
            cout << "Setting coordinates at (" << row << ", " << col << "), Size:" << value << endl; // Debug output
            cout << endl;
        } else {
            cerr << "Error: Array is not initialized." << endl;
        }
    } else {
        cerr << "Error: Index out of bounds when setting value at (" << row << ", " << col << ")." << endl;
    }
}


void updateArrayWithCityData(const vector<CityData>& cities) {
    for (size_t i = 0; i < cities.size(); ++i) {
        const CityData& city = cities[i];
        
        // Debug output
        cout << "--------------------" << endl;
        cout << "Processing city data for index " << i << endl;
        cout << "x: " << city.xCord << endl;
        cout << "y: " << city.yCord << endl;
        cout << "Size: " << city.size << endl;
        cout << "City Name: " << city.name << endl;

        // Set value in the 2D array
        setValueAt(city.yCord, city.xCord, city.size);
    }
}

void displayMapData()
{
    cout << "----------------------------------------------" << endl;
    cout << "[Displaying city map]" << endl;
    cout << "----------------------------------------------" << endl;

    
}