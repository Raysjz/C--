#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{   
  double userEnteredNumber;
  
  cout << "Please enter a number: ";
  cin >> userEnteredNumber;
  
  cout << setprecision(8);
  cout << "-------------------------------------------------------------------" << endl;
  cout << "Information on your number : " << userEnteredNumber << "..." << endl;
  cout << "-------------------------------------------------------------------" << endl;
  
  cout << setw(15) << right << "abs (" ;
  cout << setw(15) << left  << userEnteredNumber << ")";
  cout << setw(30) << right << " is : ";
  cout << setw(15) << left  << abs(userEnteredNumber) << endl;
  
  cout << setw(15) << right << "ceil ( ";
  cout << setw(15) << left  << userEnteredNumber << ")";
  cout << setw(30) << right << " is : ";
  cout << setw(15) << left  << ceil(userEnteredNumber) << endl;
  
  cout << setw(15) << right << "floor ( ";
  cout << setw(15) << left  << userEnteredNumber << ")";
  cout << setw(30) << right << " is : ";
  cout << setw(15) << left  << floor(userEnteredNumber) << endl;
  
  cout << setw(15) << right << "round ( ";
  cout << setw(15) << left  << userEnteredNumber << ")";
  cout << setw(30) << right << " is : ";
  cout << setw(15) << left  << round(userEnteredNumber) << endl;
  
  cout << setw(15) << right << " ";
  cout << setw(15) << left  << userEnteredNumber << " ";
  cout << setw(30) << right << " in scientific notation : ";
  cout << setw(15) << left  << scientific << userEnteredNumber << endl;
  
  cout << fixed;
  
  cout << setw(15) << right << " ";
  cout << setw(15) << left  << setprecision(8) << userEnteredNumber << " ";
  cout << setw(30) << right << " to 1 dec place : ";
  cout << setw(15) << left  << setprecision(1) << userEnteredNumber << endl;
  
  cout << setw(15) << right << " ";
  cout << setw(15) << left  << setprecision(8) << userEnteredNumber << " ";
  cout << setw(30) << right << " to 2 dec place : ";
  cout << setw(15) << left  << setprecision(2) << userEnteredNumber << endl;
  
  cout << setw(15) << right << " ";
  cout << setw(15) << left  << setprecision(8) << userEnteredNumber << " ";
  cout << setw(30) << right << " to 3 dec place : ";
  cout << setw(15) << left  << setprecision(3) << userEnteredNumber << endl;
  
  cout << setprecision(8);
  
  cout << setw(15) << right << "casting ";
  cout << setw(15) << left  << userEnteredNumber << " ";
  cout << setw(30) << right << " to int : ";
  cout << setw(15) << left  << static_cast <int> (userEnteredNumber) << endl;
  
  cout << setw(15) << right << "casting ";
  cout << setw(15) << left  << userEnteredNumber << " ";
  cout << setw(30) << right << " to float : ";
  cout << setw(15) << left  << static_cast <float> (userEnteredNumber) << endl;

} // end main() ...

