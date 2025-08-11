#include <iostream>
#include <string>
#include <cstring>
#include <cctype>

using namespace std;

void testCharArray();
void convertToUpperCase (char input[] );

int main()
{
	testCharArray();
	
	return (0);
	
}

void testCharArray()
{
	const int MAX_LENGTH = 30;
	char nameArray [MAX_LENGTH] ;
	
	cout << "Please enter your name : ";
	
	// VER 1 - Read in characters , stopping when encountering 1st space char
	cin >> nameArray;
/*
	// VER 2 - Read in entire line and store in char [] nameArray
	cin.getline(nameArray , MAX_LENGTH);
	
	// VER 3 - Read in entire line and store in C++ String nameString 
	string nameString;
	getline ( cin , nameString);
	strcpy (nameArray,nameString.c_str());
*/	
	cout << endl;
	
	cout << "Inside main() , BEFORE invoking convertToUpperCase() ..." << endl;
	cout << "Address of nameArray : " << &nameArray << endl;
	cout << "nameArray variable 's value (which is SUPPOSED TO BE an addr) : " << nameArray << endl;
	cout << "Address of nameArray[0] : " << &nameArray[0] << endl;  
	cout << "Address of nameArray[1] : " << &nameArray[1] << endl;  
	cout << "Address of nameArray[2] : " << &nameArray[2] << endl;  
	
	cout << "Dear " << nameArray << ", your name converted to upper case is : "<< endl << endl;
	convertToUpperCase(nameArray);
	cout << nameArray << endl;
	
}

void convertToUpperCase(char input[])
{
	/*
	IMPT NOTE: strlen () can only be used on char[] , OR C-String ( which is of type const char* ) !!!
	*/
	int size = strlen(input);
	
	for (int i = 0 ; i < size ; i++)
		if (islower (input[i]))
			input[i] = toupper(input[i]);
	
	cout << "Inside convertToUpperCase () !!! " << endl;
	cout << "Address of input variable                  : " << &input << endl;
	cout << "Input variable's value (which is SUPPOSED TO BE an addr) : " << input << endl;
	cout << "Address of input[0]                                      : " << &input[0] << endl;
	cout << "Address of input[1]                                      : " << &input[1] << endl;
	cout << "Address of input[2]                                      : " << &input[2] << endl;

	cout << "size of contents in input[]                              : " << size << endl;
	cout << endl;
}
