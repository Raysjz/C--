/*-----------------------------------------------------------
---25 Jul 24------*Unused)Summary for SC--------------------------
-------------------------------------------------------------*/
// Function4 is better that calculates coordinates of 1 ,4 ,9
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
string city_Number;
string next_Cloud;
int counter = 0; // Initialize counter
string cLine;
int smallCityCount = 0;
int mediumCityCount = 0;
int bigCityCount = 0;


// Define the CityData struct before using it
struct CityData {
    int xCord;
    int yCord;
    int cNumber;
    string cName;
    int cSize;  // This will hold the size based on the count
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
void determineCitySizes(vector<CityData>& cities);
vector < string > tokenizeString(string input, string delimiter);
vector < CityData > cities; // Vector to store CityData structs
vector < CloudData > clouds;
vector < PressureData > pressures;
CityData parseCityData(const string & input);
CloudData parseCloudData(const string & input);
PressureData parsePressureData(const string & input);
void setValueAt(int row, int col,
  const int & value);
void setValueLMH(int row, int col,
  const string & valueStr);
void rain_prob(char c, char p);
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


// Function to print the nextCloud and nextPressure values for surrounding coordinates
void displaySC(const vector<CityData>& cities, const vector<CloudData>& clouds, const vector<PressureData>& pressures) {
    for (const auto& city : cities) {
        if (city.cSize == 0) {  // Assuming 0 indicates a small city
            cout << "City: " << city.cName << " (" << city.xCord << ", " << city.yCord << "), Size: " << city.cSize << endl;
            
            vector<int> cloudValues;
            vector<int> pressureValues;
            int x = city.xCord;
            int y = city.yCord;
            string cityName = city.cName;
            int cityNumber = city.cNumber;
            int sizeCounter = 1;
            int cityCloud = 0;
            int cityPressure = 0;
            int surroundingCloud = 0;
            int surroundingPressure = 0;
            double totalCloud = 0;
            double totalPressure = 0;
            char pressureIndex = ' ';
            char cloudIndex = ' ';

            // Compute surrounding coordinates
            vector<pair<int, int>> surroundingCoords = {
                {x, y - 1}, {x, y + 1}, // North, South
                {x - 1, y}, {x + 1, y}, // West, East
                {x - 1, y - 1}, {x + 1, y - 1}, // North-West, North-East
                {x - 1, y + 1}, {x + 1, y + 1}  // South-West, South-East
            };

            

            // Extract city cloud and pressure data
            for (const auto & cloud : clouds) {
                if (cloud.xCloud == x && cloud.yCloud == y) {
                    cityCloud = cloud.nextCloud;
                }
            }

            for (const auto & pressure : pressures) {
                if (pressure.xPressure == x && pressure.yPressure == y) {
                    cityPressure = pressure.nextPressure;
                }
            }

            // Extract the relevant surrounding cloud and pressure data
            for (const auto& coord : surroundingCoords) {
                int cx = coord.first;
                int cy = coord.second;

                bool foundCloud = false;
                bool foundPressure = false;

                for (const auto& cloud : clouds) {
                    if (cloud.xCloud == cx && cloud.yCloud == cy) {
                        cloudValues.push_back(cloud.nextCloud);
                        surroundingCloud += cloud.nextCloud;
                        foundCloud = true;
                    }
                }

                for (const auto& pressure : pressures) {
                    if (pressure.xPressure == cx && pressure.yPressure == cy) {
                        pressureValues.push_back(pressure.nextPressure);
                        surroundingPressure += pressure.nextPressure;
                        foundPressure = true;
                    }
                }

                cout << "(" << cx << ", " << cy << ") ";
                if (foundCloud) cout << "Cloud: " << cloudValues.back() << " ";
                if (foundPressure) cout << "Pressure: " << pressureValues.back() << " ";
                if (!foundCloud && !foundPressure) cout << "No data ";
                cout << endl;

                if (foundCloud || foundPressure) {
                        sizeCounter++;
                  }
            }

            // Calculate average values
            totalCloud = ((cityCloud + surroundingCloud) / static_cast<double>(sizeCounter));
            totalPressure = ((cityPressure + surroundingPressure) / static_cast<double>(sizeCounter));

            // Determine cloud and pressure indices
            if (totalPressure >= 0 && totalPressure < 35) {
                pressureIndex = 'L';
            } else if (totalPressure >= 35 && totalPressure < 65) {
                pressureIndex = 'M';
            } else if (totalPressure >= 65) {
                pressureIndex = 'H';
            }

            if (totalCloud >= 0 && totalCloud < 35) {
                cloudIndex = 'L';
            } else if (totalCloud >= 35 && totalCloud < 65) {
                cloudIndex = 'M';
            } else if (totalCloud >= 65) {
                cloudIndex = 'H';
            }

            // Output results
            cout << endl;
            cout << "City Name: " << cityName << endl;
            cout << "City ID: " << cityNumber << endl;
            cout << "Counter: " << sizeCounter << endl;
            cout << "City Clouds: " << cityCloud << endl;
            cout << "City Pressure: " << cityPressure << endl;
            cout << "Surround Cloud: " << surroundingCloud << endl;
            cout << "Surround Pressure: " << surroundingPressure << endl;
            cout << "Ave. Cloud Cover (ACC): " << setprecision(2) << totalCloud << " (" << string(1, cloudIndex) << ")" << endl;
            cout << "Ave. Pressure (AP): " << setprecision(2) << totalPressure << " (" << string(1, pressureIndex) << ")" << endl;
            rain_prob(cloudIndex, pressureIndex);
            cout << endl;
        }
    }
}

void rain_prob(char c, char p) //simple rain probability print function based on the table given by the assignment document
{
  float prob;
  //if statements for every possible LMH combination leading to a computation of rain probability
  if (c == 'H' && p == 'L') {
    //90%
    prob = 90;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": " <<
      fixed << setprecision(2) << prob <<
      endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "\\\\\\\\\\" << endl;
  } else if (c == 'M' && p == 'L') {
    //80%
    prob = 80;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": " <<
      fixed << setprecision(2) << prob <<
      endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << " \\\\\\\\" << endl;
  } else if (c == 'L' && p == 'L') {
    //70%
    prob = 70;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": " <<
      fixed << setprecision(2) << prob <<
      endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "  \\\\\\" << endl;
  } else if (c == 'H' && p == 'M') {
    //60%
    prob = 60;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": " <<
      fixed << setprecision(2) << prob <<
      endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "   \\\\" << endl;
  } else if (c == 'M' && p == 'M') {
    //50%
    prob = 50;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": " <<
      fixed << setprecision(2) << prob <<
      endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "    \\" << endl;
  } else if (c == 'L' && p == 'M') {
    //40%
    prob = 40;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": " <<
      fixed << setprecision(2) << prob <<
      endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
  } else if (c == 'H' && p == 'H') {
    //30%
    prob = 30;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": " <<
      fixed << setprecision(2) << prob <<
      endl;
    cout << "~~~" << endl;
    cout << "~~~~" << endl;
  } else if (c == 'M' && p == 'H') {
    //20%
    prob = 20;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": " <<
      fixed << setprecision(2) << prob <<
      endl;
    cout << "~~" << endl;
    cout << "~~~" << endl;
  } else if (c == 'L' && p == 'H') {
    //10%
    prob = 10;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": " <<
      fixed << setprecision(2) << prob <<
      endl;
    cout << "~" << endl;
    cout << "~~" << endl;
  }
}

void displayWeatherforecast() {
  cout << "Weather Forecast Summary Report" << endl;
  cout << "-------------------------------" << endl;
  //displayBC(cities, clouds, pressures);
  cout << endl;
  //displayMC(cities, clouds, pressures);
  cout << endl;
  displaySC(cities, clouds, pressures);

}

int main() { // Start of Main
  readConfig(); // This will read the configuration file and initialize x, y, etc.

  init2DArray(x, y); // Initialize the 2D array with dimensions x and y
  populate2DArray(x, y); // Populate the 2D array with default values

  // Call updateArrayWithCityData with the cities vector
  updateArrayWithCityData(cities); // Pass the vector of CityData objects to the function

  //updateArrayWithCloudData(clouds);
  //updateArrayWithCloudLMHData(clouds);

  //updateArrayWithPressureData(pressures);
  //updateArrayWithPressureLMHData(pressures);
  displayWeatherforecast();

  isArrayInitialized = true; // Mark array as initialized

  display2DArray(x, y); // Display the contents of the 2D array
  safelyDeallocateMemory(x, y); // Deallocate memory

  cout << endl;
  return 0;
} // End of Main

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
  vector < string > tempStr;
  vector < string > tempStr2;
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
  } else if (counter == 1) {
    while (getline(inputFile, aLine)) {
      if (!aLine.empty()) {
        cout << " inside cloudcover.txt" << endl;

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
        cout << " inside pressure.txt" << endl;
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
    // Use the new function to update the array
    updateArrayWithCityData(cities);
  }

}

//--------------- Value ---------------------------------------

void setValueAt(int row, int col,
  const int & value) {
  if (row >= 0 && row < y && col >= 0 && col < x) {
    if (array2D) {
      array2D[row][col] = to_string(value); // Convert integer to string
      cout << "Setting coordinates at (" << row << ", " << col << "), Value: " << value << endl; // Debug output
      cout << endl;
    } else {
      cerr << "Error: Array is not initialized." << endl;
    }
  } else {
    cerr << "Error: Index out of bounds when setting value at (" << row << ", " << col << ")." << endl;
  }
}

void setValueLMH(int row, int col,
  const string & valueStr) {
  if (row >= 0 && row < y && col >= 0 && col < x) {
    if (array2D) {
      array2D[row][col] = valueStr;
      cout << "Setting coordinates at (" << row << ", " << col << "), Value: " << valueStr << endl; // Debug output
      cout << endl;
    } else {
      cerr << "Error: Array is not initialized." << endl;
    }
  } else {
    cerr << "Error: Index out of bounds when setting value at (" << row << ", " << col << ")." << endl;
  }
}

void determineCitySizes(vector<CityData>& cities) {


    // Loop through cities to determine counts and assign sizes
    for (size_t i = 0; i < cities.size(); ++i) {
        int count = 0;

        // Count the number of cities with the same number and name
        for (size_t j = 0; j < cities.size(); ++j) {
            if (cities[i].cNumber == cities[j].cNumber && cities[i].cName == cities[j].cName) {
                count++;
            }
        }

        // Assign size label based on the count
        if (count == 1) {
            cities[i].cSize = 0;  // Small City
            smallCityCount++;
        } else if (count == 4) {
            cities[i].cSize = 2;  // Medium City
            mediumCityCount++;
        } else if (count == 9) {
            cities[i].cSize = 3;  // Big City
            bigCityCount++;
        } else {
            cities[i].cSize = -1; // Undefined size
        }
    }
}

//--------------- City ---------------------------------------
CityData parseCityData(const string& input) {
    CityData data;
    vector<string> parts = tokenizeString(input, "-");

    if (parts.size() == 3) {
        string coordinates = parts[0];
        string cityNumber = parts[1];
        string cityName = parts[2];

        // Remove brackets from coordinates
        coordinates = coordinates.substr(1, coordinates.size() - 2);
        vector<string> coordinateParts = tokenizeString(coordinates, ",");

        data.xCord = stoi(coordinateParts[0]);
        data.yCord = stoi(coordinateParts[1]);
        data.cNumber = stoi(cityNumber);
        data.cName = cityName;
        data.cSize = 0; // Initialize with 0, will be calculated later
        determineCitySizes(cities);
    } else {
        cerr << "Unexpected format in parseCityData." << endl;
    }
    return data;
}

void updateArrayWithCityData(const vector < CityData > & cities) {
  for (size_t i = 0; i < cities.size(); ++i) {
    const CityData & city = cities[i];
    
  //Debug output
  cout << "------City Data--------------" << endl;
  cout << "Processing city data for index " << i << endl;
  cout << "x: " << city.xCord << endl;
  cout << "y: " << city.yCord << endl;
  cout << "City Number: " << city.cNumber << endl;
  cout << "City Size: " << city.cSize << endl;
  cout << "City Name: " << city.cName << endl;


    // Set value in the 2D array
    setValueAt(city.yCord, city.xCord, city.cNumber);
  }
}

//---------------End of City ---------------------------------------

CloudData parseCloudData(const string & input) {
  CloudData data;
  vector < string > parts = tokenizeString(input, "-");

  cout << endl;
  for (int i = 0; i < parts.size(); i++)
    cout << parts[i] << endl;
  cout << endl;

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
    cout << "--------------------" << endl;
    cout << "Processing Cloud data for index " << i << endl;
    cout << "x: " << cloud.xCloud << endl;
    cout << "y: " << cloud.yCloud << endl;
    cout << "Next Day: " << cloud.nextCloud << endl;

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

void updateArrayWithCloudLMHData(const vector < CloudData > & clouds) {

  for (size_t i = 0; i < clouds.size(); ++i) {
    const CloudData & cloud = clouds[i];

    // Debug output
    cout << "--------------------" << endl;
    cout << "Processing Cloud data for index " << i << endl;
    cout << "x: " << cloud.xCloud << endl;
    cout << "y: " << cloud.yCloud << endl;
    cout << "Next Day: " << cloud.nextCloud << endl;

    string cloudLMH;
    // Set value in the 2D array based on nextCloud
    if (cloud.nextCloud >= 0 && cloud.nextCloud < 35) {
      cloudLMH = "L";
    } else if (cloud.nextCloud >= 35 && cloud.nextCloud < 65) {
      cloudLMH = "M";
    } else if (cloud.nextCloud >= 65 && cloud.nextCloud < 100) {
      cloudLMH = "H";
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

  cout << endl;
  for (int i = 0; i < parts.size(); i++)
    cout << parts[i] << endl;
  cout << endl;

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
    cout << "--------------------" << endl;
    cout << "Processing Pressure data for index " << i << endl;
    cout << "x: " << pressure.xPressure << endl;
    cout << "y: " << pressure.yPressure << endl;
    cout << "Next Day: " << pressure.nextPressure << endl;

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

  for (size_t i = 0; i < pressures.size(); ++i) {
    const PressureData & pressure = pressures[i];

    // Debug output
    cout << "--------------------" << endl;
    cout << "Processing Pressure data for index " << i << endl;
    cout << "x: " << pressure.xPressure << endl;
    cout << "y: " << pressure.yPressure << endl;
    cout << "Next Day: " << pressure.nextPressure << endl;

    string PressureLMH;
    // Set value in the 2D array based on nextCloud
    if (pressure.nextPressure >= 0 && pressure.nextPressure < 35) {
      PressureLMH = "L";
    } else if (pressure.nextPressure >= 35 && pressure.nextPressure < 65) {
      PressureLMH = "M";
    } else if (pressure.nextPressure >= 65 && pressure.nextPressure < 100) {
      PressureLMH = "H";
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