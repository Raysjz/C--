#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

// Define the CityData struct before using it
struct CityData {
    int xCord;
    int yCord;
    int cNumber;
    string name;
    int cSize; // To store the size of the city
};

// Function to tokenize a string based on a delimiter
vector<string> tokenizeString(const string& str, const string& delimiter) {
    vector<string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    tokens.push_back(str.substr(start));
    return tokens;
}

// Function to parse city data from input string
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
        data.name = cityName;
        data.cSize = 0; // Initialize with 0, will be calculated later
    } else {
        cerr << "Unexpected format in parseCityData." << endl;
    }
    return data;
}

// Function to determine city sizes without using unordered_map
void determineCitySizes(vector<CityData>& cities) {
    for (size_t i = 0; i < cities.size(); ++i) {
        int count = 0;
        for (size_t j = 0; j < cities.size(); ++j) {
            if (cities[i].cNumber == cities[j].cNumber && cities[i].name == cities[j].name) {
                count++;
            }
        }
        cities[i].cSize = count;
    }
}

// Example usage
int main() {
    vector<string> inputData = {
        "[2, 8]-1-Tokyo",
        "[2, 2]-2-Beijing",
        "[2, 3]-2-Beijing",
        "[3, 2]-2-Beijing",
        "[3, 3]-2-Beijing",
        "[6, 8]-3-Oslo",
        "[6, 9]-3-Oslo",
        "[6, 10]-3-Oslo",
        "[7, 8]-3-Oslo",
        "[7, 9]-3-Oslo",
        "[7, 10]-3-Oslo",
        "[8, 8]-3-Oslo",
        "[8, 9]-3-Oslo",
        "[8, 10]-3-Oslo",
        "[7, 2]-4-Paris"
    };

    vector<CityData> cities;

    // Parse input data
    for (const auto& data : inputData) {
        cities.push_back(parseCityData(data));
    }

    // Determine city sizes
    determineCitySizes(cities);

    // Output results
    for (const auto& city : cities) {
        cout << "City: " << city.name << " (" << city.xCord << ", " << city.yCord << "), "
             << "City Number: " << city.cNumber << ", "
             << "City Size: " << city.cSize << endl;
    }

    return 0;
}
