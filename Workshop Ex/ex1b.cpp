#include <iostream>
using namespace std;

int main()
{
	int rectLength , rectBreadth;
	
	cout << "Please enter the length of a rectangle  (>= 3 units) : ";
	cin >> rectLength;
	
	cout << "Please enter the breadth of a rectangle (>= 3 units) : ";
	cin >> rectBreadth;
	cout << endl;
 	
	//Display a Horizontal Rectangle where possible ...
	for (int row = 0 ; row<rectBreadth; row ++)
	{
	    for (int col = 0; col<rectLength; col ++)
	    {
	        //cout << " [row , col] : " << "[" << row << " ," <, col << "]";
	        if( (row == 0) || (row == (rectBreadth-1)) ||
	            (col == 0) || (col == (rectLength-1)) )
	            cout << "#" ;
	       else 
	            cout << " ";
	    }
	    cout << endl;
	}
	
	cout << endl;
	cout << "Perimeter of rectangle : " << ((2* rectLength) + (2 * rectBreadth)) << " units " << endl;
	cout << "Area of rectangle      : " << (rectLength * rectBreadth) << " units square " << endl;
	cout << endl;
	
} // end main() ...