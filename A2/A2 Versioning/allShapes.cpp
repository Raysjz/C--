#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

// Abstract base class
class ShapeTwoD {
protected:
    string name;
    bool containsWarpSpace;

public:
    ShapeTwoD(string name, bool containsWarpSpace)
        : name(name), containsWarpSpace(containsWarpSpace) {}

    virtual ~ShapeTwoD() {}

    string getName() const {
        return name;
    }

    bool getContainsWarpSpace() const {
        return containsWarpSpace;
    }

    void setName(string name) {
        this->name = name;
    }

    void setContainsWarpSpace(bool containsWarpSpace) {
        this->containsWarpSpace = containsWarpSpace;
    }

    virtual string toString() const {
        stringstream ss;
        ss << "Shape: " << name << ", Contains Warp Space: " << (containsWarpSpace ? "Yes" : "No");
        return ss.str();
    }

    virtual double computeArea() const = 0;
    virtual bool isPointInShape(int x, int y) const = 0;
    virtual bool isPointOnShape(int x, int y) const = 0;
};

// Derived class: Square
class Square : public ShapeTwoD {
private:
    double side;

public:
    Square(string name, bool containsWarpSpace, double side)
        : ShapeTwoD(name, containsWarpSpace), side(side) {}

    double computeArea() const override {
        return side * side;
    }

    bool isPointInShape(int x, int y) const override {
        // Implement point in square logic
        return false;
    }

    bool isPointOnShape(int x, int y) const override {
        // Implement point on square logic
        return false;
    }

    string toString() const override {
        stringstream ss;
        ss << ShapeTwoD::toString() << ", Side: " << side;
        return ss.str();
    }
};

// Derived class: Rectangle
class Rectangle : public ShapeTwoD {
private:
    double width, height;

public:
    Rectangle(string name, bool containsWarpSpace, double width, double height)
        : ShapeTwoD(name, containsWarpSpace), width(width), height(height) {}

    double computeArea() const override {
        return width * height;
    }

    bool isPointInShape(int x, int y) const override {
        // Implement point in rectangle logic
        return false;
    }

    bool isPointOnShape(int x, int y) const override {
        // Implement point on rectangle logic
        return false;
    }

    string toString() const override {
        stringstream ss;
        ss << ShapeTwoD::toString() << ", Width: " << width << ", Height: " << height;
        return ss.str();
    }
};

// Derived class: Circle
class Circle : public ShapeTwoD {
private:
    double radius;

public:
    Circle(string name, bool containsWarpSpace, double radius)
        : ShapeTwoD(name, containsWarpSpace), radius(radius) {}

    double computeArea() const override {
        return M_PI * radius * radius;
    }

    bool isPointInShape(int x, int y) const override {
        // Implement point in circle logic
        return false;
    }

    bool isPointOnShape(int x, int y) const override {
        // Implement point on circle logic
        return false;
    }

    string toString() const override {
        stringstream ss;
        ss << ShapeTwoD::toString() << ", Radius: " << radius;
        return ss.str();
    }
};

// Derived class: Cross
class Cross : public ShapeTwoD {
private:
    double armLength, armWidth;

public:
    Cross(string name, bool containsWarpSpace, double armLength, double armWidth)
        : ShapeTwoD(name, containsWarpSpace), armLength(armLength), armWidth(armWidth) {}

    double computeArea() const override {
        return 2 * armLength * armWidth - armWidth * armWidth;
    }

    bool isPointInShape(int x, int y) const override {
        // Implement point in cross logic
        return false;
    }

    bool isPointOnShape(int x, int y) const override {
        // Implement point on cross logic
        return false;
    }

    string toString() const override {
        stringstream ss;
        ss << ShapeTwoD::toString() << ", Arm Length: " << armLength << ", Arm Width: " << armWidth;
        return ss.str();
    }
};

// Main function to demonstrate polymorphism
int main() {
    vector<ShapeTwoD*> shapes;

    shapes.push_back(new Square("Square1", false, 5.0));
    shapes.push_back(new Rectangle("Rectangle1", true, 4.0, 6.0));
    shapes.push_back(new Circle("Circle1", false, 3.0));
    shapes.push_back(new Cross("Cross1", true, 4.0, 2.0));

    for (const ShapeTwoD* shape : shapes) {
        cout << shape->toString() << endl;
        cout << "Area: " << shape->computeArea() << endl;
    }

    for (ShapeTwoD* shape : shapes) {
        delete shape;
    }

    return 0;
}
