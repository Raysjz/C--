#include "algo.h"

// Global variable definitions
string ** array2D = nullptr;
bool init = false;
int choice = 0;
int fileCounter = 0;
int x;
int y;
string cLine;
int smallCounter = 0;
int medCounter = 0;
int bigCounter = 0;
vector<CityData> cities;
vector<CloudData> clouds;
vector<PressureData> pressures;


void displayMenu() { // Menu Display 
  cout << endl;
  cout << "Student ID\t: 8466385" << endl;
  cout << "Student Name\t: Raydon See Jing Zhou" << endl;
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

void readConfig() {
  cout << "----------------------------------------------" << endl;
  cout << "[Read in and process a configuration file]\n";
  cout << "----------------------------------------------" << endl;
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
      readAFile(cLine, fileCounter);
      fileCounter++;

      cout << cLine << "... done!" << endl;
    }
  }



  cout << endl;
  cout << "All records successfully stored. Going back to main menu" << endl << endl;
}

void readAFile(string & filename, int fileCounter) {

  string aLine;

  ifstream inputFile(filename.c_str()); // Use the filename parameter
  if (!inputFile) {
    cerr << "Failed to open " << filename << endl;
    return;
  }

  if (fileCounter == 0) {
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
  } else if (fileCounter == 1) {
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
  } else if (fileCounter == 2) {
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

void display2DArray(int col, int row) {

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

void deallocateMemory(int col, int row) {
  if (array2D) {
    for (int i = 0; i < row; i++) {
      delete[] array2D[i];
    }
    delete[] array2D;
    array2D = nullptr;
  }
}



void setValueAt(int col, int row, int & value) {
  if (row >= 0 && row < y && col >= 0 && col < x) {
    if (array2D) {
      array2D[row][col] = to_string(value); // Convert integer to string
    } else {
      cerr << "Error: Array is not initialized." << endl;
    }
  } else {
    cerr << "Error: Index out of bounds when setting value at (" << col << ", " << row << ")." << endl;
  }
}

void setValueLMH(int col, int row, string & valueStr) {
  if (row >= 0 && row < y && col >= 0 && col < x) {
    if (array2D) {
      array2D[row][col] = valueStr;
    } else {
      cerr << "Error: Array is not initialized." << endl;
    }
  } else {
    cerr << "Error: Index out of bounds when setting value at (" << col << ", " << row << ")." << endl;
  }
}

// Function to determine city sizes without using unordered_map
void determineCitySizes(vector < CityData > & cities) {
  for (size_t i = 0; i < cities.size(); ++i) {
    int count = -1;
    for (size_t j = 0; j < cities.size(); ++j) {
      if (cities[i].cNumber == cities[j].cNumber && cities[i].cName == cities[j].cName) {
        count++;
      }
    }
    // Assign size based on the new criteria
    if (count == 1) {
      cities[i].cSize = 0; // Small
    } else if (count == 3) {
      cities[i].cSize = 3; // Mid
    } else if (count == 8) {
      cities[i].cSize = 8; // Big
    } else {
      cities[i].cSize = 0; // Default to Small if size doesn't match specified criteria
    }
  }

}

//---------------Start of City ---------------------------------------
CityData parseCityData(string & input) {
  CityData data;
  vector < string > parts = tokenizeString(input, "-");

  if (parts.size() == 3) {
    string coordinates = parts[0];
    string cityNumber = parts[1];
    string cityName = parts[2];

    // Remove brackets from coordinates
    coordinates = coordinates.substr(1, coordinates.size() - 2);
    vector < string > coordinateParts = tokenizeString(coordinates, ",");

    data.xCord = stoi(coordinateParts[0]);
    data.yCord = stoi(coordinateParts[1]);
    data.cNumber = stoi(cityNumber);
    data.cSize = 0; // Initialize with 0, will be calculated later
    determineCitySizes(cities);
    data.cName = cityName;
  } else {
    cerr << "Unexpected format in parseCityData." << endl;
  }
  return data;
}

void populateWithCityData(vector < CityData > & cities) {
  for (size_t i = 0; i < cities.size(); ++i) {
    CityData & city = cities[i];
    /*
      //Debug output
      cout << "--------------------" << endl;
      cout << "Processing city data for index " << i << endl;
      cout << "x: " << city.xCord << endl;
      cout << "y: " << city.yCord << endl;
      cout << "Size: " << city.cSize << endl;
      cout << "Number: " << city.cNumber << endl;
      cout << "City Name: " << city.cName << endl;
    */
    // Set value in the 2D array
    setValueAt(city.xCord, city.yCord, city.cNumber);
  }
}

//---------------End of City ---------------------------------------

CloudData parseCloudData(string & input) {
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

void populateWithCloudIndexData(vector < CloudData > & clouds) {
  for (size_t i = 0; i < clouds.size(); ++i) {
    CloudData & cloud = clouds[i];

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

void populateWithCloudLMHData(vector < CloudData > & clouds) {
  string L = "L"; // Low
  string M = "M"; // Medium
  string H = "H"; // High

  for (size_t i = 0; i < clouds.size(); ++i) {
    CloudData & cloud = clouds[i];

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

PressureData parsePressureData(string & input) {
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

void populateWithPressureData(vector < PressureData > & pressures) {
  for (size_t i = 0; i < pressures.size(); ++i) {
    PressureData & pressure = pressures[i];

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

void populateWithPressureLMHData(vector < PressureData > & pressures) {
  string L = "L"; // Low
  string M = "M"; // Medium
  string H = "H"; // High

  for (size_t i = 0; i < pressures.size(); ++i) {
    PressureData & pressure = pressures[i];

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

//-----------------------------Summary---------------------------------------

void probRain(char c, char p) //Rain Probability
{
  float chance;
  if (c == 'H' && p == 'L') {
    //------------90%----------------
    chance = 90;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": " <<
      fixed << setprecision(2) << chance <<
      endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "\\\\\\\\\\" << endl;
  } else if (c == 'M' && p == 'L') {
    //------------80%----------------
    chance = 80;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": " <<
      fixed << setprecision(2) << chance <<
      endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << " \\\\\\\\" << endl;
  } else if (c == 'L' && p == 'L') {
    //------------70%----------------
    chance = 70;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": " <<
      fixed << setprecision(2) << chance <<
      endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "  \\\\\\" << endl;
  } else if (c == 'H' && p == 'M') {
    //------------60%----------------
    chance = 60;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": " <<
      fixed << setprecision(2) << chance <<
      endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "   \\\\" << endl;
  } else if (c == 'M' && p == 'M') {
    //------------50%----------------
    chance = 50;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": " <<
      fixed << setprecision(2) << chance <<
      endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "    \\" << endl;
  } else if (c == 'L' && p == 'M') {
    //------------40%----------------
    chance = 40;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": " <<
      fixed << setprecision(2) << chance <<
      endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
  } else if (c == 'H' && p == 'H') {
    //------------30%----------------
    chance = 30;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": " <<
      fixed << setprecision(2) << chance <<
      endl;
    cout << "~~~" << endl;
    cout << "~~~~" << endl;
  } else if (c == 'M' && p == 'H') {
    //------------20%----------------
    chance = 20;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": " <<
      fixed << setprecision(2) << chance <<
      endl;
    cout << "~~" << endl;
    cout << "~~~" << endl;
  } else if (c == 'L' && p == 'H') {
    //------------10%----------------
    chance = 10;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": " <<
      fixed << setprecision(2) << chance <<
      endl;
    cout << "~" << endl;
    cout << "~~" << endl;
  }
}

// Function to handle coordinates
void handleCoordinates(vector < pair < int, int >> & coords) {
  //cout << "Handling coordinates, size: " << coords.size() << "\n";

  if (coords.empty()) {
    // cout << "No coordinates available.\n";
  } else if (coords.size() == 0) {
    // cout << "Single coordinate set:\n";
    // cout << "Coordinate: (" << coords[0].first << ", " << coords[0].second << ")\n";
  } else if (coords.size() == 3) {
    // cout << "Set of 4 coordinates:\n";
    for (pair < int, int > & coord: coords) {
      //    cout << "Coordinate: (" << coord.first << ", " << coord.second << ")\n";
    }
  } else if (coords.size() == 8) {
    // cout << "Set of 9 coordinates:\n";
    for (pair < int, int > & coord: coords) {
      //    cout << "Coordinate: (" << coord.first << ", " << coord.second << ")\n";
    }
  } else {
    // cout << "Unsupported number of coordinates: " << coords.size() << "\n";
  }
}

// Function to extract coordinates from cities based on size
vector < pair < int, int >> extractCoordinates(vector < CityData > & cities, int size, vector < string > & names, vector < int > & ids) {
  vector < pair < int, int >> coords;
  names.clear();
  ids.clear();
  coords.clear();

  for (CityData & city: cities) {
    if (city.cSize == size) {
      coords.emplace_back(city.xCord, city.yCord);
      names.push_back(city.cName);
      ids.push_back(city.cNumber);
    }
  }
  /*
    // Debug outputs
    cout << "Names in extractCoordinates:" << endl;
    for (auto & name: names) {
      cout << name << endl;
    }
    cout << "IDs in extractCoordinates:" << endl;
    for (auto & id: ids) {
      cout << id << endl;
    }
    cout << "Coords in extractCoordinates:" << endl;
    for (auto & coord: coords) {
      cout << "(" << coord.first << ", " << coord.second << ")" << endl;
    }
  */
  return coords;
}

// Function to calculate City Cloud and pressure for specific coordinates
void calculateTotals(vector < pair < int, int >> & coords,
  vector < CloudData > & clouds,
  vector < PressureData > & pressures,
  int & cityCloud, int & cityPressure) {
  cityCloud = 0;
  cityPressure = 0;

  for (pair < int, int > & coord: coords) {
    for (CloudData & cloud: clouds) {
      if (cloud.xCloud == coord.first && cloud.yCloud == coord.second) {
        cityCloud += cloud.nextCloud;
        break; // Move to next coordinate
      }
    }
    for (PressureData & pressure: pressures) {
      if (pressure.xPressure == coord.first && pressure.yPressure == coord.second) {
        cityPressure += pressure.nextPressure;
        break; // Move to next coordinate
      }
    }
  }
}

// Function to compute surrounding coordinates
vector < pair < int, int >> getSurrounding(int x, int y) {
  return {
    {
      x,
      y - 1
    },
    {
      x,
      y + 1
    }, // North, South
    {
      x - 1,
      y
    },
    {
      x + 1,
      y
    }, // West, East
    {
      x - 1,
      y - 1
    },
    {
      x + 1,
      y - 1
    }, // North-West, North-East
    {
      x - 1,
      y + 1
    },
    {
      x + 1,
      y + 1
    } // South-West, South-East
  };
}

// Function to calculate Cloud and pressure for surrounding coordinates
void calculateSurrounding1x1(vector < pair < int, int >> & smallCities,
  vector < CloudData > & clouds,
  vector < PressureData > & pressures,
  int & cityCloud, int & cityPressure) {
  cityCloud = 0;
  cityPressure = 0;

  for (pair < int, int > & city: smallCities) {
    vector < pair < int, int >> surroundingCoords = getSurrounding(city.first, city.second);

    for (pair < int, int > & coord: surroundingCoords) {
      bool foundCloud = false;
      bool foundPressure = false;

      for (CloudData & cloud: clouds) {
        if (cloud.xCloud == coord.first && cloud.yCloud == coord.second) {
          foundCloud = true;
          cityCloud += cloud.nextCloud;
        }
      }

      for (PressureData & pressure: pressures) {
        if (pressure.xPressure == coord.first && pressure.yPressure == coord.second) {
          foundPressure = true;
          cityPressure += pressure.nextPressure;
        }
      }

      smallCounter++;

      //cout << "(" << coord.first << ", " << coord.second << ") ";
      if (foundCloud) {
        // << "Cloud: " << cityCloud << " ";
      }
      if (foundPressure) {
        //    cout << "Pressure: " << cityPressure << " ";
      }
      if (!foundCloud && !foundPressure) {
        //    cout << "No data ";
        smallCounter--;
      }

      // cout << "[SCounter: " << smallCounter << "]" << endl;
    }
  }
}

// Function to calculate unique surrounding coordinates for a 2x2 grid for medium cities
vector < pair < int, int >> calculateSurrounding2x2(vector < pair < int, int >> & cities,
  vector < CloudData > & clouds,
  vector < PressureData > & pressures,
  int & cityCloud, int & cityPressure) {
  cityCloud = 0;
  cityPressure = 0;

  vector < pair < int, int >> allSurroundingCoords;
  vector < pair < int, int >> uniqueSurroundingCoords;

  // Iterate through each city and get surrounding coordinates
  for (pair < int, int > & city: cities) {
    vector < pair < int, int >> surroundingCoords = getSurrounding(city.first, city.second);
    allSurroundingCoords.insert(allSurroundingCoords.end(), surroundingCoords.begin(), surroundingCoords.end());
  }

  // Remove duplicates manually
  for (pair < int, int > & coord: allSurroundingCoords) {
    if (find(uniqueSurroundingCoords.begin(), uniqueSurroundingCoords.end(), coord) == uniqueSurroundingCoords.end()) {
      uniqueSurroundingCoords.push_back(coord);
    }
  }

  // Calculate cloud and pressure totals for the unique surrounding coordinates
  for (pair < int, int > & coord: uniqueSurroundingCoords) {
    bool foundCloud = false;
    bool foundPressure = false;

    // Check for cloud data
    for (CloudData & cloud: clouds) {
      if (cloud.xCloud == coord.first && cloud.yCloud == coord.second) {
        cityCloud += cloud.nextCloud;
        foundCloud = true;
      }
    }

    // Check for pressure data
    for (PressureData & pressure: pressures) {
      if (pressure.xPressure == coord.first && pressure.yPressure == coord.second) {
        cityPressure += pressure.nextPressure;
        foundPressure = true;
      }
    }
    medCounter++;

    // Print debug output
    //cout << "(" << coord.first << ", " << coord.second << ") ";
    if (foundCloud) {
      //   cout << "Cloud: " << cityCloud << " ";
    }
    if (foundPressure) {
      //   cout << "Pressure: " << cityPressure << " ";
    }
    if (!foundCloud && !foundPressure) {
      //    cout << "No data ";
      medCounter--;
    }
    // cout << "[MCounter: "<< medCounter << "]" << endl;

  }

  return uniqueSurroundingCoords;
}

// Function to get surrounding coordinates for a 3x3 grid
vector < pair < int, int >> getSurrounding3x3(int x, int y) {
  vector < pair < int, int >> coords;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      coords.emplace_back(x + i, y + j);
    }
  }
  return coords;
}

// Function to calculate unique surrounding coordinates for a 3x3 grid for big cities
vector < pair < int, int >> calculateSurrounding3x3(vector < pair < int, int >> & cities,
  vector < CloudData > & clouds,
  vector < PressureData > & pressures,
  int & cityCloud, int & cityPressure) {
  cityCloud = 0;
  cityPressure = 0;

  set < pair < int, int >> uniqueSurroundingCoords; // Use set to avoid duplicates

  // Iterate through each city and get surrounding coordinates
  for (pair < int, int > & city: cities) {
    vector < pair < int, int >> surroundingCoords = getSurrounding3x3(city.first, city.second);
    for (pair < int, int > & coord: surroundingCoords) {
      uniqueSurroundingCoords.insert(coord);
    }
  }

  // Calculate cloud and pressure totals for the unique surrounding coordinates
  for (auto & coord: uniqueSurroundingCoords) {
    bool foundCloud = false;
    bool foundPressure = false;

    // Check for cloud data
    for (CloudData & cloud: clouds) {
      if (cloud.xCloud == coord.first && cloud.yCloud == coord.second) {
        cityCloud += cloud.nextCloud;
        foundCloud = true;
      }
    }

    // Check for pressure data
    for (PressureData & pressure: pressures) {
      if (pressure.xPressure == coord.first && pressure.yPressure == coord.second) {
        cityPressure += pressure.nextPressure;
        foundPressure = true;
      }
    }
    bigCounter++;

    // Print debug output
    // << "(" << coord.first << ", " << coord.second << ") ";
    if (foundCloud) {
      //   cout << "Cloud: " << cityCloud << " ";
    }
    if (foundPressure) {
      //    cout << "Pressure: " << cityPressure << " ";
    }
    if (!foundCloud && !foundPressure) {
      //   cout << "No data ";
      bigCounter--;
    }

    // cout << "[BigCounter: "<< bigCounter << "]" << endl;

  }

  return vector < pair < int, int >> (uniqueSurroundingCoords.begin(), uniqueSurroundingCoords.end());
}

void displaySCSummary(vector < CityData > & cities,
  vector < CloudData > & clouds,
  vector < PressureData > & pressures) {
  vector < string > smallCityNames;
  vector < int > smallCityIDs;
  vector < pair < int, int >> smallCities;

  smallCities = extractCoordinates(cities, 0, smallCityNames, smallCityIDs);

  char pressureIndex = ' ';
  char cloudIndex = ' ';
  //cout << "Small City Summary: " << endl;

  if (!smallCities.empty()) {
    for (size_t i = 0; i < smallCities.size(); ++i) {
      pair < int, int > & cityCoord = smallCities[i];
      string & cityName = smallCityNames[i];
      int cityNumber = smallCityIDs[i];

      vector < pair < int, int >> cityCoords = {
        cityCoord
      };
      handleCoordinates(cityCoords);

      int cityCloud, cityPressure;
      calculateTotals(cityCoords, clouds, pressures, cityCloud, cityPressure);

      int surroundingCloud, surroundingPressure;
      smallCounter = 0; // Reset counter for each city
      calculateSurrounding1x1(cityCoords, clouds, pressures, surroundingCloud, surroundingPressure);

      int totalscCloud = cityCloud + surroundingCloud;
      int totalscPressure = cityPressure + surroundingPressure;
      double avesCloud = ((cityCloud + surroundingCloud) / static_cast < double > (smallCounter));
      double avesPressure = ((cityPressure + surroundingPressure) / static_cast < double > (smallCounter));

      if (avesCloud >= 0 && avesCloud < 35) {
        cloudIndex = 'L';
      } else if (avesCloud >= 35 && avesCloud < 65) {
        cloudIndex = 'M';
      } else if (avesCloud >= 65 && avesCloud < 100) {
        cloudIndex = 'H';
      }

      if (avesPressure >= 0 && avesPressure < 35) {
        pressureIndex = 'L';
      } else if (avesPressure >= 35 && avesPressure < 65) {
        pressureIndex = 'M';
      } else if (avesPressure >= 65 && avesPressure < 100) {
        pressureIndex = 'H';
      }

      cout << fixed << setprecision(2);
      cout << "City Name" << right << setw(5) << ": " << cityName << endl;
      cout << "City ID " << right << setw(6) << ": " << cityNumber << endl;
      //cout << "City Clouds: " << cityCloud << endl;
      //cout << "City Pressure: " << cityPressure << endl;
      //cout << "Cloud for Surrounding Coordinates: " << surroundingCloud << endl;
      //cout << "Pressure for Surrounding Coordinates: " << surroundingPressure << endl;
      //cout << "Total Cloud: " << totalscCloud << endl;
      //cout << "Total Pressure: " << totalscPressure << endl;
      cout << "Ave. Cloud Cover (ACC) " << right << setw(6) << ": " << avesCloud << " (" << string(1, cloudIndex) << ")" << endl;
      cout << "Ave. Pressure" << right << setw(8) << "(AP)" << right << setw(8) << ": " << avesPressure << " (" << string(1, pressureIndex) << ")" << endl;
      probRain(cloudIndex, pressureIndex);
      cout << endl;

    }
  }

}

void displayMCSummary(vector < CityData > & cities,
  vector < CloudData > & clouds,
  vector < PressureData > & pressures) {
  vector < string > mediumCityNames;
  vector < int > mediumCityIDs;
  vector < pair < int, int >> mediumCities = extractCoordinates(cities, 3, mediumCityNames, mediumCityIDs);

  char pressureIndex = ' ';
  char cloudIndex = ' ';
  string cityName;
  int cityNumber;
  int surroundingCloud, surroundingPressure;
  double avesCloud;
  double avesPressure;
  cout << endl;
  //cout << "Mid City Summary: " << endl;

  if (!mediumCities.empty()) {
    for (size_t i = 0; i < mediumCities.size(); ++i) {
      pair < int, int > & cityCoord = mediumCities[i];
      cityName = mediumCityNames[i];
      cityNumber = mediumCityIDs[i];

      vector < pair < int, int >> cityCoords = {
        cityCoord
      };
      handleCoordinates(cityCoords);

      int cityCloud, cityPressure;
      calculateTotals(mediumCities, clouds, pressures, cityCloud, cityPressure);

      //cout << "City Cloud: " << cityCloud << "\n";
      //cout << "City Pressure: " << cityPressure << "\n";

      // Calculate totals for surrounding coordinates

      medCounter = 0; // Reset counter for each city
      calculateSurrounding2x2(mediumCities, clouds, pressures, surroundingCloud, surroundingPressure);

      avesCloud = ((surroundingCloud) / static_cast < double > (medCounter));
      avesPressure = ((surroundingPressure) / static_cast < double > (medCounter));

      if (avesCloud >= 0 && avesCloud < 35) {
        cloudIndex = 'L';
      } else if (avesCloud >= 35 && avesCloud < 65) {
        cloudIndex = 'M';
      } else if (avesCloud >= 65 && avesCloud < 100) {
        cloudIndex = 'H';
      }

      if (avesPressure >= 0 && avesPressure < 35) {
        pressureIndex = 'L';
      } else if (avesPressure >= 35 && avesPressure < 65) {
        pressureIndex = 'M';
      } else if (avesPressure >= 65 && avesPressure < 100) {
        pressureIndex = 'H';
      }

    }
    cout << fixed << setprecision(2);
    cout << "City Name" << right << setw(5) << ": " << cityName << endl;
    cout << "City ID " << right << setw(6) << ": " << cityNumber << endl;
    //cout << "Cloud for Surrounding Coordinates: " << surroundingCloud << endl;
    //cout << "Pressure for Surrounding Coordinates: " << surroundingPressure << endl;
    cout << "Ave. Cloud Cover (ACC) " << right << setw(6) << ": " << avesCloud << " (" << string(1, cloudIndex) << ")" << endl;
    cout << "Ave. Pressure" << right << setw(8) << "(AP)" << right << setw(8) << ": " << avesPressure << " (" << string(1, pressureIndex) << ")" << endl;
    probRain(cloudIndex, pressureIndex);
    cout << endl;
  }
}

// Function to display the summary of cities
void displayBCSummary(vector < CityData > & cities,
  vector < CloudData > & clouds,
  vector < PressureData > & pressures) {
  // Extract coordinates for each city size
  vector < string > bigCityNames;
  vector < int > bigCityIDs;
  vector < pair < int, int >> bigCities = extractCoordinates(cities, 8, bigCityNames, bigCityIDs);

  char pressureIndex = ' ';
  char cloudIndex = ' ';
  string cityName;
  int cityNumber;
  int surroundingCloud, surroundingPressure;
  double avesCloud;
  double avesPressure;
  // Display summary
  cout << endl;
  //cout << "Big City Summary:\n";

  if (!bigCities.empty()) {
    for (size_t i = 0; i < bigCities.size(); ++i) {
      pair < int, int > & cityCoord = bigCities[i];
      cityName = bigCityNames[i];
      cityNumber = bigCityIDs[i];

      vector < pair < int, int >> cityCoords = {
        cityCoord
      };
      handleCoordinates(cityCoords);

      int cityCloud, cityPressure;
      calculateTotals(bigCities, clouds, pressures, cityCloud, cityPressure);
      //cout << "City Cloud: " << cityCloud << "\n";
      //cout << "City Pressure: " << cityPressure << "\n";

      // Calculate totals for surrounding coordinates
      bigCounter = 0;
      calculateSurrounding3x3(bigCities, clouds, pressures, surroundingCloud, surroundingPressure);

      avesCloud = ((surroundingCloud) / static_cast < double > (bigCounter));
      avesPressure = ((surroundingPressure) / static_cast < double > (bigCounter));

      if (avesCloud >= 0 && avesCloud < 35) {
        cloudIndex = 'L';
      } else if (avesCloud >= 35 && avesCloud < 65) {
        cloudIndex = 'M';
      } else if (avesCloud >= 65 && avesCloud < 100) {
        cloudIndex = 'H';
      }

      if (avesPressure >= 0 && avesPressure < 35) {
        pressureIndex = 'L';
      } else if (avesPressure >= 35 && avesPressure < 65) {
        pressureIndex = 'M';
      } else if (avesPressure >= 65 && avesPressure < 100) {
        pressureIndex = 'H';
      }

    }
    cout << fixed << setprecision(2);
    cout << "City Name" << right << setw(5) << ": " << cityName << endl;
    cout << "City ID " << right << setw(6) << ": " << cityNumber << endl;
    //cout << "Cloud for Surrounding Coordinates: " << surroundingCloud << endl;
    //cout << "Pressure for Surrounding Coordinates: " << surroundingPressure << endl;
    cout << "Ave. Cloud Cover (ACC) " << right << setw(6) << ": " << avesCloud << " (" << string(1, cloudIndex) << ")" << endl;
    cout << "Ave. Pressure" << right << setw(8) << "(AP)" << right << setw(8) << ": " << avesPressure << " (" << string(1, pressureIndex) << ")" << endl;
    probRain(cloudIndex, pressureIndex);
    cout << endl;
  }
}