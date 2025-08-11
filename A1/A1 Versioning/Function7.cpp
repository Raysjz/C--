/*-----------------------------------------------------------
---26 Jul 24------Summary for SC & MC & BC-------------------
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

int smallCounter = 0;
int medCounter = 0;
int bigCounter = 0;

void rain_prob(char c, char p) //simple rain probability print function based on the table given by the assignment document
{
    float prob;
    //if statements for every possible LMH combination leading to a computation of rain probability
    if (c == 'H' && p == 'L')
    {
        //90%
        prob = 90;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": "
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
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": "
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
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": "
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
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": "
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
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": "
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
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
    }
    else if (c == 'H' && p == 'H')
    {
        //30%
        prob = 30;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~~" << endl;
        cout << "~~~~" << endl;
    }
    else if (c == 'M' && p == 'H')
    {
        //20%
        prob = 20;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~" << endl;
        cout << "~~~" << endl;
    }
    else if (c == 'L' && p == 'H')
    {
        //10%
        prob = 10;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(4) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~" << endl;
        cout << "~~" << endl;
    }
}


// Function to handle coordinates
void handleCoordinates(const vector<pair<int, int>>& coords) {
    //cout << "Handling coordinates, size: " << coords.size() << "\n";

    if (coords.empty()) {
       // cout << "No coordinates available.\n";
    } else if (coords.size() == 0) {
       // cout << "Single coordinate set:\n";
       // cout << "Coordinate: (" << coords[0].first << ", " << coords[0].second << ")\n";
    } else if (coords.size() == 3) {
       // cout << "Set of 4 coordinates:\n";
        for (const auto& coord : coords) {
        //    cout << "Coordinate: (" << coord.first << ", " << coord.second << ")\n";
        }
    } else if (coords.size() == 8) {
       // cout << "Set of 9 coordinates:\n";
        for (const auto& coord : coords) {
        //    cout << "Coordinate: (" << coord.first << ", " << coord.second << ")\n";
        }
    } else {
       // cout << "Unsupported number of coordinates: " << coords.size() << "\n";
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
    
   /* // Debugging output
    cout << "Extracted " << coords.size() << " coordinates:\n";
    for (const auto& coord : coords) {
        cout << "(" << coord.first << ", " << coord.second << ")\n";
    }
    */
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

// Function to compute surrounding coordinates
vector<pair<int, int>> getSurrounding(int x, int y) {
    return {
        {x, y - 1}, {x, y + 1}, // North, South
        {x - 1, y}, {x + 1, y}, // West, East
        {x - 1, y - 1}, {x + 1, y - 1}, // North-West, North-East
        {x - 1, y + 1}, {x + 1, y + 1}  // South-West, South-East
    };
}

// Function to calculate Cloud and pressure for surrounding coordinates
void calculateSurrounding1x1(const vector<pair<int, int>>& smallCities,
                                const vector<CloudData>& clouds,
                                const vector<PressureData>& pressures,
                                int& cityCloud, int& cityPressure) {
    cityCloud = 0;
    cityPressure = 0;

    for (const auto& city : smallCities) {
        vector<pair<int, int>> surroundingCoords = getSurrounding(city.first, city.second);

        for (const auto& coord : surroundingCoords) {
            bool foundCloud = false;
            bool foundPressure = false;

            for (const auto& cloud : clouds) {
                if (cloud.xCloud == coord.first && cloud.yCloud == coord.second) {
                    foundCloud = true;
                    cityCloud += cloud.nextCloud;
                }
            }

            for (const auto& pressure : pressures) {
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
vector<pair<int, int>> calculateSurrounding2x2(const vector<pair<int, int>>& cities,
                                               const vector<CloudData>& clouds,
                                               const vector<PressureData>& pressures,
                                               int& cityCloud, int& cityPressure) {
    cityCloud = 0;
    cityPressure = 0;

    vector<pair<int, int>> allSurroundingCoords;
    vector<pair<int, int>> uniqueSurroundingCoords;

    // Iterate through each city and get surrounding coordinates
    for (const auto& city : cities) {
        vector<pair<int, int>> surroundingCoords = getSurrounding(city.first, city.second);
        allSurroundingCoords.insert(allSurroundingCoords.end(), surroundingCoords.begin(), surroundingCoords.end());
    }

    // Remove duplicates manually
    for (const auto& coord : allSurroundingCoords) {
        if (find(uniqueSurroundingCoords.begin(), uniqueSurroundingCoords.end(), coord) == uniqueSurroundingCoords.end()) {
            uniqueSurroundingCoords.push_back(coord);
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

    return vector<pair<int, int>>(uniqueSurroundingCoords.begin(), uniqueSurroundingCoords.end());
}


void displaySCSummary(const vector<CityData>& cities,
                        const vector<CloudData>& clouds,
                        const vector<PressureData>& pressures) {
    vector<string> smallCityNames;
    vector<int> smallCityIDs;
    vector<pair<int, int>> smallCities = extractCoordinates(cities, 0, smallCityNames, smallCityIDs);

    char pressureIndex = ' ';
    char cloudIndex = ' ';
    cout << endl;
    cout << "Small_City Summary: " << endl;

        if (!smallCities.empty()) {
        for (size_t i = 0; i < smallCities.size(); ++i) {
            const auto& cityCoord = smallCities[i];
            const string& cityName = smallCityNames[i];
            const int cityNumber = smallCityIDs[i];

            vector<pair<int, int>> cityCoords = { cityCoord };
            handleCoordinates(cityCoords);

            int cityCloud, cityPressure;
            calculateTotals(cityCoords, clouds, pressures, cityCloud, cityPressure);
            
            int surroundingCloud, surroundingPressure;
            smallCounter = 0; // Reset counter for each city
            calculateSurrounding1x1(cityCoords, clouds, pressures, surroundingCloud, surroundingPressure);

            int totalscCloud = cityCloud + surroundingCloud;
            int totalscPressure = cityPressure + surroundingPressure;
            double avesCloud = ((cityCloud + surroundingCloud) / static_cast<double>(smallCounter));
            double avesPressure = ((cityPressure + surroundingPressure) / static_cast<double>(smallCounter));

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
            cout << "City Name" <<  right << setw(5) << ": " << cityName << endl;
            cout << "City ID " <<  right << setw(6) << ": " << cityNumber << endl;
            //cout << "City Clouds: " << cityCloud << endl;
            //cout << "City Pressure: " << cityPressure << endl;
            //cout << "Cloud for Surrounding Coordinates: " << surroundingCloud << endl;
            //cout << "Pressure for Surrounding Coordinates: " << surroundingPressure << endl;
            //cout << "Total Cloud: " << totalscCloud << endl;
            //cout << "Total Pressure: " << totalscPressure << endl;
            cout << "Ave. Cloud Cover (ACC) " <<  right << setw(6) << ": " << avesCloud << " (" << string(1, cloudIndex) << ")" << endl;
            cout << "Ave. Pressure" << right << setw(8) << "(AP)" <<  right << setw(8) << ": "<< avesPressure  << " (" << string(1, pressureIndex) << ")" << endl;
            rain_prob(cloudIndex, pressureIndex);
         //   cout << "------------------------------" << endl;
        }
    }
    
}


void displayMCSummary(const vector<CityData>& cities,
                        const vector<CloudData>& clouds,
                        const vector<PressureData>& pressures) {
    vector<string> mediumCityNames;
    vector<int> mediumCityIDs;
    vector<pair<int, int>> mediumCities = extractCoordinates(cities, 3, mediumCityNames, mediumCityIDs);


    char pressureIndex = ' ';
    char cloudIndex = ' ';
    string cityName;
    int cityNumber;
    int surroundingCloud, surroundingPressure;
    double avesCloud;
    double avesPressure;
    //cout << "-------------------------------" << endl;
    cout << endl;
    cout << "Mid_City Summary: " << endl;

    if (!mediumCities.empty()) {
    for (size_t i = 0; i < mediumCities.size(); ++i) {
        const auto& cityCoord = mediumCities[i];
        cityName = mediumCityNames[i];
        cityNumber = mediumCityIDs[i];

        vector<pair<int, int>> cityCoords = { cityCoord };
        handleCoordinates(cityCoords);

        int cityCloud, cityPressure;
        calculateTotals(mediumCities, clouds, pressures, cityCloud, cityPressure);
        
        //cout << "City Cloud: " << cityCloud << "\n";
        //cout << "City Pressure: " << cityPressure << "\n";

        // Calculate totals for surrounding coordinates
        
        medCounter = 0; // Reset counter for each city
        calculateSurrounding2x2(mediumCities, clouds, pressures, surroundingCloud, surroundingPressure);

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
        cout << "City Name" <<  right << setw(5) << ": " << cityName << endl;
        cout << "City ID " <<  right << setw(6) << ": " << cityNumber << endl;
        //cout << "Cloud for Surrounding Coordinates: " << surroundingCloud << endl;
        //cout << "Pressure for Surrounding Coordinates: " << surroundingPressure << endl;
        cout << "Ave. Cloud Cover (ACC) " <<  right << setw(6) << ": " << avesCloud << " (" << string(1, cloudIndex) << ")" << endl;
        cout << "Ave. Pressure" << right << setw(8) << "(AP)" <<  right << setw(8) << ": "<< avesPressure  << " (" << string(1, pressureIndex) << ")" << endl;
        rain_prob(cloudIndex, pressureIndex);
      //  cout << "------------------------------ " << endl;
    }
}


// Function to display the summary of cities
void displayBCSummary(const vector<CityData>& cities,
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
    //cout << "-------------------------------" << endl;
    cout << endl;
    cout << "Big_City Summary:\n";
    
    if (!bigCities.empty()) {
    for (size_t i = 0; i < bigCities.size(); ++i) {
        const auto& cityCoord = bigCities[i];
        cityName = bigCityNames[i];
        cityNumber = bigCityIDs[i];

        vector<pair<int, int>> cityCoords = { cityCoord };
        handleCoordinates(bigCities);

        int cityCloud, cityPressure;
        calculateTotals(bigCities, clouds, pressures, cityCloud, cityPressure);
        //cout << "City Cloud: " << cityCloud << "\n";
        //cout << "City Pressure: " << cityPressure << "\n";

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
        cout << "City Name" <<  right << setw(5) << ": " << cityName << endl;
        cout << "City ID " <<  right << setw(6) << ": " << cityNumber << endl;
        //cout << "Cloud for Surrounding Coordinates: " << surroundingCloud << endl;
         //cout << "Pressure for Surrounding Coordinates: " << surroundingPressure << endl;
        cout << "Ave. Cloud Cover (ACC) " <<  right << setw(6) << ": " << avesCloud << " (" << string(1, cloudIndex) << ")" << endl;
        cout << "Ave. Pressure" << right << setw(8) << "(AP)" <<  right << setw(8) << ": "<< avesPressure  << " (" << string(1, pressureIndex) << ")" << endl;
        rain_prob(cloudIndex, pressureIndex);
       // cout << "------------------------------ " << endl;
    }
}


// Example usage
int main() {
    vector<CityData> cities = {
    {2, 8, 0, 1, "Tokyo"},
    {2, 2, 3, 2, "Beijing"},
    {2, 3, 3, 2, "Beijing"},
    {3, 2, 3, 2, "Beijing"},
    {3, 3, 3, 2, "Beijing"},
    {6, 8, 8, 3, "Oslo"},
    {6, 9, 8, 3, "Oslo"},
    {6, 10, 8, 3, "Oslo"},
    {7, 8, 8, 3, "Oslo"},
    {7, 9, 8, 3, "Oslo"},
    {7, 10, 8, 3, "Oslo"},
    {8, 8, 8, 3, "Oslo"},
    {8, 9, 8, 3, "Oslo"},
    {8, 10, 8, 3, "Oslo"},
    {7, 2, 0, 4, "Paris"}
    };
    
    vector<CloudData> clouds = {
    {0, 0, 47}, {0, 1, 26}, {0, 2, 51}, {0, 3, 29}, {0, 4, 91},
    {0, 5, 78}, {0, 6, 62}, {0, 7, 70}, {0, 8, 31}, {0, 9, 85},
    {0, 10, 29}, {1, 0, 10}, {1, 1, 25}, {1, 2, 13}, {1, 3, 64},
    {1, 4, 69}, {1, 5, 36}, {1, 6, 33}, {1, 7, 51}, {1, 8, 83},
    {1, 9, 50}, {1, 10, 24}, {2, 0, 72}, {2, 1, 16}, {2, 2, 43},
    {2, 3, 69}, {2, 4, 12}, {2, 5, 35}, {2, 6, 95}, {2, 7, 33},
    {2, 8, 14}, {2, 9, 65}, {2, 10, 23}, {3, 0, 66}, {3, 1, 13},
    {3, 2, 39}, {3, 3, 30}, {3, 4, 18}, {3, 5, 16}, {3, 6, 89},
    {3, 7, 74}, {3, 8, 64}, {3, 9, 54}, {3, 10, 25}, {4, 0, 72},
    {4, 1, 45}, {4, 2, 54}, {4, 3, 47}, {4, 4, 54}, {4, 5, 32},
    {4, 6, 15}, {4, 7, 67}, {4, 8, 50}, {4, 9, 77}, {4, 10, 80},
    {5, 0, 69}, {5, 1, 70}, {5, 2, 41}, {5, 3, 53}, {5, 4, 81},
    {5, 5, 42}, {5, 6, 17}, {5, 7, 29}, {5, 8, 20}, {5, 9, 19},
    {5, 10, 38}, {6, 0, 28}, {6, 1, 59}, {6, 2, 60}, {6, 3, 66},
    {6, 4, 49}, {6, 5, 12}, {6, 6, 69}, {6, 7, 37}, {6, 8, 36},
    {6, 9, 8}, {6, 10, 12}, {7, 0, 16}, {7, 1, 79}, {7, 2, 78},
    {7, 3, 48}, {7, 4, 32}, {7, 5, 50}, {7, 6, 50}, {7, 7, 58},
    {7, 8, 59}, {7, 9, 47}, {7, 10, 22}, {8, 0, 42}, {8, 1, 58},
    {8, 2, 76}, {8, 3, 73}, {8, 4, 9}, {8, 5, 12}, {8, 6, 28},
    {8, 7, 18}, {8, 8, 49}, {8, 9, 21}, {8, 10, 58}
    };
    vector<PressureData> pressures = {
    {0, 0, 24}, {0, 1, 39}, {0, 2, 27}, {0, 3, 67}, {0, 4, 49},
    {0, 5, 59}, {0, 6, 78}, {0, 7, 72}, {0, 8, 58}, {0, 9, 46},
    {0, 10, 51}, {1, 0, 37}, {1, 1, 21}, {1, 2, 67}, {1, 3, 68},
    {1, 4, 12}, {1, 5, 17}, {1, 6, 31}, {1, 7, 63}, {1, 8, 73},
    {1, 9, 73}, {1, 10, 23}, {2, 0, 71}, {2, 1, 45}, {2, 2, 14},
    {2, 3, 43}, {2, 4, 55}, {2, 5, 8}, {2, 6, 20}, {2, 7, 68},
    {2, 8, 69}, {2, 9, 93}, {2, 10, 17}, {3, 0, 64}, {3, 1, 11},
    {3, 2, 23}, {3, 3, 41}, {3, 4, 73}, {3, 5, 79}, {3, 6, 58},
    {3, 7, 53}, {3, 8, 88}, {3, 9, 48}, {3, 10, 13}, {4, 0, 87},
    {4, 1, 17}, {4, 2, 77}, {4, 3, 88}, {4, 4, 83}, {4, 5, 88},
    {4, 6, 45}, {4, 7, 66}, {4, 8, 58}, {4, 9, 75}, {4, 10, 8},
    {5, 0, 69}, {5, 1, 52}, {5, 2, 27}, {5, 3, 28}, {5, 4, 55},
    {5, 5, 73}, {5, 6, 23}, {5, 7, 23}, {5, 8, 39}, {5, 9, 25},
    {5, 10, 27}, {6, 0, 21}, {6, 1, 51}, {6, 2, 54}, {6, 3, 10},
    {6, 4, 77}, {6, 5, 15}, {6, 6, 60}, {6, 7, 16}, {6, 8, 38},
    {6, 9, 9}, {6, 10, 30}, {7, 0, 38}, {7, 1, 19}, {7, 2, 10},
    {7, 3, 15}, {7, 4, 74}, {7, 5, 83}, {7, 6, 52}, {7, 7, 43},
    {7, 8, 13}, {7, 9, 19}, {7, 10, 31}, {8, 0, 75}, {8, 1, 15},
    {8, 2, 53}, {8, 3, 35}, {8, 4, 16}, {8, 5, 53}, {8, 6, 64},
    {8, 7, 60}, {8, 8, 30}, {8, 9, 38}, {8, 10, 23}
    };
	    
	// Display city summary
    displayBCSummary(cities, clouds, pressures);
    displayMCSummary(cities, clouds, pressures);
    displaySCSummary(cities, clouds, pressures);
    
    


    return 0;
}



/*
//----------------------------
SC , MC , BC Data
//-----------------------------

vector<CityData> cities = {
        {1, 1, 8, 3, "Big_City"},
        {1, 2, 8, 3, "Big_City"},
        {1, 3, 8, 3, "Big_City"},
        {2, 1, 8, 3, "Big_City"},
        {2, 2, 8, 3, "Big_City"},
        {2, 3, 8, 3, "Big_City"},
        {2, 7, 3, 2, "Mid_City"},
        {2, 8, 3, 2, "Mid_City"},
        {3, 1, 8, 3, "Big_City"},
        {3, 2, 8, 3, "Big_City"},
        {3, 3, 8, 3, "Big_City"},
        {3, 7, 3, 2, "Mid_City"},
        {3, 8, 3, 2, "Mid_City"},
        {7, 7, 0, 1, "Small_City"},
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


*/