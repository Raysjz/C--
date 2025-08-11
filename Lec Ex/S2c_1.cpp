void AddArray ( 
		int Size,		// size of the arrays
		const float A[ ],	// array passed as input
		const float B[ ],	// array passed as input
		float C[ ] )		// array passed for output
	{
		for (int i=0; i<Size; i++)
			C[i] = A[i] + B[i];
	}
int main(){
int main(){
		const int ArySize = 5; 
		float Ary1[ArySize]={1,2,3,4,5};
		float Ary2[ArySize]={6,7,8,9,10};
		float Ary3[ArySize];
		
		AddArray(ArySize, Ary1, Ary2, Ary3);
		...
