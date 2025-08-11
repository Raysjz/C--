#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Function to tokenize a string based on a delimiter
vector<string> tokenizeString(string input, string delimiter)
{
    size_t pos = 0;
    string token;
    vector<string> result;

    while ((pos = input.find(delimiter)) != string::npos)
    {
        token = input.substr(0, pos);
        result.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    result.push_back(input);

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

int main()
{
    // Example input strings
    string rangeStr1 = "0-8";
    string rangeStr2 = "0-10";

    // Tokenize the range strings based on the '-' delimiter
    vector<string> tokenStringVector1 = tokenizeString(rangeStr1, "-");
    vector<string> tokenStringVector2 = tokenizeString(rangeStr2, "-");

    // Convert tokens to integers using stoi
    int startRow = stoi(tokenStringVector1[0]);
    int endRow = stoi(tokenStringVector1[1]);
    int startCol = stoi(tokenStringVector2[0]);
    int endCol = stoi(tokenStringVector2[1]);

    // Calculate dimensions based on the ranges
    int numRows = endRow - startRow + 1; // Number of rows
    int numCols = endCol - startCol + 1; // Number of columns

    // Output the calculated dimensions
    cout << "numRows: " << numRows << endl;
    cout << "numCols: " << numCols << endl;

    // Create and populate the 2D array
    vector<vector<int>> array(numRows, vector<int>(numCols));

    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
        }
    }

    // Print the 2D array with borders
    cout << "2D Array:" << endl;
    print2DArray(array);

    return 0;
}

