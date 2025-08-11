// Lab Exercises Task 3

#include <iostream>
#include <string>

using namespace std;

void displayArrayContents (int , string * , string *);
void safelyDeallocateMemory(int , string * ,string *);

int main()
{
	string * dynamicNameArrayPtr = nullptr;
	string * dynamicAddrArrayPtr = nullptr;

	int arraySize = 0;

	cout << "Please enter no. of students: ";
	cin >> arraySize;

	// any time cin >> is followed by getline() , use cin.ignore() !!!
	cin.ignore(80 ,'\n');
	cout << endl;

	dynamicNameArrayPtr = new string [arraySize];
	dynamicAddrArrayPtr = new string [arraySize];

	//------------------------------------------------------
	// write the code to : initialize dynamicAddrArrayPtr!
	//-------------------------------------------------------

	for (int i=0 ; i<arraySize ; i++)
	{
		cout << "Please enter name of student # " << i + 1 << " : ";
		getline(cin ,dynamicNameArrayPtr[i]);
		cout << endl;
		
		cout << "Please enter address of student # " << i + 1 << " : ";
		getline(cin, dynamicAddrArrayPtr[i]);
		cout << endl;
	
	//------------------------------------------------------
	// write the code to : prompt and store the addr of the i-th student
	//-------------------------------------------------------
		cout << endl;
	}	

	displayArrayContents (arraySize , dynamicNameArrayPtr , dynamicAddrArrayPtr);
	safelyDeallocateMemory(arraySize , dynamicNameArrayPtr , dynamicAddrArrayPtr);

	cout << endl;

	return 0;
}

	void displayArrayContents(int arraySize , string * nameArrayPtr , string * addrArrayPtr)
	{
		for(int i=0; i<arraySize ; i++)
		{
			cout << endl;
			cout << "Data of student #" << i+1 << " : " << endl;

			if(nameArrayPtr != nullptr)
				cout << "Name : " << nameArrayPtr [i] << endl;

			if(addrArrayPtr != nullptr)
				cout << "Address : " << addrArrayPtr [i] << endl;	
		//------------------------------------------------------
		// write the code to : display the addr of the i-th student
		//-------------------------------------------------------
			cout << endl;
		}	 
	}

	void safelyDeallocateMemory (int arraySize , string * dynamicNameArrayPtr , string * dynamicAddrArrayPtr)
	{
		if (arraySize <= 0)
			return;

		delete [] dynamicNameArrayPtr;
		delete [] dynamicAddrArrayPtr;
		
	}




