#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Global variables
int numRows = 0; 
int numCols = 0; 

void readAFile(string filename) {
    fstream inputFile(filename.c_str(), fstream::in);

    cout << endl;
    cout << "Reading contents of file: " << filename << endl;
    cout << endl;

    string aLine;

    while (getline(inputFile, aLine)) {
        cout << aLine << endl;
    }
    cout << endl;
}

vector<string> tokenizeString(const string& input, const string& delimiter) {
    size_t pos = 0;
    string token;
    vector<string> result;
    string s = input;

    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    result.push_back(s);
    
    return result;
}

void print2DArray(const vector<vector<int>>& array) {
    int rows = array.size();
    int cols = (rows > 0) ? array[0].size() : 0;

    
    // Print top border
    cout << setw(5) << " # ";
    for (int i = 0; i < cols; ++i) {
        cout << " # ";
    }
    cout << setw(3) << " # ";
    cout << endl;
    

    // Print row borders and values
    for (int i = 0; i < rows; ++i) {
        cout << setw(2) << (rows - i - 1) << " # ";
        for (int j = 0; j < cols; ++j) {
            cout << setw(2) << " . ";
        }
        cout << " # " << endl;
    }

    // Print bottom border
    cout << setw(5) << " # ";
    for (int i = 0; i < cols; ++i) {
        cout << " # " ;
    }
    cout << setw(3) << " # ";
    cout << endl;
    

    // Print Horizontal header
    cout << "     ";
    for (int i = 0; i < cols; ++i) {
        cout << setw(2) << i << " ";
    }
    cout << endl;
}

int main() {
    bool bEnd = false;  // Control loop termination

    // Main Menu Display
    while (!bEnd) {
        cout << endl;
        cout << "Student ID\t: 550" << endl;
        cout << "Student Name\t: Unknown" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Welcome to Weather Information Processing System!\n" << endl;
        cout << "1) Read in and process a configuration file" << endl;
        cout << "2) Display city map" << endl;
        cout << "3) Display cloud coverage map (cloudiness index)" << endl;
        cout << "4) Display cloud coverage map (LHM symbols)" << endl;
        cout << "5) Display atmospheric pressure map (pressure index)" << endl;
        cout << "6) Display atmospheric pressure map (LHM symbols)" << endl;
        cout << "7) Show weather forecast summary report" << endl;
        cout << "8) Quit\n" << endl;
        cout << "Please enter your choice: ";

        // Get user input
        int userInput;
        cin >> userInput;

        switch (userInput) {
            case 1: {
                cout << endl;
                cout << "----------------------------------------------" << endl;
                cout << "[Read in and process a configuration file]\n";
                cout << "----------------------------------------------" << endl;
                cout << endl;
                cout << "Please enter the configuration file name: ";

                string inputFilename;
                cin >> inputFilename;

                fstream inputFile(inputFilename.c_str(), fstream::in);

                string aLine;
                string rangeStr;
                string rangeStr2;

                cout << endl;
                while (getline(inputFile, aLine)) {
                    size_t pos = aLine.find(".txt"); // Find those files with .txt

                    if (pos != string::npos) 
                        readAFile(aLine);
                    
                    if (aLine.find("GridX_IdxRange") != string::npos) {
                        size_t pos = aLine.find("=");
                        if (pos != string::npos) {
                            rangeStr = aLine.substr(pos + 1);
                            vector<string> tokenStringVector = tokenizeString(rangeStr, "-");

                            // Print tokens for debugging
                            cout << endl;
                            cout << "Tokens for numRows:" << endl;
                            for (const string& token : tokenStringVector) {
                                cout << token << endl;
                            }

                            // Convert tokens to integers
                            int startRow = stoi(tokenStringVector[0]);
                            int endRow = stoi(tokenStringVector[1]);
                            numRows = endRow - startRow ;
                        }
                    }

                    if (aLine.find("GridY_IdxRange") != string::npos) {
                        size_t pos = aLine.find("=");
                        if (pos != string::npos) {
                            rangeStr2 = aLine.substr(pos + 1);
                            vector<string> tokenStringVector = tokenizeString(rangeStr2, "-");

                            // Print tokens for debugging
                            cout << endl;
                            cout << "Tokens for numCols:" << endl;
                            for (const string& token : tokenStringVector) {
                                cout << token << endl;
                            }

                            // Convert tokens to integers
                            int startCol = stoi(tokenStringVector[0]);
                            int endCol = stoi(tokenStringVector[1]);
                            numCols = endCol - startCol ;
                        }
                    }
                }

                // Output the calculated dimensions
                cout << "numRows: " << numRows << endl;
                cout << "numCols: " << numCols << endl;

                // Create and populate the 2D array
                vector<vector<int>> array(numRows, vector<int>(numCols));

                for (int i = 0; i < numRows; ++i) {
                    for (int j = 0; j < numCols; ++j) {
                    }
                }

                // Print the 2D array with borders
                cout << "2D Array:" << endl;
                print2DArray(array);

               

                break;
            }
            case 2: {
                cout << "----------------------------------------------" << endl;
                cout << "[Displaying city map]" << endl;
                cout << "----------------------------------------------" << endl;
                

                break;
            }
            case 3: {
                cout << "[Displaying cloud coverage map (cloudiness index)]" << endl;
                // Add your code for displaying the cloud coverage map (cloudiness index)
                break;
            }
            case 4: {
                cout << "[Displaying cloud coverage map (LHM symbols)]" << endl;
                // Add your code for displaying the cloud coverage map (LHM symbols)
                break;
            }
            case 5: {
                cout << "[Displaying atmospheric pressure map (pressure index)]" << endl;
                // Add your code for displaying the atmospheric pressure map (pressure index)
                break;
            }
            case 6: {
                cout << "[Displaying atmospheric pressure map (LHM symbols)]" << endl;
                // Add your code for displaying the atmospheric pressure map (LHM symbols)
                break;
            }
            case 7: {
                cout << "[Showing weather forecast summary report]" << endl;
                // Add your code for showing the weather forecast summary report
                break;
            }
            case 8: {
                cout << "Thank you for using Weather Information Processing System, have a nice day!" << endl;
                bEnd = true;  // Set to true to end the loop
                break;
            }
            default: {
                cout << "[Invalid input]\n" << endl; // Outputs this if invalid input is keyed
                cin.clear(); // Clear input stream state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Remove remaining text in buffer
                break;
            }
        }
    }

    return 0;
}
