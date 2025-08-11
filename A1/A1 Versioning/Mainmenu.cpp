#include <iostream>

using namespace std;

void displayMenu() {
    cout << "Student ID: [Your ID]" << endl;
    cout << "Student Name: [Your Name]" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Weather processing system" << endl;
    cout << endl;
    cout << "1) Read in and process a configuration file" << endl;
    cout << "2) Display city map" << endl;
    cout << "3) Display cloud coverage map (cloudiness index)" << endl;
    cout << "4) Display cloud coverage map (LMH symbols)" << endl;
    cout << "5) Display atmospheric pressure map (pressure index)" << endl;
    cout << "6) Display atmospheric pressure map (LMH symbols)" << endl;
    cout << "7) Show Weather forecast summary report" << endl;
    cout << "8) Quit" << endl;
}

int main() {
    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Reading and processing configuration file..." << endl;
                // Add your code for reading and processing the configuration file
                break;
            case 2:
                cout << "Displaying city map..." << endl;
                // Add your code for displaying the city map
                break;
            case 3:
                cout << "Displaying cloud coverage map (cloudiness index)..." << endl;
                // Add your code for displaying the cloud coverage map (cloudiness index)
                break;
            case 4:
                cout << "Displaying cloud coverage map (LMH symbols)..." << endl;
                // Add your code for displaying the cloud coverage map (LMH symbols)
                break;
            case 5:
                cout << "Displaying atmospheric pressure map (pressure index)..." << endl;
                // Add your code for displaying the atmospheric pressure map (pressure index)
                break;
            case 6:
                cout << "Displaying atmospheric pressure map (LMH symbols)..." << endl;
                // Add your code for displaying the atmospheric pressure map (LMH symbols)
                break;
            case 7:
                cout << "Showing weather forecast summary report..." << endl;
                // Add your code for showing the weather forecast summary report
                break;
            case 8:
                cout << "Quitting..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
        cout << endl;
    } while (choice != 8);

    return 0;
}
