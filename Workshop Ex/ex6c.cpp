#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main()
{
	int size;
	
	cout << "Please enter size of array : " ;
	cin >> size;
	cout << endl;
	
	int * dynamicIntArray = new int [size];
	
	for (int i = 0; i<size ; i ++)
		dynamicIntArray [i] = (i+1) * 10;
	
	cout << "Accessing dynamic array's contents ..." << endl;
	
	for (int i = 0 ; i < size ; i++ )
		cout << "dynamicIntArray [" << i << "] stores " << dynamicIntArray [i] << endl;
	
	cout << endl;
	cout << "Using pointer to access dynamic array's contents ... " << endl;
	cout << endl;
	
	int * intPtr = dynamicIntArray;
	
	for (int i = 0; i<size ; i ++)
	{
		cout << "intPtr contents (an addr) : " << intPtr << endl;
		cout << "addr : ' " << intPtr << "' stores values " << *intPtr << endl;
		cout << "incrementing intPtr now (i.e intPtr++)" << endl;
		intPtr++;
		cout << endl;
	}
	cout << endl;
	
	//without below line , you will have memory leak!
	delete [] dynamicIntArray;
	
	return 0;
	
} // end of main() ...