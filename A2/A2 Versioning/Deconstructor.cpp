#include <iostream>
#include <vector>
#include <string>

using namespace std;

class ShapeTwoD {
public:
    static int shapeTwoDCount;  // Counter for ShapeTwoD destructors
    virtual ~ShapeTwoD() {
        cout << "ShapeTwoD destructor called" << endl;
        shapeTwoDCount++;
    }
    
    virtual string toString() const = 0; // Pure virtual function
};

int ShapeTwoD::shapeTwoDCount = 0;

class Square : public ShapeTwoD {
public:
    ~Square() override {
        cout << "Square destructor called" << endl;
    }

    string toString() const override {
        return "Square";
    }
};

class Rectangle : public ShapeTwoD {
public:
    ~Rectangle() override {
        cout << "Rectangle destructor called" << endl;
    }

    string toString() const override {
        return "Rectangle";
    }
};

class Circle : public ShapeTwoD {
public:
    ~Circle() override {
        cout << "Circle destructor called" << endl;
    }

    string toString() const override {
        return "Circle";
    }
};

class Cross : public ShapeTwoD {
public:
    ~Cross() override {
        cout << "Cross destructor called" << endl;
    }

    string toString() const override {
        return "Cross";
    }
};

int main() {
    int numShapes = 4;
    ShapeTwoD** shapesArray = new ShapeTwoD*[numShapes];

    shapesArray[0] = new Square();
    shapesArray[1] = new Rectangle();
    shapesArray[2] = new Circle();
    shapesArray[3] = new Cross();

    cout << "Shapes in array:" << endl;
    for (int i = 0; i < numShapes; ++i) {
        cout << i << ": " << shapesArray[i]->toString() << endl;
    }

    // User selects which shape to delete
    int indexToDelete;
    cout << "Enter the index of the shape to delete (0-3): ";
    cin >> indexToDelete;

    if (indexToDelete >= 0 && indexToDelete < numShapes) {
        delete shapesArray[indexToDelete];
        shapesArray[indexToDelete] = nullptr; // Set to nullptr to avoid dangling pointer
    } else {
        cout << "Invalid index!" << endl;
    }

    cout << "Remaining shapes in array:" << endl;
    for (int i = 0; i < numShapes; ++i) {
        if (shapesArray[i]) {
            cout << i << ": " << shapesArray[i]->toString() << endl;
        }
    }

    // Clean up remaining shapes
    for (int i = 0; i < numShapes; ++i) {
        if (shapesArray[i]) {
            delete shapesArray[i];
        }
    }

    delete[] shapesArray;

    // Print the number of ShapeTwoD destructors called
    cout << "ShapeTwoD destructor called " << ShapeTwoD::shapeTwoDCount << " times." << endl;

    return 0;
}
