#include <iostream>

using namespace std;

void demoPassByValue ();
int getDiv_PassByValue (int, int);
int getMod_PassByValue (int ,int);

void demoPassByReference ();
void getDivMod(int , int , int& , int&);

int main()
{   
  demoPassByValue();
  demoPassByReference();
  
  return 0;
  
} // end main() ...

void demoPassByValue()
{
  int a = 19, b = 7 , dividend , modulus;
  dividend = getDiv_PassByValue(a,b);
  modulus = getMod_PassByValue(a,b);
 
  cout << endl;
  cout << "At end of demoPassByValue() !!!" << endl;
  cout << "&a         : " << &a         << ", a         : " << a         << endl;
  cout << "&b         : " << &b         << ", b         : " << b         << endl;
  cout << "&dividend  : " << &dividend  << ", dividend  : " << dividend  << endl;
  cout << "&modulus   : " << &modulus   << ", modulus   : " << modulus   << endl;   
}

int getDiv_PassByValue (int num1 , int num2)
{
	int result = num1 / num2 ;
	
	cout << endl;
	cout << "At end of getDiv_PassByValue !!!" << endl;
	cout << "&num1    : " << &num1     << ", num1   : " << num1        << endl;
	cout << "&num2    : " << &num2     << ", num2   : " << num2        << endl;
	cout << "&result  : " << &result   << ", result : " << result      << endl;
	
	return(result);
}

int getMod_PassByValue( int num3 , int num4)
{
	int result = num3 % num4 ;
	
	cout << endl;
	cout << "At end of getMod_PassByValue !!!" << endl;
	cout << "&num3    : " << &num3     << ", num3   : " << num3       << endl;
	cout << "&num4    : " << &num4     << ", num4   : " << num4       << endl;
	cout << "&result  : " << &result   << ", result : " << result      << endl;
	
	return(result);
	
}


void demoPassByReference()
{
	int a = 19 , b = 7 , dividend , modulus;
	getDivMod (a , b , dividend , modulus);
	
	cout << endl;
	cout << "At end of demoPassByReference() !!!" << endl;
	cout << "&a          : " << &a         << ", a  : "       << a          << endl;
	cout << "&b          : " << &b         << ", b   : "      << b          << endl;
	cout << "&dividend   : " << &dividend  << ", dividend : " << dividend   << endl;
	cout << "&modulus    : " << &modulus   << ", modulus : "  << modulus    << endl;

}


void getDivMod(int num5, int num6, int& addrOne , int& addrTwo)
{
	addrOne = num5 / num6;
	addrTwo = num5 % num6 ;
	
	cout << endl;
	cout << "At end of demoPassByReference() !!!" << endl;
	cout << "&num5      : " << &num5      << ", num5    : " << num5      << endl;
	cout << "&num6      : " << &num6      << ", num6    : " << num6      << endl;
	cout << "&addrOne   : " << &addrOne   << ", addrOne : " << addrOne   << endl;
	cout << "&addrTwo   : " << &addrTwo   << ", addrTwo : " << addrTwo	 << endl;
	
}

