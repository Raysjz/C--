#ifndef ALGO_H
#define ALGO_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <iomanip>
#include <set> 
#include <algorithm> 

using namespace std;

// Global variables
extern string ** array2D;
extern bool init;
extern int choice;
extern int fileCounter;
extern int x;
extern int y;
extern string cLine;
extern int smallCounter;
extern int medCounter;
extern int bigCounter;
extern vector<string> tokenizeString(string input, string delimiter);
extern vector<CityData> cities;
extern vector<CloudData> clouds;
extern vector<PressureData> pressures;

// Struct definitions
struct CityData {
    int xCord;
    int yCord;
    int cSize; // City size
    int cNumber;
    string cName;
};

struct CloudData {
    int xCloud;
    int yCloud;
    int nextCloud;
};

struct PressureData {
    int xPressure;
    int yPressure;
    int nextPressure;
};

// Function declarations
void displayMenu();
void processOption(int choice);
void waitForEnter();
void readConfig();
void readAFile(string & filename, int fileCounter);

CityData parseCityData(string & input);
CloudData parseCloudData(string & input);
PressureData parsePressureData(string & input);
void determineCitySizes(vector<CityData> & cities);
void setValueAt(int col, int row, int & value);
void setValueLMH(int col, int row, string & valueStr);
void populateWithCityData(vector<CityData> & cities);
void populateWithCloudIndexData(vector<CloudData> & clouds);
void populateWithCloudLMHData(vector<CloudData> & clouds);
void populateWithPressureData(vector<PressureData> & pressures);
void populateWithPressureLMHData(vector<PressureData> & pressures);
void init2DArray(int, int);
void display2DArray(int, int);
void deallocateMemory(int, int);
void probRain(char c, char p);
void handleCoordinates(vector<pair<int, int>> & coords);
vector<pair<int, int>> extractCoordinates(vector<CityData> & cities, int size, vector<string> & names, vector<int> & ids);
void calculateTotals(vector<pair<int, int>> & coords, vector<CloudData> & clouds, vector<PressureData> & pressures, int & cityCloud, int & cityPressure);
vector<pair<int, int>> getSurrounding(int x, int y);

void calculateSurrounding1x1(vector<pair<int, int>> & smallCities, vector<CloudData> & clouds, vector<PressureData> & pressures, int & cityCloud, int & cityPressure);

vector<pair<int, int>> calculateSurrounding2x2(vector<pair<int, int>> & cities, vector<CloudData> & clouds, vector<PressureData> & pressures, int & cityCloud, int & cityPressure);

vector<pair<int, int>> getSurrounding3x3(int x, int y);

vector<pair<int, int>> calculateSurrounding3x3(vector<pair<int, int>> & cities, vector<CloudData> & clouds, vector<PressureData> & pressures, int & cityCloud, int & cityPressure);

void displaySCSummary(vector<CityData> & cities, vector<CloudData> & clouds, vector<PressureData> & pressures);

void displayMCSummary(vector<CityData> & cities, vector<CloudData> & clouds, vector<PressureData> & pressures);

void displayBCSummary(vector<CityData> & cities, vector<CloudData> & clouds, vector<PressureData> & pressures);

#endif // ALGO_H
