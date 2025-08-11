#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <cmath>

using namespace std;

int generatePositiveRandomInt (int lowerLimit , int upperLimit);

int main()
{
	string filename = " file.txt" ;
	ofstream outputFileStream (filename);
	
	cout << endl;
	cout << "------------------------------------------------------------------------" << endl;
	cout << "Generating random values and storing them in file : '" << filename << "'" << endl;
	cout << "------------------------------------------------------------------------" << endl;
	cout << endl;
	
	for (int i = 1; i<=10; i++)
	{
		outputFileStream << "Random #" << i << " : " << generatePositiveRandomInt (-5, 5) << endl;
	}
	
	outputFileStream.close();
	
	ifstream inputFileStream(filename);
	string aLine;
	
	while(getline (inputFileStream , aLine))
		cout << "aLine : " << aLine << endl;
	
	inputFileStream.close();
	
	cout << endl;
	
	return(0);
}

int generatePositiveRandomInt (int lowerLimit , int upperLimit)
{
	if(upperLimit == lowerLimit)
		return (lowerLimit);
	
	int range = abs(upperLimit - lowerLimit) + 1;
	int lowerValue = (upperLimit > lowerLimit)?lowerLimit:upperLimit;
	
	// the sleep () is just a "convenience mechanism" to generate random int
	// AVOID using sleep() in your future programs as much as possible !!!
	sleep(1);
	srand(time(NULL));
	int randInt = rand() % range + lowerValue;
	
	cout << "randInt : " << randInt << endl;
	return(randInt);
}
	
	
	
	
	
	
