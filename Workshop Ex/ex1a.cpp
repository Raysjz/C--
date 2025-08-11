#include <iostream>
using namespace std;

int main()
{
	int howManyIntegers;
	
	cout << "Wish to process how many integers : ";
	cin >> howManyIntegers;
	cout << endl;

	long useEnteredNum;
	
	for(int i = 0; i<howManyIntegers; i++)
	{
		cout << "Enter a POSITIVE number : ";
		cin >> useEnteredNum;
		
		cin.clear();
		//ignore up to 100 chars , or up to newline 'n' char...
		cin.ignore(100, '\n');
		
		long aNumber = useEnteredNum;
		//if user entered a negative number , change it to positive !
		if(aNumber < 0)
			aNumber *= -1;
		
			int sumOfDigits = 0;
			int temp = aNumber;
			
		while ( temp > 0)
		{
			cout << "B4 sumOfDigits : " << sumOfDigits << " , temp : " << temp << endl;
				sumOfDigits += temp % 10;
				temp /= 10;
			cout << "Aft sumOfDigits : " << sumOfDigits << " , temp : " << temp << endl;
			
		} //end while loop
		
		cout << "Sum of all digits in ' "<< useEnteredNum << " ' is : " << sumOfDigits << endl;
		cout << endl;
		
	} // end for-loop 
	
} // end main() 