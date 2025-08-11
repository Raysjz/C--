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

void demoWriteBinaryDataToOutputFile(int noOfRecs);
void demoReadBinaryDataFromInputFile(int noOfRecs);

int main()
{
	
	cout << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "(1) Prompt user for name, phone, email							   " << endl;
	cout << "(2) Store name, phone, email in a friends struct variable 		   " << endl;
	cout << "(3) Write contents of the struct variable into 'friends.dat'	   " << endl;
	cout << " 	 as binary data												   " << endl;
	cout << "------------------------------------------------------------------" << endl;
	
	demoWriteBinaryDataToOutputFile(3);
	
	cout << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "(1) Reading contents from binary file 'friends.dat'			   " << endl;
	cout << "    struct by struct											   " << endl;
	cout << "(2) Store binary data into temporary friends struct variable 'x'  " << endl;
	cout << " 	 as binary data, befoore accessing and display its contents    " << endl;
	cout << "------------------------------------------------------------------" << endl;
	
	demoReadBinaryDataFromInputFile(3);
	
	return 0;
	
} // end main() ...

void demoWriteBinaryDataToOutputFile(int noOfRecs)
{
	friends x;
	
ofstream fout("friends.dat", ios::out | ios::binary);

	if(fout.good())
	{
		for(int i=0; i<noOfRecs; i++)
		{
			//get details
			cout << "Name: ";		cin >> x.name;
			cout << "Phone: ";		cin >> x.phone;
			cout << "Email: ";		cin >> x.email;
			
			//Write the structure to the file
			fout.write( reinterpret_cast <const char*>(&x), sizeof(friends) );
			
		} // end for-loop ...
	
	fout.close();
	
	} // end-if...
	
} // end demoWriteBinaryDataToOutputFile ...

void demoReadBinaryDataFromInputFile (int noOfRecs)
{
	friends x;
	
	ifstream fin("friends.dat", ios::in | ios::binary);
	if (fin.good())
	{
		for (int i = 0; i<noOfRecs; i++)
		{
			//read the structure from the file
			fin.read ( reinterpret_cast<char*>(&x), sizeof(friends) );
			
			//print details
			cout << "Name: "  << x.name << endl;
			cout << "Phone: " << x.phone << endl;
			cout << "Email: " << x.email <<	endl << endl;
			
		} // end for-loop ...
		
	  fin.close();
	} // end - if ...
	
} // end demoReadBinaryDataFromInputFile() ...