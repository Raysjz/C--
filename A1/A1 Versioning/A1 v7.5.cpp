#include <algorithm>   // For algorithms like sort
#include <fstream>     // For file input and output
#include <iomanip>     // For formatting output
#include <iostream>    // For standard input and output
#include <limits>      // For numeric limits
#include <set>         // For set container
#include <sstream>     // For string stream operations
#include <string>      // For string operations
#include <vector>      // For vector container

using namespace std; // Use the standard namespace to avoid prefixing std::

// Global variables
string** array2D = nullptr;
bool bInit = false;  // Auto init of readConfig()
int choice;
int x;
int y;
int fileCounter;  // Initialize counter for files
string cLine;
bool isArrayInitialized = false; // Flag to indicate if the 2D array has been initialized
int smallCounter = 0; // Counter for small cities
int medCounter = 0;    // Counter for medium cities
int bigCounter = 0;    // Counter for large cities

// Function to tokenize a string based on a delimiter
vector<string> tokenizeString(string input, string delimiter);

// Struct definitions

// Struct to hold data about a city
struct CityData {
  int xCord;
  int yCord;
  int cSize;    // Size category of the city (e.g., small, medium, big)
  int cNumber;  // City ID
  string cName;
};

// Struct to hold data about a cloud
struct CloudData {
  int xCloud;
  int yCloud;
  int nextCloud;
};

// Struct to hold data about pressure readings
struct PressureData {
  int xPressure;
  int yPressure;
  int nextPressure;
};

// Vectors to store collections of data
vector<CityData> cities;        // Vector to store all city data
vector<CloudData> clouds;       // Vector to store all cloud data
vector<PressureData> pressures; // Vector to store all pressure data

//---------------Function Prototype--------------------------------------------------------------------------

//---------------------------------Menu----------------------------------
void displayMenu();
void processOption(int choice);
void waitForEnter();

//---------------------------------Read and Init----------------------------------------------
void readConfig();
void readAFile(string&, int);
void init2DArray(int, int);
void display2DArray(int, int);
void deallocateMemory(int, int);

//-----------------------------------Parse Data----------------------------------------------
CityData parseCityData(string& input);
CloudData parseCloudData(string& input);
PressureData parsePressureData(string& input);
void determineCitySizes(vector<CityData>& cities);
void setValueAt(int col, int row, int& value);
void setValueLMH(int col, int row, string& valueStr);
void populateWithCityData(vector<CityData>& cities);
void populateWithCloudIndexData(vector<CloudData>& clouds);
void populateWithCloudLMHData(vector<CloudData>& clouds);
void populateWithPressureData(vector<PressureData>& pressures);
void populateWithPressureLMHData(vector<PressureData>& pressures);

//--------------------------------------Summary----------------------------------------------
// Displays the main menu to the user
void displayMenu();

// Processes the user's menu choice
void processOption(int choice);

// Pauses the program and waits for the user to press Enter
void waitForEnter();

//---------------------------------Read and Init----------------------------------------------
// Reads configuration settings and initializes variables
void readConfig();

// Reads a file and processes its contents based on an identifier
void readAFile(string&, int);

// Initializes a 2D array with given dimensions
void init2DArray(int rows, int cols);

// Displays the contents of the 2D array
void display2DArray(int rows, int cols);

// Deallocates memory used by the 2D array
void deallocateMemory(int rows, int cols);

//-----------------------------------Parse Data----------------------------------------------
// Parses city data from a string and returns a CityData object
CityData parseCityData(string& input);

// Parses cloud data from a string and returns a CloudData object
CloudData parseCloudData(string& input);

// Parses pressure data from a string and returns a PressureData object
PressureData parsePressureData(string& input);

// Determines and categorizes city sizes (small, medium, big)
void determineCitySizes(vector<CityData>& cities);

// Sets a value at a specific column and row in the 2D array
void setValueAt(int col, int row, int& value);

// Sets a value in the 2D array based on a string input for LMH (Low, Medium, High)
void setValueLMH(int col, int row, string& valueStr);

// Populates the city vector with data from input sources
void populateWithCityData(vector<CityData>& cities);

// Populates the cloud vector with index data
void populateWithCloudIndexData(vector<CloudData>& clouds);

// Populates the cloud vector with LMH (Low, Medium, High) data
void populateWithCloudLMHData(vector<CloudData>& clouds);

// Populates the pressure vector with data from input sources
void populateWithPressureData(vector<PressureData>& pressures);

// Populates the pressure vector with LMH (Low, Medium, High) data
void populateWithPressureLMHData(vector<PressureData>& pressures);

//--------------------------------Summary----------------------------------------------

// Determines probability of rain based on city and pressure data
void probRain(char c, char p);

// Extracts coordinates from the city data for a given size, names, and IDs
vector<pair<int, int>> extractCoordinates(vector<CityData>& cities, int size,
                                          vector<string>& names,
                                          vector<int>& ids);

// Calculates total cloud cover and pressure for the given coordinates
void calculateTotals(vector<pair<int, int>>& coords, vector<CloudData>& clouds,
                     vector<PressureData>& pressures, int& cityCloud,
                     int& cityPressure);

// Gets surrounding coordinates for a specific x, y location
vector<pair<int, int>> getSurrounding(int x, int y);

// Calculates surrounding data for a 1x1 city size and updates totals
void calculateSurrounding1x1(vector<pair<int, int>>& smallCities,
                             vector<CloudData>& clouds,
                             vector<PressureData>& pressures, int& cityCloud,
                             int& cityPressure);

// Calculates surrounding data for a 2x2 city size and updates totals
vector<pair<int, int>> calculateSurrounding2x2(vector<pair<int, int>>& cities,
                                               vector<CloudData>& clouds,
                                               vector<PressureData>& pressures,
                                               int& cityCloud,
                                               int& cityPressure);

// Gets surrounding coordinates for a 3x3 area
vector<pair<int, int>> getSurrounding3x3(int x, int y);

// Calculates surrounding data for a 3x3 city size and updates totals
vector<pair<int, int>> calculateSurrounding3x3(vector<pair<int, int>>& cities,
                                               vector<CloudData>& clouds,
                                               vector<PressureData>& pressures,
                                               int& cityCloud,
                                               int& cityPressure);

// Displays a summary of small cities, including cloud and pressure data
void displaySCSummary(vector<CityData>& cities, vector<CloudData>& clouds,
                      vector<PressureData>& pressures);

// Displays a summary of medium cities, including cloud and pressure data
void displayMCSummary(vector<CityData>& cities, vector<CloudData>& clouds,
                      vector<PressureData>& pressures);

// Displays a summary of big cities, including cloud and pressure data
void displayBCSummary(vector<CityData>& cities, vector<CloudData>& clouds,
                      vector<PressureData>& pressures);


int main() {  //------------Start of Main------------------------------

  // Prompt to read and process the configuration file
  if (!bInit) {
    choice = 1;  // Automatically set to read and process the configuration file
    processOption(choice);  // Process the configuration file
    bInit = true;            // Set init to true after processing
  }

  do {
    displayMenu();
    cin >> choice;

    // Clear input buffer in case of invalid input
    if (cin.fail()) {
      cin.clear();  // Clear the error flag
      cin.ignore(numeric_limits<streamsize>::max(),
                 '\n');  // Discard invalid input
      choice = 0;        // Set choice to 0 to prompt user again
    }

    processOption(choice);

    if (choice >= 2 && choice <= 7) {
      waitForEnter();
    }

  } while (choice != 8);

  cout << "Exiting program. Goodbye!" << endl;
  return 0;
}  //------------End of Main------------------------------


//-----------Start of Menu ------------------------------

void displayMenu() {  // Menu Display
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

void processOption(int choice) {
  switch (choice) {
    case 1:
      // Call function to read and process configuration file
        readConfig();

      

      break;
    case 2:
      // Call function to display city map
      cout << "----------------------------------------------" << endl;
      cout << "[Displaying city map]" << endl;
      cout << "----------------------------------------------" << endl;
      init2DArray(x, y);
      populateWithCityData(cities);
      display2DArray(x, y);
      deallocateMemory(x, y);
      break;
    case 3:
      // Call function to display cloud coverage map (cloudiness index)
      cout << "----------------------------------------------" << endl;
      cout << "[Displaying cloud coverage map (cloudiness index)]" << endl;
      cout << "----------------------------------------------" << endl;
      init2DArray(x, y);
      populateWithCloudIndexData(clouds);
      display2DArray(x, y);
      deallocateMemory(x, y);
      break;
    case 4:
      // Call function to display cloud coverage map (LHM symbols)
      cout << "----------------------------------------------" << endl;
      cout << "[Displaying cloud coverage map (LHM symbols)]" << endl;
      cout << "----------------------------------------------" << endl;
      init2DArray(x, y);
      populateWithCloudLMHData(clouds);
      display2DArray(x, y);
      deallocateMemory(x, y);
      break;
    case 5:
      // Call function to display atmospheric pressure map (pressure index)
      cout << "----------------------------------------------" << endl;
      cout << "[Displaying atmospheric pressure map (pressure index)]" << endl;
      cout << "----------------------------------------------" << endl;
      init2DArray(x, y);
      populateWithPressureData(pressures);
      display2DArray(x, y);
      deallocateMemory(x, y);

      break;
    case 6:
      // Call function to display atmospheric pressure map (LHM symbols)
      cout << "----------------------------------------------" << endl;
      cout << "[Displaying atmospheric pressure map (LHM symbols)]" << endl;
      cout << "----------------------------------------------" << endl;
      init2DArray(x, y);
      populateWithPressureLMHData(pressures);
      display2DArray(x, y);
      deallocateMemory(x, y);
      break;
    case 7:
      // Call function to show weather forecast summary report
      cout << "----------------------------------------------" << endl;
      cout << "[Showing weather forecast summary report]" << endl;
      cout << "----------------------------------------------" << endl;
      cout << "Weather Forecast Summary Report" << endl;
      cout << "---------------------------" << endl;
      displayBCSummary(cities, clouds, pressures);
      displayMCSummary(cities, clouds, pressures);
      displaySCSummary(cities, clouds, pressures);

      break;
    case 8:
      // Quit the program
      cout << "Thank you for using Weather Information Processing System, have "
              "a nice day!"
           << endl;
      deallocateMemory(x, y);
      break;
    default:
      cout << "[Invalid input]\n"
           << endl;  // Outputs this if invalid input is keyed
      cin.clear();   // Clear input stream state
      break;
  }
}

void waitForEnter() {
  cout << "Press <Enter> to go back to the main menu...";
  cin.ignore(numeric_limits<streamsize>::max(),
             '\n');  // Discard any remaining input
  cin.clear();       // Clear input stream state
  cin.get();         // Wait for user to press Enter
}

//----------------------End of menu -------------------------------------------

//------------Start  of  Read and Init------------------------------

void init2DArray(int col, int row) {
  array2D = new string*[row];
  for (int i = 0; i < row; i++) {
    array2D[i] = new string[col];
  }

  // No default values needed
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      array2D[i][j] = "";  // Initialize with empty strings
    }
  }
}

void display2DArray(int col, int row) {
if (!isArrayInitialized) {
    cout << endl;
    cout << "<----Array not initialized. Cannot display---->" << endl;
    cout << endl;
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

void deallocateMemory(int col, int row) {
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
  cout << "----------------------------------------------" << endl;
  cout << "[Read in and process a configuration file]\n";
  cout << "----------------------------------------------" << endl;
  cout << "Please enter the config filename: ";

  string inputFilename;
  cin >> inputFilename;
  inputFilename += ".txt";  // Appended .txt to lessen the hassle of typing .txt

  ifstream inputFile(inputFilename.c_str());
  if (!inputFile) {
    cerr << "Failed to open " << inputFilename << endl;
    return;
  }

  deallocateMemory(x, y); //Deallocate Array Size before inputting in new Array Size

  string aLine;
  vector<string> tempStr;
  vector<string> tempStr2;
  string temps;

  cout << endl;
  while (getline(inputFile, aLine)) {
    // cout << aLine << endl;

    tempStr = tokenizeString(aLine, "=");

    if (tempStr[0] == "GridX_IdxRange") {
      temps = tempStr[1];
      tempStr2 = tokenizeString(temps, "-");
      x = stoi(tempStr2[1]) + 1;
      cout << "Reading in GridX_IdxRange : " << tempStr[1] << "... done!"
           << endl;
    } else if (tempStr[0] == "GridY_IdxRange") {
      temps = tempStr[1];
      tempStr2 = tokenizeString(temps, "-");
      y = stoi(tempStr2[1]) + 1;
      cout << "Reading in GridY_IdxRange : " << tempStr[1] << "... done!"
           << endl;
    }
  }

  fstream inputFile1(inputFilename.c_str(),
                     fstream::in);  // Second file stream to find all the lines
                                    // that end in .txt for value mapping
  cout << endl;
  cout << "Storing data from input file: " << endl;
  while (getline(inputFile1, cLine)) {
    // cout << cLine << endl;
    size_t pos = cLine.find(".txt");

    if (pos != string::npos) {
      readAFile(cLine, fileCounter);
      fileCounter++;

    }
  }       
  isArrayInitialized = true;
  fileCounter = 0; //Reset File Counter to 0 for new inputs
  //cout << "File Counter when successfully stored:" << fileCounter << endl;
  cout << endl;
  cout << "All records successfully stored. Going back to main menu" << endl
       << endl;
}

void readAFile(string& filename, int fileCounter) {
  string aLine;

  ifstream inputFile(filename.c_str());  // Use the filename parameter
  if (!inputFile) {
    cerr << filename << "... failed!" << endl;
    fileCounter = 0; //Reset File Counter to 0 for new inputs if failed to input data
    return;
  }else{
    cout << filename << "... done!" << endl;
  }

  if (fileCounter == 0) {
    while (getline(inputFile, aLine)) {
      if (!aLine.empty()) {
        // cout << " inside citylocation.txt" << endl;
        CityData city = parseCityData(aLine);
        // Check if the city coordinates are within bounds
        if (city.xCord >= 0 && city.xCord < x && city.yCord >= 0 &&
            city.yCord < y) {
          cities.push_back(city);  // Store each CityData struct in the vector
        } else {
          cerr << "Error: City coordinates (" << city.xCord << ", "
               << city.yCord << ") are out of bounds." << endl;
        }
      }
    }
  } else if (fileCounter == 1) {
    while (getline(inputFile, aLine)) {
      if (!aLine.empty()) {
        // cout << " inside cloudcover.txt" << endl;
        CloudData cloud = parseCloudData(aLine);
        // Check if the Cloud coordinates are within bounds
        if (cloud.xCloud >= 0 && cloud.xCloud < x && cloud.yCloud >= 0 &&
            cloud.yCloud < y) {
          clouds.push_back(cloud);  // Store each CloudData struct in the vector
        } else {
          cerr << "Error: Cloud coordinates (" << cloud.xCloud << ", "
               << cloud.yCloud << ") are out of bounds." << endl;
        }
      }
    }
  } else if (fileCounter == 2) {
    while (getline(inputFile, aLine)) {
      if (!aLine.empty()) {
        // cout << " inside pressure.txt" << endl;
        PressureData pressure = parsePressureData(aLine);
        // Check if the Cloud coordinates are within bounds
        if (pressure.xPressure >= 0 && pressure.xPressure < x &&
            pressure.yPressure >= 0 && pressure.yPressure < y) {
          pressures.push_back(
              pressure);  // Store each PressureData struct in the vector
        } else {
          cerr << "Error: Pressure coordinates (" << pressure.xPressure << ", "
               << pressure.yPressure << ") are out of bounds." << endl;
        }
      }
    }
  } else {
    inputFile.close();  // Close the file after reading
  }

}

//------------End  of  Read and Init------------------------------

//---------------Start of Parse Data---------------------------------------

// Parses a string input to extract CityData information
CityData parseCityData(string& input) {
  CityData data;
  // Tokenize the input string based on the "-" delimiter
  vector<string> parts = tokenizeString(input, "-");

  // Check if the input string was correctly tokenized into 3 parts
  if (parts.size() == 3) {
    string coordinates = parts[0];
    string cityNumber = parts[1];
    string cityName = parts[2];

    // Remove brackets from coordinates (e.g., "(x,y)" to "x,y")
    coordinates = coordinates.substr(1, coordinates.size() - 2);
    // Tokenize coordinates based on the "," delimiter
    vector<string> coordinateParts = tokenizeString(coordinates, ",");

    // Convert the coordinate parts to integers and assign to CityData
    data.xCord = stoi(coordinateParts[0]);
    data.yCord = stoi(coordinateParts[1]);
    data.cNumber = stoi(cityNumber);
    data.cSize = 0;  // Initialize with 0, will be calculated later
    determineCitySizes(cities); // Determine the size of the city
    data.cName = cityName;
  } else {
    cerr << "Unexpected format in parseCityData." << endl;
  }
  return data;
}

// Populates the 2D array with city data from the cities vector
void populateWithCityData(vector<CityData>& cities) {
  for (size_t i = 0; i < cities.size(); ++i) {
    CityData& city = cities[i];

    // Set the value in the 2D array based on city coordinates and number
    setValueAt(city.xCord, city.yCord, city.cNumber);
  }
}

// Determines the size of cities based on their occurrences
void determineCitySizes(vector<CityData>& cities) {
  for (size_t i = 0; i < cities.size(); ++i) {
    int count = -1;  // Initialize count to -1 to exclude the current city
    // Count occurrences of cities with the same number and name
    for (size_t j = 0; j < cities.size(); ++j) {
      if (cities[i].cNumber == cities[j].cNumber &&
          cities[i].cName == cities[j].cName) {
        count++;
      }
    }
    // Assign size based on the count
    if (count == 0 ) {
      cities[i].cSize = 0;  // Small
    } else if (count == 2 || count == 3) {
      cities[i].cSize = 4;  // Medium
    } else if (count == 7 || count == 8) {
      cities[i].cSize = 9;  // Big
    } else {
      cities[i].cSize = 0;  // Default to Small if size doesn't match specified criteria
    }
  }
}

// Sets a value in the 2D array at the specified column and row
void setValueAt(int col, int row, int& value) {
  // Check if the indices are within bounds
  if (row >= 0 && row < y && col >= 0 && col < x) {
    // Check if the array is initialized
    if (array2D) {
      array2D[row][col] = to_string(value);  // Convert integer to string
    } else {
      cerr << "Error: Array is not initialized." << endl;
    }
  } else {
    cerr << "Error: Index out of bounds when setting value at (" << col << ", "
         << row << ")." << endl;
  }
}

// Sets a value in the 2D array at the specified column and row with a string value
void setValueLMH(int col, int row, string& valueStr) {
  // Check if the indices are within bounds
  if (row >= 0 && row < y && col >= 0 && col < x) {
    // Check if the array is initialized
    if (array2D) {
      array2D[row][col] = valueStr;
    } else {
      cerr << "Error: Array is not initialized." << endl;
    }
  } else {
    cerr << "Error: Index out of bounds when setting value at (" << col << ", "
         << row << ")." << endl;
  }
}


//---------------End of City ---------------------------------------

// Parses a string input to extract CloudData information
CloudData parseCloudData(string& input) {
  CloudData data;
  // Tokenize the input string based on the "-" delimiter
  vector<string> parts = tokenizeString(input, "-");

  // Check if the input string was correctly tokenized into 2 parts
  if (parts.size() == 2) {
    string coordinates = parts[0];
    string nextDay = parts[1];

    // Remove brackets from coordinates (e.g., "(x,y)" to "x,y")
    coordinates = coordinates.substr(1, coordinates.size() - 2);
    // Tokenize coordinates based on the "," delimiter
    vector<string> coordinate_parts = tokenizeString(coordinates, ",");

    // Convert the coordinate parts to integers and assign to CloudData
    data.xCloud = stoi(coordinate_parts[0]);
    data.yCloud = stoi(coordinate_parts[1]);
    data.nextCloud = stoi(nextDay);
  } else {
    cerr << "Unexpected format in parseCloudData." << endl;
  }

  return data;
}

// Populates the 2D array with cloud index data based on the nextCloud value
void populateWithCloudIndexData(vector<CloudData>& clouds) {
  for (size_t i = 0; i < clouds.size(); ++i) {
    CloudData& cloud = clouds[i];

    int cloudIndex;
    // Determine cloud index based on nextCloud value ranges
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
      cloudIndex = -1;  // Or another error value
    }

    // Only update if cloudIndex is valid
    if (cloudIndex != -1) {
      setValueAt(cloud.xCloud, cloud.yCloud, cloudIndex);
    } else {
      cerr << "Error: Cloud value (" << cloud.nextCloud << ") is out of bounds."
           << endl;
    }
  }
}

// Populates the 2D array with cloud data categorized as Low, Medium, or High
void populateWithCloudLMHData(vector<CloudData>& clouds) {
  string L = "L";  // Low
  string M = "M";  // Medium
  string H = "H";  // High

  for (size_t i = 0; i < clouds.size(); ++i) {
    CloudData& cloud = clouds[i];

    string cloudLMH;
    // Determine cloud category based on nextCloud value ranges
    if (cloud.nextCloud >= 0 && cloud.nextCloud < 35) {
      cloudLMH = L;
    } else if (cloud.nextCloud >= 35 && cloud.nextCloud < 65) {
      cloudLMH = M;
    } else if (cloud.nextCloud >= 65 && cloud.nextCloud < 100) {
      cloudLMH = H;
    } else {
      // Handle unexpected values for nextCloud
      cloudLMH = "-1";  // Or another error value
    }

    // Only update if cloudLMH is not an error value
    if (cloudLMH != "-1") {
      setValueLMH(cloud.xCloud, cloud.yCloud, cloudLMH);
    } else {
      cerr << "Error: Cloud value (" << cloud.nextCloud << ") is out of bounds."
           << endl;
    }
  }
}


//---------------End of Cloud ---------------------------------------

// Parses a string input to extract PressureData information
PressureData parsePressureData(string& input) {
  PressureData data;
  // Tokenize the input string based on the "-" delimiter
  vector<string> parts = tokenizeString(input, "-");

  // Check if the input string was correctly tokenized into 2 parts
  if (parts.size() == 2) {
    string coordinates = parts[0];
    string nextDay = parts[1];

    // Remove brackets from coordinates (e.g., "(x,y)" to "x,y")
    coordinates = coordinates.substr(1, coordinates.size() - 2);
    // Tokenize coordinates based on the "," delimiter
    vector<string> coordinate_parts = tokenizeString(coordinates, ",");

    // Convert the coordinate parts to integers and assign to PressureData
    data.xPressure = stoi(coordinate_parts[0]);
    data.yPressure = stoi(coordinate_parts[1]);
    data.nextPressure = stoi(nextDay);
  } else {
    cerr << "Unexpected format in parsePressureData." << endl;
  }

  return data;
}

// Populates the 2D array with pressure index data based on the nextPressure value
void populateWithPressureData(vector<PressureData>& pressures) {
  for (size_t i = 0; i < pressures.size(); ++i) {
    PressureData& pressure = pressures[i];

    int PressureIndex;
    // Determine pressure index based on nextPressure value ranges
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
      PressureIndex = -1;  // Or another error value
    }

    // Only update if PressureIndex is valid
    if (PressureIndex != -1) {
      setValueAt(pressure.xPressure, pressure.yPressure, PressureIndex);
    } else {
      cerr << "Error: Pressure value (" << pressure.nextPressure
           << ") is out of bounds." << endl;
    }
  }
}

// Populates the 2D array with pressure data categorized as Low, Medium, or High
void populateWithPressureLMHData(vector<PressureData>& pressures) {
  string L = "L";  // Low
  string M = "M";  // Medium
  string H = "H";  // High

  for (size_t i = 0; i < pressures.size(); ++i) {
    PressureData& pressure = pressures[i];

    string PressureLMH;
    // Determine pressure category based on nextPressure value ranges
    if (pressure.nextPressure >= 0 && pressure.nextPressure < 35) {
      PressureLMH = L;
    } else if (pressure.nextPressure >= 35 && pressure.nextPressure < 65) {
      PressureLMH = M;
    } else if (pressure.nextPressure >= 65 && pressure.nextPressure < 100) {
      PressureLMH = H;
    } else {
      // Handle unexpected values for nextPressure
      PressureLMH = "-1";  // Or another error value
    }

    // Only update if PressureLMH is not an error value
    if (PressureLMH != "-1") {
      setValueLMH(pressure.xPressure, pressure.yPressure, PressureLMH);
    } else {
      cerr << "Error: Pressure value (" << pressure.nextPressure
           << ") is out of bounds." << endl;
    }
  }
}


//-----------------------------Summary---------------------------------------

void probRain(char c, char p)  // Rain Probability
{
  float chance;
  if (c == 'H' && p == 'L') {
    //------------90%----------------
    chance = 90;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4)
         << ": " << fixed << setprecision(2) << chance << endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "\\\\\\\\\\" << endl;
  } else if (c == 'M' && p == 'L') {
    //------------80%----------------
    chance = 80;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4)
         << ": " << fixed << setprecision(2) << chance << endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << " \\\\\\\\" << endl;
  } else if (c == 'L' && p == 'L') {
    //------------70%----------------
    chance = 70;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4)
         << ": " << fixed << setprecision(2) << chance << endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "  \\\\\\" << endl;
  } else if (c == 'H' && p == 'M') {
    //------------60%----------------
    chance = 60;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4)
         << ": " << fixed << setprecision(2) << chance << endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "   \\\\" << endl;
  } else if (c == 'M' && p == 'M') {
    //------------50%----------------
    chance = 50;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4)
         << ": " << fixed << setprecision(2) << chance << endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "    \\" << endl;
  } else if (c == 'L' && p == 'M') {
    //------------40%----------------
    chance = 40;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4)
         << ": " << fixed << setprecision(2) << chance << endl;
    cout << "~~~~" << endl;
    cout << "~~~~~" << endl;
  } else if (c == 'H' && p == 'H') {
    //------------30%----------------
    chance = 30;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4)
         << ": " << fixed << setprecision(2) << chance << endl;
    cout << "~~~" << endl;
    cout << "~~~~" << endl;
  } else if (c == 'M' && p == 'H') {
    //------------20%----------------
    chance = 20;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4)
         << ": " << fixed << setprecision(2) << chance << endl;
    cout << "~~" << endl;
    cout << "~~~" << endl;
  } else if (c == 'L' && p == 'H') {
    //------------10%----------------
    chance = 10;
    cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4)
         << ": " << fixed << setprecision(2) << chance << endl;
    cout << "~" << endl;
    cout << "~~" << endl;
  }
}


// Function to extract coordinates from cities based on size
vector<pair<int, int>> extractCoordinates(vector<CityData>& cities, int size,
                                          vector<string>& names,
                                          vector<int>& ids) {
  vector<pair<int, int>> coords;
  names.clear();
  ids.clear();

  for (CityData& city : cities) {
    if (city.cSize == size) {
      coords.emplace_back(city.xCord, city.yCord);
      names.push_back(city.cName);
      ids.push_back(city.cNumber);
    }
  }

  return coords;
}

// Function to calculate City Cloud and pressure for specific coordinates
void calculateTotals(vector<pair<int, int>>& coords, vector<CloudData>& clouds,
                     vector<PressureData>& pressures, int& cityCloud,
                     int& cityPressure) {
  cityCloud = 0;
  cityPressure = 0;

  // Iterate through coordinates to accumulate cloud and pressure values
  for (pair<int, int>& coord : coords) {
    for (CloudData& cloud : clouds) {
      if (cloud.xCloud == coord.first && cloud.yCloud == coord.second) {
        cityCloud += cloud.nextCloud;
        break;  // Moves to the next coordinate once a match is found
      }
    }
    for (PressureData& pressure : pressures) {
      if (pressure.xPressure == coord.first &&
          pressure.yPressure == coord.second) {
        cityPressure += pressure.nextPressure;
        break;  // Moves to the next coordinate once a match is found
      }
    }
  }
}

// Function to compute surrounding coordinates
vector<pair<int, int>> getSurrounding(int x, int y) {
  return {
      {x, y - 1},     // North
      {x, y + 1},     // South
      {x - 1, y},     // West
      {x + 1, y},     // East
      {x - 1, y - 1}, // North-West
      {x + 1, y - 1}, // North-East
      {x - 1, y + 1}, // South-West
      {x + 1, y + 1}  // South-East
  };
}

// Function to calculate Cloud and pressure for surrounding coordinates
void calculateSurrounding1x1(vector<pair<int, int>>& smallCities,
                             vector<CloudData>& clouds,
                             vector<PressureData>& pressures, int& cityCloud,
                             int& cityPressure) {
  cityCloud = 0;
  cityPressure = 0;

   // Iterate through small cities
  for (pair<int, int>& city : smallCities) {
    vector<pair<int, int>> surroundingCoords =
        getSurrounding(city.first, city.second);

     // Iterate through surrounding coordinates
    for (pair<int, int>& coord : surroundingCoords) {
      bool foundCloud = false;
      bool foundPressure = false;

      for (CloudData& cloud : clouds) {
        if (cloud.xCloud == coord.first && cloud.yCloud == coord.second) {
          foundCloud = true;
          cityCloud += cloud.nextCloud;
        }
      }

      for (PressureData& pressure : pressures) {
        if (pressure.xPressure == coord.first &&
            pressure.yPressure == coord.second) {
          foundPressure = true;
          cityPressure += pressure.nextPressure;
        }
      }

      smallCounter++; // Counter to calculate what is the size within border

      // cout << "(" << coord.first << ", " << coord.second << ") ";
      if (foundCloud) {
        // << "Cloud: " << cityCloud << " ";
      }
      if (foundPressure) {
        // cout << "Pressure: " << cityPressure << " ";
      }
      if (!foundCloud && !foundPressure) {
        // cout << "No data ";
        smallCounter--; // Counter to calculate what is the size within border
      }

      // cout << "[SCounter: " << smallCounter << "]" << endl;
    }
  }
}

// Function to calculate unique surrounding coordinates for a 2x2 grid for
// medium cities
vector<pair<int, int>> calculateSurrounding2x2(vector<pair<int, int>>& cities,
                                               vector<CloudData>& clouds,
                                               vector<PressureData>& pressures,
                                               int& cityCloud,
                                               int& cityPressure) {
  cityCloud = 0;
  cityPressure = 0;

  vector<pair<int, int>> allSurroundingCoords;
  vector<pair<int, int>> uniqueSurroundingCoords;

  // Iterate through each mid city and get surrounding coordinates
  for (pair<int, int>& city : cities) {
    vector<pair<int, int>> surroundingCoords =
        getSurrounding(city.first, city.second);
    allSurroundingCoords.insert(allSurroundingCoords.end(),
                                surroundingCoords.begin(),
                                surroundingCoords.end());
  }

  // Remove duplicates manually
  for (pair<int, int>& coord : allSurroundingCoords) {
    if (find(uniqueSurroundingCoords.begin(), uniqueSurroundingCoords.end(),
             coord) == uniqueSurroundingCoords.end()) {
      uniqueSurroundingCoords.push_back(coord);
    }
  }

  // Calculate cloud and pressure totals for the unique surrounding coordinates
  for (pair<int, int>& coord : uniqueSurroundingCoords) {
    bool foundCloud = false;
    bool foundPressure = false;

    // Check for cloud data
    for (CloudData& cloud : clouds) {
      if (cloud.xCloud == coord.first && cloud.yCloud == coord.second) {
        cityCloud += cloud.nextCloud;
        foundCloud = true;
      }
    }

    // Check for pressure data
    for (PressureData& pressure : pressures) {
      if (pressure.xPressure == coord.first &&
          pressure.yPressure == coord.second) {
        cityPressure += pressure.nextPressure;
        foundPressure = true;
      }
    }
    medCounter++; // Counter to calculate what is the size within border

    // Print debug output
    // cout << "(" << coord.first << ", " << coord.second << ") ";
    if (foundCloud) {
      // cout << "Cloud: " << cityCloud << " ";
    }
    if (foundPressure) {
      // cout << "Pressure: " << cityPressure << " ";
    }
    if (!foundCloud && !foundPressure) {
      // cout << "No data ";
      medCounter--; // Counter to calculate what is the size within border
    }
    // cout << "[MCounter: "<< medCounter << "]" << endl; 
  }

  return uniqueSurroundingCoords;
}

// Function to get surrounding coordinates for a 3x3 grid
vector<pair<int, int>> getSurrounding3x3(int x, int y) {
  vector<pair<int, int>> coords;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      coords.emplace_back(x + i, y + j);
    }
  }
  return coords;
}

// Function to calculate unique surrounding coordinates for a 3x3 grid for big
// cities
vector<pair<int, int>> calculateSurrounding3x3(vector<pair<int, int>>& cities,
                                               vector<CloudData>& clouds,
                                               vector<PressureData>& pressures,
                                               int& cityCloud,
                                               int& cityPressure) {
  cityCloud = 0;
  cityPressure = 0;

  set<pair<int, int>> uniqueSurroundingCoords;  // Use set to avoid duplicates

  // Iterate through each big city and get surrounding coordinates
  for (pair<int, int>& city : cities) {
    vector<pair<int, int>> surroundingCoords =
        getSurrounding3x3(city.first, city.second);
    for (pair<int, int>& coord : surroundingCoords) {
      uniqueSurroundingCoords.insert(coord);
    }
  }

  // Calculate cloud and pressure totals for the unique surrounding coordinates
  for (auto& coord : uniqueSurroundingCoords) {
    bool foundCloud = false;
    bool foundPressure = false;

    // Check for cloud data
    for (CloudData& cloud : clouds) {
      if (cloud.xCloud == coord.first && cloud.yCloud == coord.second) {
        cityCloud += cloud.nextCloud;
        foundCloud = true;
      }
    }

    // Check for pressure data
    for (PressureData& pressure : pressures) {
      if (pressure.xPressure == coord.first &&
          pressure.yPressure == coord.second) {
        cityPressure += pressure.nextPressure;
        foundPressure = true;
      }
    }
    bigCounter++; // Counter to calculate what is the size within border

    // Print debug output
    // << "(" << coord.first << ", " << coord.second << ") ";
    if (foundCloud) {
      // cout << "Cloud: " << cityCloud << " ";
    }
    if (foundPressure) {
      // cout << "Pressure: " << cityPressure << " ";
    }
    if (!foundCloud && !foundPressure) {
      // cout << "No data ";
      bigCounter--; // Counter to calculate what is the size within border
    }

    // cout << "[BigCounter: "<< bigCounter << "]" << endl;
  }

  return vector<pair<int, int>>(uniqueSurroundingCoords.begin(),
                                uniqueSurroundingCoords.end());
}

void displaySCSummary(vector<CityData>& cities, vector<CloudData>& clouds,
                      vector<PressureData>& pressures) {
  vector<string> smallCityNames;
  vector<int> smallCityIDs;
  vector<pair<int, int>> smallCities;

  smallCities = extractCoordinates(cities, 0, smallCityNames, smallCityIDs);

  char pressureIndex = ' ';
  char cloudIndex = ' ';

  if (!smallCities.empty()) {
    for (size_t i = 0; i < smallCities.size(); ++i) {
      pair<int, int>& cityCoord = smallCities[i];
      string& cityName = smallCityNames[i];
      int cityNumber = smallCityIDs[i];

      vector<pair<int, int>> cityCoords = {cityCoord};

      int cityCloud, cityPressure;
      calculateTotals(cityCoords, clouds, pressures, cityCloud, cityPressure);

      int surroundingCloud, surroundingPressure;
      smallCounter = 0;  // Reset counter for each city
      calculateSurrounding1x1(cityCoords, clouds, pressures, surroundingCloud,
                              surroundingPressure);

      double avesCloud =
          ((cityCloud + surroundingCloud) / static_cast<double>(smallCounter + 1));
      double avesPressure = ((cityPressure + surroundingPressure) /
                             static_cast<double>(smallCounter + 1));

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
      cout << "Ave. Cloud Cover (ACC) " << right << setw(6) << ": " << avesCloud
           << " (" << string(1, cloudIndex) << ")" << endl;
      cout << "Ave. Pressure" << right << setw(8) << "(AP)" << right << setw(8)
           << ": " << avesPressure << " (" << string(1, pressureIndex) << ")"
           << endl;
      probRain(cloudIndex, pressureIndex);
      cout << endl;
    }
  }
}

void displayMCSummary(vector<CityData>& cities, vector<CloudData>& clouds,
                      vector<PressureData>& pressures) {
  vector<string> mediumCityNames;
  vector<int> mediumCityIDs;
  vector<pair<int, int>> mediumCities =
      extractCoordinates(cities, 4, mediumCityNames, mediumCityIDs);

  char pressureIndex = ' ';
  char cloudIndex = ' ';
  string cityName;
  int cityNumber;
  int surroundingCloud, surroundingPressure;
  double avesCloud;
  double avesPressure;
  cout << endl;

  if (!mediumCities.empty()) {
    for (size_t i = 0; i < mediumCities.size(); ++i) {
      pair<int, int>& cityCoord = mediumCities[i];
      cityName = mediumCityNames[i];
      cityNumber = mediumCityIDs[i];

      vector<pair<int, int>> cityCoords = {cityCoord};

      int cityCloud, cityPressure;
      calculateTotals(mediumCities, clouds, pressures, cityCloud, cityPressure);

      medCounter = 0;  // Reset counter for each city
      calculateSurrounding2x2(mediumCities, clouds, pressures, surroundingCloud,
                              surroundingPressure);

      avesCloud = ((surroundingCloud) / static_cast<double>(medCounter));
      avesPressure = ((surroundingPressure) / static_cast<double>(medCounter));

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
    cout << "Ave. Cloud Cover (ACC) " << right << setw(6) << ": " << avesCloud
         << " (" << string(1, cloudIndex) << ")" << endl;
    cout << "Ave. Pressure" << right << setw(8) << "(AP)" << right << setw(8)
         << ": " << avesPressure << " (" << string(1, pressureIndex) << ")"
         << endl;
    probRain(cloudIndex, pressureIndex);
    cout << endl;
  }
}

// Function to display the summary of cities
void displayBCSummary(vector<CityData>& cities, vector<CloudData>& clouds,
                      vector<PressureData>& pressures) {
  // Extract coordinates for big city size vector pairing
  vector<string> bigCityNames;
  vector<int> bigCityIDs;
  vector<pair<int, int>> bigCities =
      extractCoordinates(cities, 9, bigCityNames, bigCityIDs);

  char pressureIndex = ' ';
  char cloudIndex = ' ';
  string cityName;
  int cityNumber;
  int surroundingCloud, surroundingPressure;
  double avesCloud;
  double avesPressure;
  cout << endl;

  if (!bigCities.empty()) {
    for (size_t i = 0; i < bigCities.size(); ++i) {
      pair<int, int>& cityCoord = bigCities[i];
      cityName = bigCityNames[i];
      cityNumber = bigCityIDs[i];

      vector<pair<int, int>> cityCoords = {cityCoord};

      int cityCloud, cityPressure;
      calculateTotals(bigCities, clouds, pressures, cityCloud, cityPressure);
      // Calculate totals for surrounding coordinates
      bigCounter = 0;
      calculateSurrounding3x3(bigCities, clouds, pressures, surroundingCloud,
                              surroundingPressure);

      avesCloud = ((surroundingCloud) / static_cast<double>(bigCounter));
      avesPressure = ((surroundingPressure) / static_cast<double>(bigCounter));

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
    cout << "Ave. Cloud Cover (ACC) " << right << setw(6) << ": " << avesCloud
         << " (" << string(1, cloudIndex) << ")" << endl;
    cout << "Ave. Pressure" << right << setw(8) << "(AP)" << right << setw(8)
         << ": " << avesPressure << " (" << string(1, pressureIndex) << ")"
         << endl;
    probRain(cloudIndex, pressureIndex);
    cout << endl;
  }
}