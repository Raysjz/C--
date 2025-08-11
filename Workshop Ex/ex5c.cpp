#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct friends
{
	char name[64];
	long phone;
	char email[128];
	
};

void demoWriteArrayofBinaryDataToOutputFile(int noOfRecs);
void demoReadArrayofBinaryDataFromInputFile(int noOfRecs);


int main()
{
	
	cout << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "(1) Prompt user for name, phone, email							   " << endl;
	cout << "(2) Store name, phone, email in a friends struct array slot 	   " << endl;
	cout << "(3) Write contents of the array into 'friends.dat'				   " << endl;
	cout << " 	 as binary data												   " << endl;
	cout << "------------------------------------------------------------------" << endl;
	
	demoWriteArrayofBinaryDataToOutputFile(3);
	
	cout << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "(1) Reading contents of an entire array of friend struct from	   " << endl;
	cout << "    binary file 'friends.dat', and store them in local array	   " << endl;
	cout << "(2) Loop through the array of friends struct 'xArray' and		   " << endl;
	cout << " 	 display its contents...								       " << endl;
	cout << "------------------------------------------------------------------" << endl;
	
	demoReadArrayofBinaryDataFromInputFile(3);
	
	return 0;
	
} // end main() ...

void demoWriteArrayofBinaryDataToOutputFile(int noOfRecs)
{
	friends xArray[noOfRecs];
	
	for(int i=0; i<noOfRecs; i++)
	{
		//get details
		cout << "Name: ";		cin >> xArray[i].name;
		cout << "Phone: ";		cin >> xArray[i].phone;
		cout << "Email: ";		cin >> xArray[i].email;
		cout << endl;
		
			
	} // end for-loop ...

	ofstream fout("friends.dat", ios::out | ios::binary);
	
	if(fout.good())
		fout.write ( reinterpret_cast<const char*> (xArray), (sizeof(friends) * noOfRecs) );
	
	fout.close();
	
	
} // end demoWriteArrayofBinaryDataToOutputFile ...

void demoReadArrayofBinaryDataFromInputFile (int noOfRecs)
{
	friends xArray[noOfRecs];
	
	ifstream fin("friends.dat", ios::in | ios::binary);
	
	if (fin.good())
		fin.read ( reinterpret_cast<char*> (xArray), (sizeof(friends) * noOfRecs) );
		
	for (int i = 0; i<noOfRecs; i++)
	{
			
		
		cout << "Rec #"  << i+1 << endl;
		cout << "Name: "  << xArray[i].name << endl;
		cout << "Phone: " << xArray[i].phone << endl;
		cout << "Email: " << xArray[i].email <<	endl << endl;
			
	} // end for-loop ...
		
	fin.close();
	
} // end demoReadArrayofBinaryDataFromInputFile() ...