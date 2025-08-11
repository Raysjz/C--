#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Struct to hold data about a city
struct CityData {
    int xCord;
    int yCord;
    int cSize;    // Size category of the city (e.g., small, medium, big)
    int cNumber;  // City ID
    string cName;

    // Method to reset the struct
    void reset() {
        xCord = 0;
        yCord = 0;
        cSize = 0;
        cNumber = 0;
        cName.clear(); // Clear the string
    }
};

// Struct to hold data about a cloud
struct CloudData {
    int xCloud;
    int yCloud;
    int nextCloud;

    // Method to reset the struct
    void reset() {
        xCloud = 0;
        yCloud = 0;
        nextCloud = 0;
    }
};

// Struct to hold data about pressure readings
struct PressureData {
    int xPressure;
    int yPressure;
    int nextPressure;

    // Method to reset the struct
    void reset() {
        xPressure = 0;
        yPressure = 0;
        nextPressure = 0;
    }
};

// Vectors to store collections of data
vector<CityData> cities;        // Vector to store all city data
vector<CloudData> clouds;       // Vector to store all cloud data
vector<PressureData> pressures; // Vector to store all pressure data

void resetAllData() {
    // Reset all vectors
    cities.clear();
    clouds.clear();
    pressures.clear();
}

void populateData() {
    // Populate vectors with example data
    cities.push_back({1, 2, 3, 4, "CityA"});
    clouds.push_back({5, 6, 7});
    pressures.push_back({8, 9, 10});
}

void printData() {
    // Print data from vectors
    cout << "Cities:" << endl;
    for (const auto& city : cities) {
        cout << "xCord: " << city.xCord << ", yCord: " << city.yCord
             << ", cSize: " << city.cSize << ", cNumber: " << city.cNumber
             << ", cName: " << city.cName << endl;
    }

    cout << "Clouds:" << endl;
    for (const auto& cloud : clouds) {
        cout << "xCloud: " << cloud.xCloud << ", yCloud: " << cloud.yCloud
             << ", nextCloud: " << cloud.nextCloud << endl;
    }

    cout << "Pressures:" << endl;
    for (const auto& pressure : pressures) {
        cout << "xPressure: " << pressure.xPressure << ", yPressure: " << pressure.yPressure
             << ", nextPressure: " << pressure.nextPressure << endl;
    }
}

int main() {
    populateData(); // Populate vectors with example data

    cout << "Before resetting:" << endl;
    printData(); // Print data before resetting

    resetAllData(); // Clear all vectors

    cout << "After resetting:" << endl;
    printData(); // Print data after resetting

    return 0;
}
