#include <iostream>

using namespace std;

int findLargest (int num1 , int num2);
int findLargest (int num1 , int num2 , int num3);
float findLargest (float num1, float num2);
float findLargest (float num1, float num2, float num3);
double findLargest (int num1 , float num2);
double findLargest (float num1 , int num2);

int main()
{   
	int biggestInt = findLargest(1,1);
	
	biggestInt =
	
	float biggestFloat = 
	
	biggestFloat =
	
	double biggestNum = findLargest(1.23f , 8);
	cout << "findLargest (1.23f , 8) returns : " << biggestNum << endl;
	
	biggestNum = findLargest (3,6.3f);
	cout << "findLargest (3 , 6.3f)) returns : " << biggestNum << endl;
  
} // end main() ...

int FindLargest (int num1 , int num2)
{
	return ( (num1 < num2) ? num1 : num2) ;
}

int findLargest (int num1 , int num2 , int num3)
{
	int tmp = (num1 > num2)?num1:num2;
	return ( ( num3 > tmp)?num3:tmp );
}

float findLargest(float num1, float num2)
{
	return ( (num1 > num2)?num1:num2 ) ;
}

float findLargest (float num1, float num2, float num3)
{
	int tmp = (num1 > num2)?num1:num2;
	return ( (num3 > tmp)?num3:tmp );
	
}

double findLargest (int num1 , float num2)
{
	return ( (num1 > num2)?num1:num2 );
}

double findLargest (float num1 , int num2)
{
	return ( (num1 > num2)?num1:num2 );
}