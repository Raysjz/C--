#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct CityData {
    int x;
    int y;
    int value;
    string name;
};

vector<string> tokenizeString (string input, string delimiter)
{
	size_t pos = 0;
	string token;
	vector<string> result;

	while ((pos = input.find(delimiter)) != string::npos) 
	{
    	token = input.substr(0, pos);
    	result.push_back (token);
		input.erase(0, pos + delimiter.length());
	}

	result.push_back (input);

	return (result); 
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

        data.x = stoi(coordinate_parts[0]);
        data.y = stoi(coordinate_parts[1]);
        data.value = stoi(value);
        data.name = city_name;
    } else {
        cerr << "Unexpected format." << endl;
    }

    return data;
}

void readCityName() {
    cout << endl;
    cout << "----------------------------------------------" << endl;
    cout << "[Read in and process a citylocation file]" << endl;
    cout << "----------------------------------------------" << endl;
    cout << endl;
    cout << "Please enter the citylocation file name (e.g.citylocation): ";

    string inputFilename;
    cin >> inputFilename;
    inputFilename += ".txt";

    ifstream inputFile(inputFilename.c_str());
    if (!inputFile) {
        cerr << "Failed to open " << inputFilename << endl;
        return;
    }

    vector<CityData> cities; // Vector to store CityData structs
    string aLine;

    while (getline(inputFile, aLine)) {
        if (!aLine.empty()) {
            CityData city = parseCityData(aLine);
            cities.push_back(city); // Store each CityData struct in the vector
        }
    }

    inputFile.close(); // Close the file after reading

    // Output the stored city data
    for (const auto& city : cities) {
        cout << "x: " << city.x << endl;
        cout << "y: " << city.y << endl;
        cout << "Value: " << city.value << endl;
        cout << "City Name: " << city.name << endl;
        cout << "--------------------" << endl;
    }
}

int main() {
    readCityName(); // Call the function to read and process the city location file

    return 0;
}
