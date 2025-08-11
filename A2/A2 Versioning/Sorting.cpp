#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

// Base class and derived classes
class ShapeTwoD {
public:
    virtual double getArea() const = 0;
    virtual string toString() const = 0;
};

// Example derived class
class Circle : public ShapeTwoD {
    double area;
    string name;
    string specType;
    vector<pair<int, int>> vertices;
public:
    Circle(double a, const string& n, const string& s) : area(a), name(n), specType(s) {}
    double getArea() const override { return area; }
    string toString() const override {
        ostringstream oss;
        oss << "Name  : " << name << "\n";
        oss << "Special Type : " << specType << "\n";
        oss << "Area : " << area << " units square\n";
        oss << "Vertices : \n";
        for (size_t i = 0; i < vertices.size(); ++i) {
            oss << "Point[" << i << "] : (" << vertices[i].first << ", " << vertices[i].second << ")\n";
        }
        oss << "\nPoints on Perimeter : None!" << "\n";
        oss << "\nPoints within shape : None!" << "\n";
        return oss.str();
    }
};

// Sorting function
void sortAscending(vector<ShapeTwoD *> &Shapes) {
    sort(Shapes.begin(), Shapes.end(), [](ShapeTwoD *lhs, ShapeTwoD *rhs) {
        return lhs->getArea() < rhs->getArea();
    });
}

// Descending sort using comparator of lambda
void sortDescending(vector<ShapeTwoD *> Shapes) {
  sort(Shapes.begin(), Shapes.end(), [](ShapeTwoD *lhs, ShapeTwoD *rhs) {
    return lhs->getArea() > rhs->getArea();
  });
}

void displayAscending(vector<ShapeTwoD *> Shapes)
{
    cout << "Display Ascending" << endl;
    sortAscending(Shapes);
    for (int i = 0; i < Shapes.size(); i++) {
    cout << Shapes[i]->toString() << endl << endl;
  }
}

void displayDescending(vector<ShapeTwoD *> Shapes)
{
    cout << "Displaying Descending" << endl;
    sortDescending(Shapes);
    for (int i = 0; i < Shapes.size(); i++) {
    cout << Shapes[i]->toString() << endl << endl;
  }
}


// Output to file
void outputToFile(const vector<ShapeTwoD *> &Shapes, const string &filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    for (const auto &Shape : Shapes) {
        outFile << Shape->toString() << endl << endl;
    }
}

// Output function
void outputAscending(vector<ShapeTwoD *> &Shapes, const string &filename) {
    vector<ShapeTwoD *> tempShapes = Shapes;  // Create a temporary vector

    sortAscending(tempShapes);  // Sort the temporary vector
    cout << "Output Ascending.txt" << endl;

    // Output the sorted shapes to the console
    for (const auto &Shape : tempShapes) {
        cout << Shape->toString() << endl << endl;
    }

    // Output the sorted shapes to a file
    outputToFile(tempShapes, filename);
}

// Sort by area (descending)
void outputDescending(vector<ShapeTwoD *> Shapes, string filename) {
   vector<ShapeTwoD *> tempShapes = Shapes;  // Create a temporary vector

  sortDescending(tempShapes);  // Sort the shapes first

  cout << "Output Descending.txt" << endl;
  for (const auto &Shape : tempShapes) {
        cout << Shape->toString() << endl << endl;
    }
    outputToFile(tempShapes, filename);  // Output the sorted shapes to a file


  
}

int main() {
    vector<ShapeTwoD *> shapes = {
        new Circle(28.27, "circle", "NS"),
        new Circle(12.57, "circle", "WS"),
        new Circle(3.14, "circle", "WS")
    };

    //displayAscending(shapes);
    outputAscending(shapes, "Asc_shapes.txt");
    cout << "--------------------------------------" << endl;
    //displayDescending(shapes);
    outputDescending(shapes, "Dsc_shapes.txt");

 

    // Clean up
    for (auto shape : shapes) {
        delete shape;
    }

    return 0;
}
