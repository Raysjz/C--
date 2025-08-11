// Lab Exercises Task 4

#include <iostream>
#include <string>

using namespace std;

struct Student
{
	string name;
	string addr;
};

//Please google "c typedef" to see learn the convenience of typedef
typedef struct Student StudentType;

void displayArrayContents1(int , StudentType *);
void displayArrayContents2(int , struct Student *);
void safelyDeallocateMemory(int , StudentType *);

int main()
{
	StudentType * dynamicStudentTypeArrayPtr = nullptr;
	//struct Student * dynamicStudentTypeArrayPtr = nullptr;

	int arraySize = 0;

	cout << "Please enter no. of students : ";
	cin >> arraySize;

	// any time cin >> is followed by getline() , use cin.ignore() !!!
	cin.ignore(80, '\n');
	cout << endl;

	dynamicStudentTypeArrayPtr = new StudentType[arraySize];

	for(int i=0 ; i <arraySize ; i++)
	{
		StudentType temp;
		//struct Student temp;

		cout << "Please enter name of students #" << i + 1 << " : ";
		getline(cin , temp.name);
		cout << endl;

		cout << "Please enter address of students #" << i + 1 << " : ";
		getline(cin , temp.addr);
		cout << endl;
	
	//------------------------------------------------------
	// write the code to : prompt and store the addr of the i-th student
	//-------------------------------------------------------
	
		cout << endl;

		dynamicStudentTypeArrayPtr [i] = temp;
	
	}

	displayArrayContents1(arraySize , dynamicStudentTypeArrayPtr);
	displayArrayContents2(arraySize , dynamicStudentTypeArrayPtr);

	safelyDeallocateMemory(arraySize , dynamicStudentTypeArrayPtr);

	cout << endl;

	return 0;

}

void displayArrayContents1 (int arraySize , StudentType *studentArrayPtr)
{
	//------------------------------------------------------
	// write the code to : display contents in the array of struct(storing students data)
	//-------------------------------------------------------
	for (int i = 0 ; i < arraySize ; i++)
	{
		StudentType tmp = studentArrayPtr [i];
		//struct Student temp = studentArrayPtr[i];

		cout << endl;
		cout << "Data of Student #" << i + 1 << " : " << endl;
		cout << "Name : " << tmp.name << endl;
		cout << "Address : " << tmp.addr << endl;
		cout << endl;
	}
}

void displayArrayContents2(int arraySize , struct Student *studentArrayPtr)
{

	displayArrayContents1 (arraySize , studentArrayPtr);

}

void safelyDeallocateMemory (int arraySize , StudentType *studentArrayPtr)
{
		if (arraySize <= 0)
			return;

		delete [] studentArrayPtr;
	
}	