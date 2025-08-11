#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;


struct CityData {
    int x;
    int y;
    int value;
    string name;
};

vector<string> tokenizeString(const string& input, const string& delimiter) {
    vector<string> tokens;
    size_t start = 0, end = 0;
    while ((end = input.find(delimiter, start)) != string::npos) {
        tokens.push_back(input.substr(start, end - start));
        start = end + delimiter.length();
    }
    tokens.push_back(input.substr(start));
    return tokens;
}

CityData parseCityData(const string& input) {
    CityData data;
    vector<string> parts = tokenizeString(input, "-");

    if (parts.size() == 3) {
        string coordinates = parts[0];
        string value = parts[1];
        string city_name = parts[2];

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

int main() {
    string input = "[1, 1]-3-Big_City";
    CityData city = parseCityData(input);

    cout << "x: " << city.x << endl;
    cout << "y: " << city.y << endl;
    cout << "Value: " << city.value << endl;
    cout << "City Name: " << city.name << endl;

    return 0;
}
