#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

// Global variables
string ** array2D = nullptr;
vector<string> tokenizeString(string input, string delimiter);
int x;
int y;
bool isArrayInitialized;

// Global Calls
void readAFile(string filename);
void displayMenu();
void readConfig();

void init2DArray(int,int);
void populate2DArray(int,int);
void display2DArray(int,int);
void safelyDeallocateMemory(int,int);
void displayMapData();   



int main() { //main
    
    bool bEnd = false;  // Control loop termination

    // Main Menu Display
    while (!bEnd) {
        displayMenu();

        // Get user input
        int userInput;
        cin >> userInput;

        switch (userInput) {
            case 1: {
                readConfig();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Removes remaining text in buffer
                break;
            }
            case 2: {
                cout << "----------------------------------------------" << endl;
                cout << "[Displaying city map]" << endl;
                cout << "----------------------------------------------" << endl;
                

                display2DArray(x,y);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Removes remaining text in buffer

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
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Removes remaining text in buffer
                safelyDeallocateMemory(x, y);
                break;
            }
        }
    }

    return 0;
} //main 

void displayMenu() 
{ // Menu Display 
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
}

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


void readAFile(string filename) 
{
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


void readConfig(){ // start of readconfig
   //Output Message
                cout << endl;
                cout << "----------------------------------------------" << endl;
                cout << "[Read in and process a configuration file]\n";
                cout << "----------------------------------------------" << endl;
                cout << endl;
                cout << "Please enter the configuration file name(eg config): ";

                //Local Variable
                string inputFilename;

                // when prompted, please type in 'config'
                cin >> inputFilename;
                inputFilename = inputFilename + ".txt";

                fstream inputFile(inputFilename.c_str(), fstream::in);

                string aLine;
                vector<string> tempStr;
                vector<string> tempStr2;
                string temps;


                cout << endl;
                while (getline(inputFile, aLine)) 
                {   //Reading output of file
                    cout << aLine << endl;

                // -----------------------------------------------
                //  Extracting Map Data for Dimensions
                    tempStr = tokenizeString(aLine,"=");
                    if(tempStr[0] == "GridX_IdxRange")
                    {
                        temps = tempStr[1];
                        tempStr2 = tokenizeString(aLine,"-");
                        x = stoi(tempStr2[1]) + 1;
                        cout << "Reading in x variables : " << tempStr[1] << "... done!" << endl;
                     
                    }
                // -----------------------------------------------
                    if(tempStr[0] == "GridY_IdxRange") 
                    {
                        temps = tempStr[1];
                        tempStr2 = tokenizeString(aLine,"-");
                        y = stoi(tempStr2[1]) + 1;
                        cout << "Reading in y variables : " << tempStr[1] << "... done!" << endl;

                    }
                        if (x > 0 && y > 0) {
                        init2DArray(x, y); //Init Array
                        populate2DArray(x, y); //Populate Array
                        isArrayInitialized = true;
                    }

                // -----------------------------------------------     
                    size_t pos = aLine.find(".txt");

                    if (pos != string::npos){
                        readAFile (aLine);
                    }
                        
                }   

}   // end of readconfig           

void init2DArray(int col, int row)
{
	array2D = new string * [row]; //Dynamically create a 1D array row string

	for(int i=0 ; i < row ; i++)
		array2D[i] = new string [col]; //Dynamically create second col

}

void populate2DArray(int col , int row)
{
	for (int i =(row-1); i >=0 ; i--) //Changes made (2.5)
	{
		for(int j=0; j < col ; j++)
		{
			ostringstream oss;
			oss << "x" << j+1 << "y" << i+1; //Changes made (2.5)

			array2D [i] [j] = oss.str();
		}
	}
}

void display2DArray(int col, int row)
{
    if(!isArrayInitialized){
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
            cout << setw(2) << " . ";
        }
        cout << " # " << endl;
    }

    // Print bottom border
    cout << setw(5) << " # ";
    for (int i = 0; i < col; ++i) {
        cout << " # " ;
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

void safelyDeallocateMemory (int col , int row)
{
	if(col <=0)
		return;
	for (int i=0; i<row ; i++)
		delete [] array2D[i];

	delete [] array2D;
}



void displayMapData()
{
    cout << "----------------------------------------------" << endl;
    cout << "[Displaying city map]" << endl;
    cout << "----------------------------------------------" << endl;

    
}