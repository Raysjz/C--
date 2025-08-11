#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

struct StudentInfo
{
	string name;
	string studentID;
	double gpa;
};

typedef StudentInfo StudentType;

int main()
{
	int noOfRecs;
	cout << "Please enter no. of records : ";
	cin >> noOfRecs;
	cin.ignore(100, '\n');
	cout << endl;
	
	StudentType * studentRecords = new StudentType [noOfRecs];
	
	for (int i=0; i<noOfRecs; i++)
	{
	cout << "Please enter student #" << i+1 << "'s name 		: ";
	getline(cin, studentRecords [i].name);
	
	cout << "Please enter student #" << i+1 << "'s student id	: ";
	getline(cin, studentRecords [i].studentID);
	
	cout << "Please enter student #" << i+1 << "'s gpa	        : ";
	cin >> studentRecords[i].gpa;
	cin.ignore(100, '\n');
	cout << endl;
	}

	for (int i=0; i<noOfRecs; i++)
	{
		cout << "Stored info for student #" << i+1 << " : " << endl;
		cout << "Name 		: " << studentRecords [i].name << endl;
		cout << "Student ID : " << studentRecords [i].studentID << endl;
		cout << "GPA 		: " << studentRecords [i].gpa << endl;
		cout << endl;
	}
	
	delete [] studentRecords;
	
	return 0;
	
} // end of main() ...