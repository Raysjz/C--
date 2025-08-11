#include <iostream>
using namespace std;

const double PI = 3.14159;

int main(){
	int radius;
	
	cout << "Enter a radius : ";
	cin >> radius;
	
	double area = PI * radius * radius;
	double circumference = 2 * PI * radius;
	
	cout << "Area is " << area << endl;
	cout << "Circumference is " << circumference << endl;
}