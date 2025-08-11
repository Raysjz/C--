/*-----------------------------------------------------------
---26 Jul 24------Summary for BC--------------------------
-------------------------------------------------------------*/


#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <set> // for std::set
#include <algorithm> // for find

using namespace std;

struct CityData {
    int xCord;
    int yCord;
    int cSize; // City size
    int cNumber;
    string cName;
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

int bigCounter = 0;


void rain_prob(char c, char p) //simple rain probability print function based on the table given by the assignment document
{
    float prob;
    //if statements for every possible LMH combination leading to a computation of rain probability
    if (c == 'H' && p == 'L')
    {
        //90%
        prob = 90;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << "\\\\\\\\\\" << endl;
    }
    else if (c == 'M' && p == 'L')
    {
        //80%
        prob = 80;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << " \\\\\\\\" << endl;
    }
    else if (c == 'L' && p == 'L')
    {
        //70%
        prob = 70;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << "  \\\\\\" << endl;
    }
    else if (c == 'H' && p == 'M')
    {
        //60%
        prob = 60;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << "   \\\\" << endl;
    }
    else if (c == 'M' && p == 'M')
    {
        //50%
        prob = 50;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << "    \\" << endl;
    }
    else if (c == 'L' && p == 'M')
    {
        //40%
        prob = 40;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
    }
    else if (c == 'H' && p == 'H')
    {
        //30%
        prob = 30;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~~" << endl;
        cout << "~~~~" << endl;
    }
    else if (c == 'M' && p == 'H')
    {
        //20%
        prob = 20;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~" << endl;
        cout << "~~~" << endl;
    }
    else if (c == 'L' && p == 'H')
    {
        //10%
        prob = 10;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~" << endl;
        cout << "~~" << endl;
    }
}

// Function to handle coordinates
void handleCoordinates(const vector<pair<int, int>>& coords) {
    cout << "Handling coordinates, size: " << coords.size() << "\n";

    if (coords.empty()) {
        cout << "No coordinates available.\n";
    } else if (coords.size() == 0) {
        cout << "Single coordinate set:\n";
        cout << "Coordinate: (" << coords[0].first << ", " << coords[0].second << ")\n";
    } else if (coords.size() == 3) {
        cout << "Set of 4 coordinates:\n";
        for (const auto& coord : coords) {
            cout << "Coordinate: (" << coord.first << ", " << coord.second << ")\n";
        }
    } else if (coords.size() == 8) {
        cout << "Set of 9 coordinates:\n";
        for (const auto& coord : coords) {
            cout << "Coordinate: (" << coord.first << ", " << coord.second << ")\n";
        }
    } else {
        cout << "Unsupported number of coordinates: " << coords.size() << "\n";
    }
}

// Function to extract coordinates from cities based on size
vector<pair<int, int>> extractCoordinates(const vector<CityData>& cities, int size, vector<string>& names, vector<int>& ids) {
    vector<pair<int, int>> coords;
    names.clear();
    ids.clear();
    for (const auto& city : cities) {
        if (city.cSize == size) {
            coords.emplace_back(city.xCord, city.yCord);
            names.push_back(city.cName);
            ids.push_back(city.cNumber);
        }
    }
    
    // Debugging output
    cout << "Extracted " << coords.size() << " coordinates:\n";
    for (const auto& coord : coords) {
        cout << "(" << coord.first << ", " << coord.second << ")\n";
    }
    
    return coords;
}

// Function to calculate City Cloud and pressure for specific coordinates
void calculateTotals(const vector<pair<int, int>>& coords,
                     const vector<CloudData>& clouds,
                     const vector<PressureData>& pressures,
                     int& cityCloud, int& cityPressure) {
    cityCloud = 0;
    cityPressure = 0;

    for (const auto& coord : coords) {
        for (const auto& cloud : clouds) {
            if (cloud.xCloud == coord.first && cloud.yCloud == coord.second) {
                cityCloud += cloud.nextCloud;
                break; // Move to next coordinate
            }
        }
        for (const auto& pressure : pressures) {
            if (pressure.xPressure == coord.first && pressure.yPressure == coord.second) {
                cityPressure += pressure.nextPressure;
                break; // Move to next coordinate
            }
        }
    }
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

// Function to calculate unique surrounding coordinates for a 3x3 grid for big cities
vector<pair<int, int>> calculateSurrounding3x3(const vector<pair<int, int>>& cities,
                                               const vector<CloudData>& clouds,
                                               const vector<PressureData>& pressures,
                                               int& cityCloud, int& cityPressure) {
    cityCloud = 0;
    cityPressure = 0;

    set<pair<int, int>> uniqueSurroundingCoords; // Use set to avoid duplicates

    // Iterate through each city and get surrounding coordinates
    for (const auto& city : cities) {
        vector<pair<int, int>> surroundingCoords = getSurrounding3x3(city.first, city.second);
        for (const auto& coord : surroundingCoords) {
            uniqueSurroundingCoords.insert(coord);
        }
    }

    // Calculate cloud and pressure totals for the unique surrounding coordinates
    for (const auto& coord : uniqueSurroundingCoords) {
        bool foundCloud = false;
        bool foundPressure = false;

        // Check for cloud data
        for (const auto& cloud : clouds) {
            if (cloud.xCloud == coord.first && cloud.yCloud == coord.second) {
                cityCloud += cloud.nextCloud;
                foundCloud = true;
            }
        }

        // Check for pressure data
        for (const auto& pressure : pressures) {
            if (pressure.xPressure == coord.first && pressure.yPressure == coord.second) {
                cityPressure += pressure.nextPressure;
                foundPressure = true;
            }
        }
        bigCounter++;

        // Print debug output
        cout << "(" << coord.first << ", " << coord.second << ") ";
        if (foundCloud) {
            cout << "Cloud: " << cityCloud << " ";
        }
        if (foundPressure) {
            cout << "Pressure: " << cityPressure << " ";
        }
        if (!foundCloud && !foundPressure) {
            cout << "No data ";
            bigCounter--;
        }

        cout << "[BigCounter: "<< bigCounter << "]" << endl;
       
    }

    return vector<pair<int, int>>(uniqueSurroundingCoords.begin(), uniqueSurroundingCoords.end());
}

// Function to display the summary of cities
void displayCitySummary(const vector<CityData>& cities,
                        const vector<CloudData>& clouds,
                        const vector<PressureData>& pressures) {
    // Extract coordinates for each city size
    vector<string> bigCityNames;
    vector<int> bigCityIDs;
    vector<pair<int, int>> bigCities = extractCoordinates(cities, 8, bigCityNames, bigCityIDs);

    char pressureIndex = ' ';
    char cloudIndex = ' ';
    string cityName;
    int cityNumber;
    int surroundingCloud, surroundingPressure;
    double avesCloud;
    double avesPressure;
    // Display summary
    cout << "-------------------------------" << endl;
    cout << "City Summary:\n";
    
    if (!bigCities.empty()) {
    for (size_t i = 0; i < bigCities.size(); ++i) {
        const auto& cityCoord = bigCities[i];
        cityName = bigCityNames[i];
        cityNumber = bigCityIDs[i];

        vector<pair<int, int>> cityCoords = { cityCoord };
        cout << "Big Cities:\n";
        handleCoordinates(bigCities);

        int cityCloud, cityPressure;
        calculateTotals(bigCities, clouds, pressures, cityCloud, cityPressure);
        cout << "City Cloud: " << cityCloud << "\n";
        cout << "City Pressure: " << cityPressure << "\n";

        // Calculate totals for surrounding coordinates
        bigCounter = 0;
        calculateSurrounding3x3(bigCities, clouds, pressures, surroundingCloud, surroundingPressure);

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
        cout << "City Name: " << cityName << endl;
        cout << "City ID: " << cityNumber << endl;
        cout << "Cloud for Surrounding Coordinates: " << surroundingCloud << endl;
        cout << "Pressure for Surrounding Coordinates: " << surroundingPressure << endl;
        cout << "Ave. Cloud Cover (ACC): " << avesCloud << " (" << string(1, cloudIndex) << ")" << endl;
        cout << "Ave. Pressure (AP): " << avesPressure << " (" << string(1, pressureIndex) << ")" << endl;
        rain_prob(cloudIndex, pressureIndex);
        cout << "------------------------------ " << endl;
    }
}


// Example usage
int main() {
    vector<CityData> cities = {
        {1, 1, 8, 3, "Big City"},
        {1, 2, 8, 3, "Big City"},
        {1, 3, 8, 3, "Big City"},
        {2, 1, 8, 3, "Big City"},
        {2, 2, 8, 3, "Big City"},
        {2, 3, 8, 3, "Big City"},
        {3, 1, 8, 3, "Big City"},
        {3, 2, 8, 3, "Big City"},
        {3, 3, 8, 3, "Big City"},
    };
 vector<CloudData> clouds = {
        {0, 0, 41}, {0, 1, 93}, {0, 2, 90}, {0, 3, 24}, {0, 4, 70},
        {0, 5, 39}, {0, 6, 47}, {0, 7, 35}, {0, 8, 83}, {1, 0, 38},
        {1, 1, 66}, {1, 2, 45}, {1, 3, 11}, {1, 4, 53}, {1, 5, 35},
        {1, 6, 88}, {1, 7, 75}, {1, 8, 21}, {2, 0, 56}, {2, 1, 81},
        {2, 2, 34}, {2, 3, 76}, {2, 4, 53}, {2, 5, 44}, {2, 6, 70},
        {2, 7, 38}, {2, 8, 32}, {3, 0, 86}, {3, 1, 13}, {3, 2, 23},
        {3, 3, 93}, {3, 4, 68}, {3, 5, 26}, {3, 6, 53}, {3, 7, 52},
        {3, 8, 29}, {4, 0, 76}, {4, 1, 60}, {4, 2, 43}, {4, 3, 82},
        {4, 4, 40}, {4, 5, 72}, {4, 6, 48}, {4, 7, 29}, {4, 8, 75},
        {5, 0, 16}, {5, 1, 49}, {5, 2, 36}, {5, 3, 53}, {5, 4, 18},
        {5, 0, 16}, {5, 1, 49}, {5, 2, 36}, {5, 3, 53}, {5, 4, 18},
        {5, 5, 47}, {5, 6, 27}, {5, 7, 98}, {5, 8, 78}, {6, 0, 68},
        {6, 1, 63}, {6, 2, 33}, {6, 3, 92}, {6, 4, 27}, {6, 5, 48},
        {6, 6, 13}, {6, 7, 15}, {6, 8, 37}, {7, 0, 47}, {7, 1, 3},
        {7, 2, 8}, {7, 3, 17}, {7, 4, 62}, {7, 5, 62}, {7, 6, 14},
        {7, 7, 35}, {7, 8, 84}, {8, 0, 7}, {8, 1, 23}, {8, 2, 63},
        {8, 3, 24}, {8, 4, 37}, {8, 5, 18}, {8, 6, 44}, {8, 7, 6},
        {8, 8, 18}
    };
    vector<PressureData> pressures = {
        {0, 0, 36}, {0, 1, 32}, {0, 2, 38}, {0, 3, 64}, {0, 4, 9},
        {0, 5, 62}, {0, 6, 56}, {0, 7, 41}, {0, 8, 56}, {1, 0, 24},
        {1, 1, 65}, {1, 2, 27}, {1, 3, 27}, {1, 4, 85}, {1, 5, 83},
        {1, 6, 6}, {1, 7, 38}, {1, 8, 82}, {2, 0, 72}, {2, 1, 42},
        {2, 2, 17}, {2, 3, 15}, {2, 4, 79}, {2, 5, 11}, {2, 6, 10},
        {2, 7, 47}, {2, 8, 39}, {3, 0, 53}, {3, 1, 86}, {3, 2, 33},
        {3, 3, 13}, {3, 4, 15}, {3, 5, 59}, {3, 6, 16}, {3, 7, 39},
        {3, 8, 38}, {4, 0, 15}, {4, 1, 54}, {4, 2, 58}, {4, 3, 84},
        {4, 4, 47}, {4, 5, 78}, {4, 6, 68}, {4, 7, 69}, {4, 8, 25},
        {5, 0, 52}, {5, 1, 36}, {5, 2, 35}, {5, 3, 40}, {5, 4, 65},
        {5, 5, 40}, {5, 6, 83}, {5, 7, 50}, {5, 8, 23}, {6, 0, 27},
        {6, 1, 59}, {6, 2, 42}, {6, 3, 42}, {6, 4, 63}, {6, 5, 51},
        {6, 6, 5}, {6, 7, 90}, {6, 8, 83}, {7, 0, 36}, {7, 1, 53},
        {7, 2, 63}, {7, 3, 77}, {7, 4, 78}, {7, 5, 50}, {7, 6, 86},
        {7, 7, 24}, {7, 8, 33}, {8, 0, 70}, {8, 1, 32}, {8, 2, 71},
        {8, 3, 18}, {8, 4, 29}, {8, 5, 73}, {8, 6, 40}, {8, 7, 80},
        {8, 8, 78}
    };
	    
	// Display city summary
    displayCitySummary(cities, clouds, pressures);

    return 0;
}
