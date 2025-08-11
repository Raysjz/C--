// Menu.h
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

// Menu
void displayMenu();
void processOption(int choice);
void waitForEnter();

// Function to make String Uppercase
string stringToUpper(string & sInput);

// Shapes
void inputSensorData();
void computeArea();
void printShapesReport();
void displaySubmenu();

// Delete Array
void deallocateMemory();


#endif