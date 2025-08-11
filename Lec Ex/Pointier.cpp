#include <iostream>
using namespace std;

class Pointier 
{
  public:
    int *x;
    Pointier()	{ x = new int(5); }
    void display()	{ cout << *x << endl; }
};

int main()
{
    Pointier PointA;
    Pointier PointB(PointA);
    PointA.display();
    PointB.display();
    *(PointB.x)=3;
    PointA.display();
    PointB.display();
}
