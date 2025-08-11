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

vector<string> tokenizeString(string input, string delimiter) {
    size_t pos = 0;
    string token;
    vector<string> result;

    while ((pos = input.find(delimiter)) != string::npos) {
        token = input.substr(0, pos);
        result.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    result.push_back(input);

    return result;
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
                string xRange;
                string yRange;

                cout << endl;
                while (getline (inputFile, aLine))
                    {
                        cout << aLine << endl; //Print out file lines

                        size_t pos = aLine.find(".txt"); //Find those files with .txt

                        if (pos != string::npos)
                        readAFile (aLine);

                        if (aLine.find("Range") != string::npos) {
                          size_t pos = aLine.find("=");
                            if (pos != string::npos) 
                            {   
                                
                                xRange = aLine.substr(pos + 1);
                                vector<string> tokenStringVector = tokenizeString (xRange, "=");
                                cout << endl;
                                for (int i=0; i<tokenStringVector.size(); i++)
                                    cout << tokenStringVector [i] << endl;
                                cout << endl;
                                //------------------------------
                                tokenStringVector.clear();
                                tokenStringVector = tokenizeString (yRange, "-");
                                cout << endl;
                                for (int i=0; i<tokenStringVector.size(); i++)
                                    cout << tokenStringVector [i] << endl;
                                cout << endl;

                            }
                    
                        }
                    }
                }
                
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
