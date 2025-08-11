#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

string** array2D = nullptr;
bool isArrayInitialized = false;

void init2DArray(int col, int row) {
    array2D = new string*[row];
    for (int i = 0; i < row; i++) {
        array2D[i] = new string[col];
        for (int j = 0; j < col; j++) {
            array2D[i][j] = "."; // Initialize all cells with "."
        }
    }
    isArrayInitialized = true;
    cout << "Array initialized to " << row << " x " << col << endl << endl;
}

void populate2DArray(const vector<pair<int, int>>& coordinates) {
    for (const auto& coord : coordinates) {
        int x = coord.first;
        int y = coord.second;
        array2D[y][x] = "X"; // Mark the cross points with "X"
    }
}

void display2DArray(int col, int row) {
    if (!isArrayInitialized) {
        cout << endl;
        cout << "<----Array not initialized. Cannot display---->" << endl;
        return;
    }

    // Print top border
    cout << setw(5) << " # ";
    for (int i = 0; i < col; ++i) {
        cout << " # ";
    }
    cout << setw(3) << " # ";
    cout << endl;

    // Print row borders and values
    for (int i = 0; i < row; ++i) {
        cout << setw(2) << (row - i - 1) << " # ";
        for (int j = 0; j < col; ++j) {
            cout << setw(2) << array2D[row - i - 1][j] << " ";
        }
        cout << " # " << endl;
    }

    // Print bottom border
    cout << setw(5) << " # ";
    for (int i = 0; i < col; ++i) {
        cout << " # ";
    }
    cout << setw(3) << " # ";
    cout << endl;

    // Print Horizontal header
    cout << "     ";
    for (int i = 0; i < col; ++i) {
        cout << setw(2) << i << " ";
    }
    cout << endl;
}

void safelyDeallocateMemory(int col, int row) {
    if (array2D) {
        for (int i = 0; i < row; i++) {
            delete[] array2D[i];
        }
        delete[] array2D;
        array2D = nullptr;
    }
}

int main() {
    int col = 20;
    int row = 20;

    // Adjusted coordinates to form a cross shape
    vector<pair<int, int>> crossCoordinates = {
     //Square
    
      {1, 7}, {1, 6}, {2, 6}, {2, 7}, 
      {6, 13}, {6, 11}, {8, 11}, {8, 13},
       {15, 4}, {15, 1}, {18, 1}, {18, 4},
    
    // Rectangle
        {2, 17}, {2, 15}, {6, 15}, {6, 17},
        {8, 7}, {8, 2}, {9, 2}, {9, 7}, 
        {16, 10}, {16, 7}, {18, 7}, {18, 10}, 
    
    // Circle
        {16, 14}, {11, 11}, {3, 3},
    
        
    };

    init2DArray(col, row);
    populate2DArray(crossCoordinates);
    display2DArray(col, row);
    safelyDeallocateMemory(col, row);

    return 0;
}
