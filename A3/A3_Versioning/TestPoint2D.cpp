#include <iostream>
#include <vector>
#include <fstream>    // For file operations
#include <iostream>   // For standard input and output
#include <limits>     // For numeric limits
#include <string>     // For string operations
#include <algorithm>  // For find function

#include "Point2D.h"

using namespace std;

int main() {
    // Create a vector of Point2D objects
    vector<Point2D> points;
    //4 containers for each class

    // Add Point2D objects to the vector
    points.emplace_back(1, 2);
    points.emplace_back(3, 4);
    points.emplace_back(5, 6);

    // Access and manipulate elements in the vector
    for (auto& point : points) {
        cout << "Point(" << point.getX() << ", " << point.getY() << ") - Distance from Origin: " << point.getScalarValue() << endl;
    }

    // Example of modifying an element
    points[0].setX(10);
    points[0].setY(20);

    // Print updated vector
    cout << "After modification:\n";
    for (auto& point : points) {
        cout << "Point(" << point.getX() << ", " << point.getY() << ") - Distance from Origin: " << point.getScalarValue() << endl;
    }

    return 0;
}
