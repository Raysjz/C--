#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    //Exercise 1
    /*
    int value1 = 1;
    int value2 = 2 ;
    int temp = value1;
    value1 = value2;
    value2 = temp;

    cout << "Value 1 : " << value1 << endl;
    cout << "Value 2 : " << value2 << endl;
    */


   //Exercise 2
    /*
    double x = 10;
    double y = 5;
    double z = (x + 10) / (3 * y);

    cout << "x : " << x << endl;
    cout << "y : " << y << endl;
    cout << "z : " << z << endl;
    */

   //Exercise 3
   /*
    double sales = 95000;
    cout << "Sales : $" << sales << endl;
    double tax = sales * 0.04;
    cout << "State Tax : $" << tax << endl;
    double countyTax = sales * 0.02;
    cout << "County Tax : $" << countyTax << endl;

    double totalTax = tax + countyTax;

    cout << "Total Tax : $" << totalTax << endl;
    */

    //Exercise 4
    /*
    cout << "Enter a value: ";
    int value;
    cin >> value;
    cout << value;
    */

    //Exercise 5
    /*
    cout << "Enter a temperature in Fahrenheit : ";
    double fahValue;
    cin >> fahValue;
    double celValue;
    celValue = ((fahValue - 32) * 5) / 9 ;

    cout << "Temperature Converted to Celsius : " << celValue << " C" << endl;
    */

    const short minValue = 1;
    const short maxValue = 6;
    srand(time(0));
    short firstDie = (rand() % (maxValue - minValue + 1)) + minValue;
    short secondDie = (rand() % (maxValue - minValue + 1)) + minValue;

    cout << firstDie << " , " << secondDie;

    return 0;
}