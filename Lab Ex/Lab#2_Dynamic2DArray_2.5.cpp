// Lab Exercises Task 2_5

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string ** array2D = nullptr;

void init2DArray(int,int);
void populate2DArray(int,int);
void display2DArray(int,int);
void safelyDeallocateMemory(int,int);

int main()
{
	int row, col;
	row = col = 0;

	cout << "Please enter no. of cols : ";
	cin >> col;
	cout << endl;

	cout << "Please enter no. of rows: ";
	cin >> row;
	cout << endl;
    

	init2DArray(col, row);
	populate2DArray(col, row);
	display2DArray(col, row);
	safelyDeallocateMemory(col, row);

	cout << endl;

	return 0;
}


void init2DArray(int col, int row)
{
	array2D = new string * [row]; //Dynamically create a 1D array row string

	for(int i=0 ; i < row ; i++)
		array2D[i] = new string [col]; //Dynamically create second col

}

void populate2DArray(int col , int row)
{
	for (int i =(row-1); i >=0 ; i--) //Changes made
	{
		for(int j=0; j < col ; j++)
		{
			ostringstream oss;
			oss << "x" << j+1 << "y" << i+1; //Changes made

			array2D [i] [j] = oss.str();
		}
	}
}

void display2DArray(int col, int row)
{
	cout << endl;
	for (int i =(row-1); i >=0 ; i--){ //Changes made
		for(int j=0; j<col ; j++)
		{
			cout << array2D [i][j] << ", ";
		}
	cout << endl;
	}
	
}

void safelyDeallocateMemory (int col , int row)
{
	if(col <=0)
		return;
	for (int i=0; i<row ; i++)
		delete [] array2D[i];

	delete [] array2D;
}
