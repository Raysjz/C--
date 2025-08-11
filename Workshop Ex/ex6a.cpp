#include <fstream>
#include <iostream>
#include <string>

using namespace std;


int main()
{

	int intVar	 = 38;
	int * intPtr = &intVar;
	
	cout << endl;
	cout << "int intVar   = 38; 	 " << endl;
	cout << "int * intPtr = &intVar; " << endl;
	
	cout << endl;
	cout << "Address  of intVar : " << &intVar << endl;
	cout << "Contents of intVar : " << intVar  << endl;
	
	cout << endl;
	cout << "Address  of 	intPtr : " << &intPtr << endl;
	cout << "Contents of 	intPtr : " << intPtr  << endl;
	cout << "De-referencing intPtr : " << *intPtr << endl;
	
	cout << endl;
	intVar = 168;
	cout << "intVar = 168" << endl;
	
	cout << endl;
	cout << "Address  of intVar : " << &intVar << endl;
	cout << "Contents of intVar : " << intVar  << endl;
	
	cout << endl;
	cout << "Address  of 	intPtr : " << &intPtr << endl;
	cout << "Contents of 	intPtr : " << intPtr  << endl;
	cout << "De-referencing intPtr : " << *intPtr << endl;
	
	return 0;

	
} // end main() ...