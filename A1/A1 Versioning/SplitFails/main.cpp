#include "algo.cpp"

int main() {
  //Upon program Execution Prompt to read and process the configuration file

  if (!init) {
    choice = 1; // Automatically set to read and process the configuration file
    processOption(choice); // Process the configuration file
    init = true; // Set init to true after processing
  }

  do {
    displayMenu();
    cin >> choice;

    // Clear input buffer in case of invalid input
    if (cin.fail()) {
      cin.clear(); // Clear the error flag
      cin.ignore(numeric_limits < streamsize > ::max(), '\n'); // Discard invalid input
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


void processOption(int choice) {

  switch (choice) {
  case 1:
    // Call function to read and process configuration file
    readConfig();

    break;
  case 2:
    // Call function to display city map
    cout << "----------------------------------------------" << endl;
    cout << "[Displaying city map]" << endl;
    cout << "----------------------------------------------" << endl;
    init2DArray(x, y);
    populateWithCityData(cities);
    display2DArray(x, y);
    deallocateMemory(x, y);
    break;
  case 3:
    // Call function to display cloud coverage map (cloudiness index)
    cout << "----------------------------------------------" << endl;
    cout << "[Displaying cloud coverage map (cloudiness index)]" << endl;
    cout << "----------------------------------------------" << endl;
    init2DArray(x, y);
    populateWithCloudIndexData(clouds);
    display2DArray(x, y);
    deallocateMemory(x, y);
    break;
  case 4:
    // Call function to display cloud coverage map (LHM symbols)
    cout << "----------------------------------------------" << endl;
    cout << "[Displaying cloud coverage map (LHM symbols)]" << endl;
    cout << "----------------------------------------------" << endl;
    init2DArray(x, y);
    populateWithCloudLMHData(clouds);
    display2DArray(x, y);
    deallocateMemory(x, y);
    break;
  case 5:
    // Call function to display atmospheric pressure map (pressure index)
    cout << "----------------------------------------------" << endl;
    cout << "[Displaying atmospheric pressure map (pressure index)]" << endl;
    cout << "----------------------------------------------" << endl;
    init2DArray(x, y);
    populateWithPressureData(pressures);
    display2DArray(x, y);
    deallocateMemory(x, y);
    
    break;
  case 6:
    // Call function to display atmospheric pressure map (LHM symbols)
    cout << "----------------------------------------------" << endl;
    cout << "[Displaying atmospheric pressure map (LHM symbols)]" << endl;
    cout << "----------------------------------------------" << endl;
    init2DArray(x, y);
    populateWithPressureLMHData(pressures);
    display2DArray(x, y);
    deallocateMemory(x, y);
    break;
  case 7:
    // Call function to show weather forecast summary report
    cout << "----------------------------------------------" << endl;
    cout << "[Showing weather forecast summary report]" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Weather Forecast Summary Report" << endl;
    cout << "---------------------------" << endl;
    displayBCSummary(cities, clouds, pressures);
    displayMCSummary(cities, clouds, pressures);
    displaySCSummary(cities, clouds, pressures);

    break;
  case 8:
    // Quit the program
    cout << "Thank you for using Weather Information Processing System, have a nice day!" << endl;
    deallocateMemory(x, y);
    break;
  default:
    cout << "[Invalid input]\n" << endl; // Outputs this if invalid input is keyed
    cin.clear(); // Clear input stream state
    break;
  }
}

void waitForEnter() {
  cout << "Press <Enter> to go back to the main menu...";
  cin.ignore(numeric_limits < streamsize > ::max(), '\n'); // Discard any remaining input
  cin.clear(); // Clear input stream state
  cin.get(); // Wait for user to press Enter
}