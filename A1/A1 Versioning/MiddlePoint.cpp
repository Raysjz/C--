#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct City {
    int x;
    int y;
    int size;
    string name;
};

// Function to calculate the center point of a city type
pair<float, float> calculateCenter(const vector<City>& cities, const string& cityName) {
    int xSum = 0;
    int ySum = 0;
    int count = 0;

    for (const auto& city : cities) {
        if (city.name == cityName) {
            xSum += city.x;
            ySum += city.y;
            count++;
        }
    }

    if (count == 0) {
        throw invalid_argument("No cities of type " + cityName + " found.");
    }

    return {static_cast<float>(xSum) / count, static_cast<float>(ySum) / count};
}

// Function to calculate perimeter coordinates
void calculatePerimeter(const vector<City>& cities, const string& cityName) {
    auto center = calculateCenter(cities, cityName);

    // Determine the size of the perimeter based on city type
    int size;
    if (cityName == "Big_City") {
        size = 5;
    } else if (cityName == "Mid_City") {
        size = 4;
    } else if (cityName == "Small_City") {
        size = 3;
    } else {
        throw invalid_argument("Unknown city type: " + cityName);
    }

    // Compute perimeter coordinates
    cout << "Perimeter for " << cityName << " (" << center.first << ", " << center.second << "):" << endl;
    int halfSize = size / 2;
    
    for (int x = center.first - halfSize; x <= center.first + halfSize; ++x) {
        for (int y = center.second - halfSize; y <= center.second + halfSize; ++y) {
            // Exclude center city coordinates from the perimeter
            if (!(x >= center.first - halfSize + 1 && x <= center.first + halfSize - 1 &&
                  y >= center.second - halfSize + 1 && y <= center.second + halfSize - 1)) {
                cout << "(" << x << ", " << y << ")" << endl;
            }
        }
    }
}

int main() {
    vector<City> cities = {
        {1, 1, 3, "Big_City"},
        {1, 2, 3, "Big_City"},
        {1, 3, 3, "Big_City"},
        {2, 1, 3, "Big_City"},
        {2, 2, 3, "Big_City"},
        {2, 3, 3, "Big_City"},
        {2, 7, 2, "Mid_City"},
        {2, 8, 2, "Mid_City"},
        {3, 1, 3, "Big_City"},
        {3, 2, 3, "Big_City"},
        {3, 3, 3, "Big_City"},
        {3, 7, 2, "Mid_City"},
        {3, 8, 2, "Mid_City"},
        {7, 7, 1, "Small_City"}
    };

    try {
        calculatePerimeter(cities, "Big_City");
        calculatePerimeter(cities, "Mid_City");
        calculatePerimeter(cities, "Small_City");
    } catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
