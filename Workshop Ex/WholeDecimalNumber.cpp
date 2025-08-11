#include <iostream>
#include <cmath>

using namespace std;

int main()
{
   cout << endl;
   cout << "Please enter a number: ";
   
   double num;
   cin >> num;
   
   if(floor(num)== ceil(num))
        cout << num << " is a whole number" << endl;
   else
        cout << num << " is a decimal number" << endl;
        
   cout << endl;
     

    return 0;
}