#include <iostream>
#include <string>
#include <cstring>
#include <cctype>

using namespace std;

voidtestIntArray();
void arrayValuesIncrement (int numArray [] , int arraySize);

int main()
{
	testIntArray ();
	
	return(0);
	
}

void testIntArray()
{
	int numberList [] = {2 ,7 , 5 , 12 ,37 ,67);
	
	cout << endl;
	cout << "In testIntArray() !!" << endl;
	cout << "numberList variable's value 					: " << numberList << endl;
	cout << "numberList variable's value (which is an addr) : " << &numberList << endl;
	cout << "Address of numberList [0]						: " << numberList[0] << endl; 
	cout << "Address of numberList [1]						: " << numberList[1] << endl; 
	cout << "Address of numberList [2]						: " << numberList[2] << endl; 
	cout << endl;

	cout << "In testIntArray() , BEFORE calling arrayValuesIncrement() , numberList[] contrains : " << endl;
	for (int i = 0 ; i<6 ; i++ )
		cout << numberList[i] << ", ";
	cout << endl << endl;
	
	arrayValuesIncrement (numberList, 6);
	
	cout << endl;
	cout << "In testIntArray() , AFTER calling arrayValuesIncrement() , numberList[] contains : " << endl;
	for (int i = 0; i < 6 ; i++)
		cout << numberList[i] << ", ";
	cout << endl;
}

void arrayValuesIncrement (int numArray [] , int arraySize)
{
	for (int i =0; i<arraySize; i++)
		numArray[i]++;
	
	cout << "Inside arrayValuesIncrement () !!! << endl;
	cout << "address of numArray variable					: " << &numArray << endl;
	cout << "numArray variable's value (which is an addr)	: " << numArray  << endl;
	cout << "Address of numArray[0]							: " << &numArray[0] << endl;
	cout << "Address of numArray[1]							: " << &numArray[1] << endl;
	cout << "Address of numArray[2]							: " << &numArray[2] << endl;
	cout << "arraySize										: " << arraySize << endl;
}