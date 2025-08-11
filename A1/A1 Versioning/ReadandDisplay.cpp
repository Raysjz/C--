#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void readAndDisplay(string filename) {
    ifstream inputFile;
    inputFile.open(filename.c_str());

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string aLine;
    while (getline(inputFile, aLine)) {
        cout << aLine << endl;
    }

    inputFile.close();
}

int main() {
    // Example usage
    cout << "Enter configuration file name: ";
    string filename;
    cin >> filename;

    readAndDisplay(filename);

    return 0;
}
