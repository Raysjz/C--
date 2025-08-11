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
string city_Size;
int counter = 0; // Initialize counter
string cLine;

// Define the CityData struct before using it
struct CityData {
  int xCord;
  int yCord;
  int cSize;
  string name;
};

struct CloudData {
  int xCloud;
  int yCloud;
  int nextCloud;
};

struct PressureData {
  int xPressure;
  int yPressure;
  int nextPressure;
};

// Function Prototype & Misc
vector < string > tokenizeString(string input, string delimiter);
vector < CityData > cities; // Vector to store CityData structs
vector < CloudData > clouds;
vector < PressureData > pressures;
CityData parseCityData(const string & input);
CloudData parseCloudData(const string & input);
PressureData parsePressureData(const string & input);
void setValueAt(int row, int col,const int & value);
void setValueLMH(int row, int col,const string & valueStr);
void updateArrayWithCityData(const vector < CityData > & cities);
void updateArrayWithCloudIndexData(const vector < CloudData > & clouds);
void updateArrayWithCloudLMHData(const vector < CloudData > & clouds);
void updateArrayWithPressureData(const vector < PressureData > & pressures);
void updateArrayWithPressureLMHData(const vector < PressureData > & pressures);
void readAFile(string filename);
void displayMenu();
void readConfig();
void readAFile(string & , int);
void init2DArray(int, int);
void populate2DArray(int, int);
void display2DArray(int, int);
void safelyDeallocateMemory(int, int);

int main() { //main

  bool bEnd = false; // Control loop termination

  // Main Menu Display
  while (!bEnd) {
    bool bInit = false;
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
      isArrayInitialized = true; // Mark array as initialized

      break;
    }
    case 2: {
      cout << "----------------------------------------------" << endl;
      cout << "[Displaying city map]" << endl;
      cout << "----------------------------------------------" << endl;
      // Call updateArrayWithCityData with the cities vector
      updateArrayWithCityData(cities);  // Pass the vector of CityData objects to the function
      display2DArray(x, y);
      cin.ignore(numeric_limits < streamsize > ::max(), '\n'); // Removes remaining text in buffer

      break;
    }
    case 3: {
      cout << "----------------------------------------------" << endl;
      cout << "[Displaying cloud coverage map (cloudiness index)]" << endl;
      cout << "----------------------------------------------" << endl;
     updateArrayWithCloudIndexData(clouds);
     display2DArray(x, y);
     cin.ignore(numeric_limits < streamsize > ::max(), '\n'); // Removes remaining text in buffer

      break;
    }
    case 4: {
      cout << "----------------------------------------------" << endl;
      cout << "[Displaying cloud coverage map (LHM symbols)]" << endl;
      cout << "----------------------------------------------" << endl;
      updateArrayWithCloudLMHData(clouds);
      display2DArray(x, y);
      cin.ignore(numeric_limits < streamsize > ::max(), '\n'); // Removes remaining text in buffer

      break;
    }
    case 5: {
      cout << "----------------------------------------------" << endl;
      cout << "[Displaying atmospheric pressure map (pressure index)]" << endl;
      cout << "----------------------------------------------" << endl;
      updateArrayWithPressureData(pressures);
      display2DArray(x, y);
      cin.ignore(numeric_limits < streamsize > ::max(), '\n'); // Removes remaining text in buffer

      break;
    }
    case 6: {
      cout << "----------------------------------------------" << endl;
      cout << "[Displaying atmospheric pressure map (LHM symbols)]" << endl;
      cout << "----------------------------------------------" << endl;
      updateArrayWithPressureLMHData(pressures);
      display2DArray(x, y);
      cin.ignore(numeric_limits < streamsize > ::max(), '\n'); // Removes remaining text in buffer
      break;
    }
    case 7: {
      cout << "----------------------------------------------" << endl;
      cout << "[Showing weather forecast summary report]" << endl;
      cout << "----------------------------------------------" << endl;
      // Add your code for showing the weather forecast summary report
      break;
    }
    case 8: {
      cout << "Thank you for using Weather Information Processing System, have a nice day!" << endl;
      bEnd = true; // Set to true to end the loop
	  cin.ignore(numeric_limits < streamsize > ::max(), '\n'); // Removes remaining text in buffer
      safelyDeallocateMemory(x, y);
      break;
    }
    default: {
      cout << "[Invalid input]\n" << endl; // Outputs this if invalid input is keyed
      cin.clear(); // Clear input stream state
      cin.ignore(numeric_limits < streamsize > ::max(), '\n'); // Removes remaining text in buffer
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

void readConfig() {
  cout << endl;
  cout << "----------------------------------------------" << endl;
  cout << "[Read in and process a configuration file]\n";
  cout << "----------------------------------------------" << endl;
  cout << endl;
  cout << "Please enter the config filename: ";

  string inputFilename;
  cin >> inputFilename;
  inputFilename += ".txt"; //Appended .txt to lessen the hassle of typing .txt

  ifstream inputFile(inputFilename.c_str());
  if (!inputFile) {
    cerr << "Failed to open " << inputFilename << endl;
    return;
  }

  string aLine;
  vector < string > tempStr;
  vector < string > tempStr2;
  string temps;

  cout << endl;
  while (getline(inputFile, aLine)) {
    //cout << aLine << endl;

    tempStr = tokenizeString(aLine, "=");

    if (tempStr[0] == "GridX_IdxRange") {
      temps = tempStr[1];
      tempStr2 = tokenizeString(temps, "-");
      x = stoi(tempStr2[1]) + 1;
      cout << "Reading in GridX_IdxRange : " << tempStr[1] << "... done!" << endl;
    } else if (tempStr[0] == "GridY_IdxRange") {
      temps = tempStr[1];
      tempStr2 = tokenizeString(temps, "-");
      y = stoi(tempStr2[1]) + 1;
      cout << "Reading in GridY_IdxRange : " << tempStr[1] << "... done!" << endl;
    }
  }

  fstream inputFile1(inputFilename.c_str(), fstream::in); // Second file stream to find all the lines that end in .txt for value mapping
  cout << endl;
  cout << "Storing data from input file: " << endl;  
  while (getline(inputFile1, cLine)) {
    //cout << cLine << endl;
    size_t pos = cLine.find(".txt");

    if (pos != string::npos) {
      readAFile(cLine, counter);
      counter++;

      cout << cLine << "... done!" << endl;
    }
  }
  
  cout << endl;
  cout << "All records successfully stored. Going back to main menu" << endl << endl;
}

void readAFile(string & filename, int counter) {

  string aLine;

  ifstream inputFile(filename.c_str()); // Use the filename parameter
  if (!inputFile) {
    cerr << "Failed to open " << filename << endl;
    return;
  }
    
  if (counter == 0) {
    while (getline(inputFile, aLine)) {
      if (!aLine.empty()) {
        //cout << " inside citylocation.txt" << endl;
        CityData city = parseCityData(aLine);
        // Check if the city coordinates are within bounds
        if (city.xCord >= 0 && city.xCord < x && city.yCord >= 0 && city.yCord < y) {
          cities.push_back(city); // Store each CityData struct in the vector
        } else {
          cerr << "Error: City coordinates (" << city.xCord << ", " << city.yCord << ") are out of bounds." << endl;
        }
        
      }
    }
  } else if (counter == 1) {
    while (getline(inputFile, aLine)) {
      if (!aLine.empty()) {
        //cout << " inside cloudcover.txt" << endl;
        CloudData cloud = parseCloudData(aLine);
        // Check if the Cloud coordinates are within bounds
        if (cloud.xCloud >= 0 && cloud.xCloud < x && cloud.yCloud >= 0 && cloud.yCloud < y) {
          clouds.push_back(cloud); // Store each CityData struct in the vector
        } else {
          cerr << "Error: Cloud coordinates (" << cloud.xCloud << ", " << cloud.yCloud << ") are out of bounds." << endl;
        }
        
      }
    }
  } else if (counter == 2) {
    while (getline(inputFile, aLine)) {
      if (!aLine.empty()) {
        //cout << " inside pressure.txt" << endl;
        PressureData pressure = parsePressureData(aLine);
        // Check if the Cloud coordinates are within bounds
        if (pressure.xPressure >= 0 && pressure.xPressure < x && pressure.yPressure >= 0 && pressure.yPressure < y) {
          pressures.push_back(pressure); // Store each CityData struct in the vector
        } else {
          cerr << "Error: Pressure coordinates (" << pressure.xPressure << ", " << pressure.yPressure << ") are out of bounds." << endl;
        }
      }
    }
  } else {
    inputFile.close(); // Close the file after reading
  }

}

//--------------- Value ---------------------------------------

void setValueAt(int row, int col, const int & value) {
  if (row >= 0 && row < y && col >= 0 && col < x) {
    if (array2D) {
      array2D[row][col] = to_string(value); // Convert integer to string
      // cout << "Setting coordinates at (" << row << ", " << col << "), Value: " << value << endl; // Debug output
      cout << endl;
    } else {
      cerr << "Error: Array is not initialized." << endl;
    }
  } else {
    cerr << "Error: Index out of bounds when setting value at (" << row << ", " << col << ")." << endl;
  }
}

void setValueLMH(int row, int col,const string & valueStr) {
  if (row >= 0 && row < y && col >= 0 && col < x) {
    if (array2D) {
      array2D[row][col] = valueStr; 
     // cout << "Setting coordinates at (" << row << ", " << col << "), Value: " << valueStr << endl; // Debug output
      cout << endl;
    } else {
      cerr << "Error: Array is not initialized." << endl;
    }
  } else {
    cerr << "Error: Index out of bounds when setting value at (" << row << ", " << col << ")." << endl;
  }
}

//--------------- City ---------------------------------------
CityData parseCityData(const string & input) {
  CityData data;
  vector < string > parts = tokenizeString(input, "-");

  if (parts.size() == 3) {
    string coordinates = parts[0];
    string city_Size = parts[1];
    string city_Name = parts[2];

    // Remove brackets from coordinates
    coordinates = coordinates.substr(1, coordinates.size() - 2);
    vector < string > coordinate_parts = tokenizeString(coordinates, ",");

    data.xCord = stoi(coordinate_parts[0]);
    data.yCord = stoi(coordinate_parts[1]);
    data.cSize = stoi(city_Size);
    data.name = city_Name;
  } else {
    cerr << "Unexpected format in parseCityData." << endl;
  }
  return data;
}

void updateArrayWithCityData(const vector < CityData > & cities) {
  for (size_t i = 0; i < cities.size(); ++i) {
    const CityData & city = cities[i];

    // Debug output
   // cout << "--------------------" << endl;
   // cout << "Processing city data for index " << i << endl;
   // cout << "x: " << city.xCord << endl;
   // cout << "y: " << city.yCord << endl;
   // cout << "Size: " << city.cSize << endl;
   // cout << "City Name: " << city.name << endl;

    // Set value in the 2D array
    setValueAt(city.yCord, city.xCord, city.cSize);
  }
}

//---------------End of City ---------------------------------------

CloudData parseCloudData(const string & input) {
  CloudData data;
  vector < string > parts = tokenizeString(input, "-");


  if (parts.size() == 2) {
    string coordinates = parts[0];
    string nextDay = parts[1];

    // Debug output
    //cout << "Parsing coordinates: " << coordinates << endl;
    //cout << "Parsing nextDay: " << nextDay << endl;

    // Remove brackets from coordinates
    coordinates = coordinates.substr(1, coordinates.size() - 2);
    vector < string > coordinate_parts = tokenizeString(coordinates, ",");

    data.xCloud = stoi(coordinate_parts[0]);
    data.yCloud = stoi(coordinate_parts[1]);
    data.nextCloud = stoi(nextDay);
  } else {
    cerr << "Unexpected format in parseCloudData." << endl;
  }

  /*
        //Debug output
      if (coordinate_parts.size() == 2) {
          data.xCloud = stoi(coordinate_parts[0]);
          data.yCloud = stoi(coordinate_parts[1]);
          data.nextCloud = stoi(nextDay);

          // Debug output
          cout << "Parsed CloudData - xCloud: " << data.xCloud << ", yCloud: " << data.yCloud << ", nextCloud: " << data.nextCloud << endl;
      } else {
          cerr << "Error: Invalid coordinate format." << endl;
      }
  } else {
      cerr << "Unexpected format in parseCloudData. " << input << endl;
  }
    */

  return data;
}

void updateArrayWithCloudIndexData(const vector < CloudData > & clouds) {
  for (size_t i = 0; i < clouds.size(); ++i) {
    const CloudData & cloud = clouds[i];

    // Debug output
   // cout << "--------------------" << endl;
   // cout << "Processing Cloud data for index " << i << endl;
   // cout << "x: " << cloud.xCloud << endl;
   // cout << "y: " << cloud.yCloud << endl;
   // cout << "Next Day: " << cloud.nextCloud << endl;

    int cloudIndex;
    // Set value in the 2D array
    if (cloud.nextCloud >= 0 && cloud.nextCloud < 10) {
      cloudIndex = 0;
    } else if (cloud.nextCloud >= 10 && cloud.nextCloud < 20) {

      cloudIndex = 1;
    } else if (cloud.nextCloud >= 20 && cloud.nextCloud < 30) {

      cloudIndex = 2;
    } else if (cloud.nextCloud >= 30 && cloud.nextCloud < 40) {

      cloudIndex = 3;
    } else if (cloud.nextCloud >= 40 && cloud.nextCloud < 50) {

      cloudIndex = 4;
    } else if (cloud.nextCloud >= 50 && cloud.nextCloud < 60) {

      cloudIndex = 5;
    } else if (cloud.nextCloud >= 60 && cloud.nextCloud < 70) {

      cloudIndex = 6;
    } else if (cloud.nextCloud >= 70 && cloud.nextCloud < 80) {

      cloudIndex = 7;
    } else if (cloud.nextCloud >= 80 && cloud.nextCloud < 90) {

      cloudIndex = 8;
    } else if (cloud.nextCloud >= 90 && cloud.nextCloud < 100) {

      cloudIndex = 9;
    } else {
      // Handle unexpected values for nextCloud
      cloudIndex = -1; // Or another error value
    }

    // Only update if PressureIndex is valid
    if (cloudIndex != -1) {
      setValueAt(cloud.xCloud, cloud.yCloud, cloudIndex);
    } else {
      cerr << "Error: Cloud value (" << cloud.nextCloud << ") is out of bounds." << endl;
    }

  }
}

void updateArrayWithCloudLMHData(const vector<CloudData>& clouds) {
    const string L = "L";  // Low
    const string M = "M";  // Medium
    const string H = "H";  // High

    for (size_t i = 0; i < clouds.size(); ++i) {
        const CloudData& cloud = clouds[i];

        // Debug output
       // cout << "--------------------" << endl;
       // cout << "Processing Cloud data for index " << i << endl;
       // cout << "x: " << cloud.xCloud << endl;
      //  cout << "y: " << cloud.yCloud << endl;
      //  cout << "Next Day: " << cloud.nextCloud << endl;

        string cloudLMH;
        // Set value in the 2D array based on nextCloud
        if (cloud.nextCloud >= 0 && cloud.nextCloud < 35) {
            cloudLMH = L;
        } else if (cloud.nextCloud >= 35 && cloud.nextCloud < 65) {
            cloudLMH = M;
        } else if (cloud.nextCloud >= 65 && cloud.nextCloud < 100) {
            cloudLMH = H;
        } else {
            // Handle unexpected values for nextCloud
            cloudLMH = "-1"; // Or another error value
        }

        // Only update if cloudLMH is not an error value
        if (cloudLMH != "-1") {
            setValueLMH(cloud.xCloud, cloud.yCloud, cloudLMH);
        } else {
            cerr << "Error: Cloud value (" << cloud.nextCloud << ") is out of bounds." << endl;
        }
    }
}


//---------------End of Cloud ---------------------------------------

PressureData parsePressureData(const string & input) {
  PressureData data;
  vector < string > parts = tokenizeString(input, "-");

  if (parts.size() == 2) {
    string coordinates = parts[0];
    string nextDay = parts[1];

    // Debug output
    //cout << "Parsing coordinates: " << coordinates << endl;
    //cout << "Parsing nextDay: " << nextDay << endl;

    // Remove brackets from coordinates
    coordinates = coordinates.substr(1, coordinates.size() - 2);
    vector < string > coordinate_parts = tokenizeString(coordinates, ",");

    data.xPressure = stoi(coordinate_parts[0]);
    data.yPressure = stoi(coordinate_parts[1]);
    data.nextPressure = stoi(nextDay);
  } else {
    cerr << "Unexpected format in parsePressureData." << endl;
  }

  /*
      if (coordinate_parts.size() == 2) {
          data.xPressure = stoi(coordinate_parts[0]);
          data.yPressure = stoi(coordinate_parts[1]);
          data.nextPressure = stoi(nextDay);

          // Debug output
          cout << "Parsed PressureData - xPressure: " << data.xPressure << ", yPressure: " << data.yPressure << ", nextPressure: " << data.nextPressure << endl;
      } else {
          cerr << "Error: Invalid coordinate format." << endl;
      }
  } else {
      cerr << "Unexpected format in parsePressureData. " << input << endl;
  }*/

  return data;
}

void updateArrayWithPressureData(const vector < PressureData > & pressures) {
  for (size_t i = 0; i < pressures.size(); ++i) {
    const PressureData & pressure = pressures[i];

    // Debug output
    //cout << "--------------------" << endl;
    //cout << "Processing Pressure data for index " << i << endl;
    //cout << "x: " << pressure.xPressure << endl;
    //cout << "y: " << pressure.yPressure << endl;
   // cout << "Next Day: " << pressure.nextPressure << endl;

    int PressureIndex;
    // Set value in the 2D array based on nextPressure
    if (pressure.nextPressure >= 0 && pressure.nextPressure < 10) {
      PressureIndex = 0;
    } else if (pressure.nextPressure >= 10 && pressure.nextPressure < 20) {
      PressureIndex = 1;
    } else if (pressure.nextPressure >= 20 && pressure.nextPressure < 30) {
      PressureIndex = 2;
    } else if (pressure.nextPressure >= 30 && pressure.nextPressure < 40) {
      PressureIndex = 3;
    } else if (pressure.nextPressure >= 40 && pressure.nextPressure < 50) {
      PressureIndex = 4;
    } else if (pressure.nextPressure >= 50 && pressure.nextPressure < 60) {
      PressureIndex = 5;
    } else if (pressure.nextPressure >= 60 && pressure.nextPressure < 70) {
      PressureIndex = 6;
    } else if (pressure.nextPressure >= 70 && pressure.nextPressure < 80) {
      PressureIndex = 7;
    } else if (pressure.nextPressure >= 80 && pressure.nextPressure < 90) {
      PressureIndex = 8;
    } else if (pressure.nextPressure >= 90 && pressure.nextPressure < 100) {
      PressureIndex = 9;
    } else {
      // Handle unexpected values for nextPressure
      PressureIndex = -1; // Or another error value
    }

    // Only update if PressureIndex is valid
    if (PressureIndex != -1) {
      setValueAt(pressure.xPressure, pressure.yPressure, PressureIndex);
    } else {
      cerr << "Error: Pressure value (" << pressure.nextPressure << ") is out of bounds." << endl;
    }
  }
}

void updateArrayWithPressureLMHData(const vector < PressureData > & pressures) {
    const string L = "L";  // Low
    const string M = "M";  // Medium
    const string H = "H";  // High

    for (size_t i = 0; i < pressures.size(); ++i) {
    const PressureData & pressure = pressures[i];

    // Debug output
    //    cout << "--------------------" << endl;
    //    cout << "Processing Pressure data for index " << i << endl;
    //    cout << "x: " << pressure.xPressure << endl;
    //    cout << "y: " << pressure.yPressure << endl;
    //    cout << "Next Day: " << pressure.nextPressure << endl;

        string PressureLMH;
        // Set value in the 2D array based on nextCloud
        if (pressure.nextPressure >= 0 && pressure.nextPressure < 35) {
            PressureLMH = L;
        } else if (pressure.nextPressure >= 35 && pressure.nextPressure < 65) {
            PressureLMH = M;
        } else if (pressure.nextPressure >= 65 && pressure.nextPressure < 100) {
            PressureLMH = H;
        } else {
            // Handle unexpected values for nextCloud
            PressureLMH = "-1"; // Or another error value
        }

        // Only update if PressureLMH is not an error value
        if (PressureLMH != "-1") {
            setValueLMH(pressure.xPressure, pressure.yPressure, PressureLMH);
        } else {
            cerr << "Error: Pressure value (" << pressure.nextPressure << ") is out of bounds." << endl;
        }
    }
}
