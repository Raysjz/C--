class Person 
{ 
private: int idNum; 
string firstName; 
string lastName; 
public: 
void setData(int id, string fn, string ln); 
void printData() const; }; 
void Person::setData(int id, string first, string last) 
{ idNum = id; lastName = last; firstName = first; } 
void Person::printData() const 
	{ 
	cout << "ID: " << idNum << ", Name: " << firstName << " " << lastName << endl; 
	}
}


int main() 
{ 
Customer cust1; 
cust1.setData (537, "Mr", "Bob"); 
cust1.printData(); 
cust1.setBalanceDue(123.45); 
cust1.outputBalanceDue(); 
}