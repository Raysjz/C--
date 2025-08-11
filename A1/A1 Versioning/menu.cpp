#include <iostream>
#include <limits>  // For std::numeric_limits
#include <string>

using namespace std;

// Function prototypes
void displayMenu();
void processOption(int choice);
void waitForEnter();

int main() {
    int choice = 0;

    do {
        displayMenu();
        cin >> choice;

        // Clear input buffer in case of invalid input
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            choice = 0; // Set choice to 0 to prompt user again
        }

        processOption(choice);

        if (choice >= 2 && choice <= 7) {
            waitForEnter();
        }

    } while (choice != 8);

    cout << "Exiting program. Goodbye!" << endl;
    return 0;
}

void displayMenu() {
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

void processOption(int choice) {
    switch (choice) {
        case 1:
            // Call function to read and process configuration file
            cout << "Option 1 selected: Read in and process a configuration file" << endl;
            break;
        case 2:
            // Call function to display city map
            cout << "Option 2 selected: Display city map" << endl;
            break;
        case 3:
            // Call function to display cloud coverage map (cloudiness index)
            cout << "Option 3 selected: Display cloud coverage map (cloudiness index)" << endl;
            break;
        case 4:
            // Call function to display cloud coverage map (LHM symbols)
            cout << "Option 4 selected: Display cloud coverage map (LHM symbols)" << endl;
            break;
        case 5:
            // Call function to display atmospheric pressure map (pressure index)
            cout << "Option 5 selected: Display atmospheric pressure map (pressure index)" << endl;
            break;
        case 6:
            // Call function to display atmospheric pressure map (LHM symbols)
            cout << "Option 6 selected: Display atmospheric pressure map (LHM symbols)" << endl;
            break;
        case 7:
            // Call function to show weather forecast summary report
            cout << "Option 7 selected: Show weather forecast summary report" << endl;
            break;
        case 8:
            // Quit the program
            break;
        default:
            cout << "Invalid choice. Please select a number between 1 and 8." << endl;
            break;
    }
}

void waitForEnter() {
    cout << "Press <Enter> to go back to the main menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any remaining input
    cin.get(); // Wait for user to press Enter
}
