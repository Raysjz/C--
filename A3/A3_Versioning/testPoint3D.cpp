#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

class Point3D {
public:
    Point3D(int x, int y, int z) : x(x), y(y), z(z) {}

    int getX() const { return x; }
    int getY() const { return y; }
    int getZ() const { return z; }

    double getScalarValue() const {
        return sqrt(x * x + y * y + z * z);
    }

    // Define < and > operators
    bool operator<(const Point3D& other) const {
        if (x == other.x) {
            if (y == other.y) return z < other.z;
            return y < other.y;
        }
        return x < other.x;
    }

    bool operator>(const Point3D& other) const {
        if (x == other.x) {
            if (y == other.y) return z > other.z;
            return y > other.y;
        }
        return x > other.x;
    }

    friend ostream& operator<<(ostream& os, const Point3D& point);

private:
    int x, y, z;
};

ostream& operator<<(ostream& os, const Point3D& point) {
    os << "[" << setw(4) << right << fixed << setprecision(0) << point.getX() << "," 
       << setw(5) << right << fixed << setprecision(0) << point.getY() << "," 
       << setw(5) << right << fixed << setprecision(0) << point.getZ() << "]" 
       << "   " << fixed << setprecision(3) << point.getScalarValue();
    return os;
}

int main() {
    vector<Point3D> points = {
        Point3D(-13, 30, 17),
        Point3D(-8, -23, -27),
        Point3D(14, -25, 25),
        Point3D(29, -7, 13),
        Point3D(29, 16, -9)
    };

    auto compareDescending = [](const Point3D& lhs, const Point3D& rhs) {
    if (lhs.getX() != rhs.getX()) return lhs.getX() > rhs.getX();  // Compare X in descending order
    if (lhs.getY() != rhs.getY()) return lhs.getY() > rhs.getY();  // Compare Y in descending order
    return lhs.getZ() > rhs.getZ();  // Compare Z in descending order
};


    // Sort by X descending order
    sort(points.begin(), points.end(), compareDescending);
    cout << "Point3D (Sort by X, Y, Z Descending)" << endl;
    cout << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) 
         << right << "Z" << "    Dist. Fr Origin" << endl
         << "- - - - - - - - - - - - - - - - - - -" << endl;
    for (const auto& point : points) {
        cout << point << endl;
    }

    return 0;
}
