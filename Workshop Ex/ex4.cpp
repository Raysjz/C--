#include <iostream>
#include <string>
#include <cmath>

using namespace std;

enum TERRAIN_TYPE {UNKNOWN , GRASS_LAND , MOUNTAINOUS , LAKE , OCEAN , HILLY , SWAMP , URBAN_BUILT_UP};

struct GridArea
{
	int x, y;
	TERRAIN_TYPE terrain;
	
	GridArea()
	{
		x = 0;
		y = 0;
		terrain = UNKNOWN;
	}
	
	GridArea (int _x, int _y)
	{
		x = _x;
		y = _y;
		terrain = UNKNOWN;
	}
	
	GridArea (int _x , int _y , TERRAIN_TYPE _t)
	{
		// Implement algo here!!!
		//set x , y and terrain to their respective arguments!
		x = _x;
		y = _y;
		terrain = _t;
	}	
	
	bool isAdjacent (GridArea anotherPt)
	{
		int verticalDist = abs (anotherPt.y - y);
		int horizontalDist = abs (anotherPt.x - x);
		
		//if same x , difference in y by 1 unit , OR vice versa
		if(
			((anotherPt.x == x) && (verticalDist	== 1 )) ||
			((anotherPt.y == y) && (verticalDist	== 1 )) 
		   )
			return(true);
			
		return(false);
	}
	
	bool isDiagonalAdjacent (GridArea anotherPt)
	{
		bool isUpperLeft = (anotherPt.x == (x-1)) && (anotherPt.y == (y+1));
		bool isLowerLeft = (anotherPt.x == (x-1)) && (anotherPt.y == (y-1));
		bool isUpperRight = (anotherPt.x == (x+1)) && (anotherPt.y == (y+1));
		bool isLowerRight = (anotherPt.x == (x+1)) && (anotherPt.y == (y-1));
		
		if (isUpperLeft || isLowerLeft || isUpperRight || isLowerRight)
			return(true);
		else
			return(false);
	}
	
	string convertTerrainToString()
	{
		string terrainString = "";
		
		switch(terrain)
		{
			case UNKNOWN		 : terrainString = "UNKNOWN"; break;
			case GRASS_LAND		 : terrainString = "GRASS_LAND"; break;
			case MOUNTAINOUS	 : terrainString = "MOUNTAINOUS"; break;
			case LAKE			 : terrainString = "LAKE"; break;
			case OCEAN			 : terrainString = "OCEAN"; break;
			case HILLY			 : terrainString = "HILLY"; break;
			case SWAMP			 : terrainString = "SWAMP"; break;
			case URBAN_BUILT_UP  : terrainString = "URBAN_BUILT_UP"; break;
		}
		
		return(terrainString);
		
	}
	
	
	void displayInfo()
	{
		cout << "Grid Area [" << x << ", " << y << "] , Terrain : ";
		cout << convertTerrainToString() << endl;
	}
	
	
};

int main()
{
	GridArea ga;
	
	ga.x = 3; ga.y = 3; ga.terrain = HILLY;
	
	GridArea ga3_2 (3, 2, LAKE);
	GridArea ga3_4 (3, 4, MOUNTAINOUS);
	GridArea ga2_3 (2, 3, URBAN_BUILT_UP);
	GridArea ga4_3 (4, 3, URBAN_BUILT_UP);
	
	GridArea ga2_4 (2, 4, MOUNTAINOUS);
	GridArea ga2_2 (2, 2, GRASS_LAND);
	GridArea ga4_4 (4, 4, MOUNTAINOUS);
	GridArea ga4_2 (4, 2, GRASS_LAND);
	
	cout << endl;
	cout << "ga.isAdjacent (ga3_2) : " << boolalpha << ga.isAdjacent(ga3_2) << endl;
	cout << "ga.isAdjacent (ga3_4) : " << boolalpha << ga.isAdjacent(ga3_4) << endl;
	cout << "ga.isAdjacent (ga2_3) : " << boolalpha << ga.isAdjacent(ga2_3) << endl;
	cout << "ga.isAdjacent (ga4_3) : " << boolalpha << ga.isAdjacent(ga4_3) << endl;
	
	cout << "ga.isAdjacent (ga2_4) : " << boolalpha << ga.isAdjacent(ga2_4) << endl;
	cout << "ga.isAdjacent (ga2_2) : " << boolalpha << ga.isAdjacent(ga2_2) << endl;
	cout << "ga.isAdjacent (ga4_4) : " << boolalpha << ga.isAdjacent(ga4_4) << endl;
	cout << "ga.isAdjacent (ga4_2) : " << boolalpha << ga.isAdjacent(ga4_2) << endl;
	cout << endl;
	
	cout << endl;
	cout << "ga.isDiagonalAdjacent (ga3_2) : " << boolalpha << ga.isDiagonalAdjacent (ga3_2) << endl;
	cout << "ga.isDiagonalAdjacent (ga3_4) : " << boolalpha << ga.isDiagonalAdjacent (ga3_4) << endl;
	cout << "ga.isDiagonalAdjacent (ga2_3) : " << boolalpha << ga.isDiagonalAdjacent (ga2_3) << endl;
	cout << "ga.isDiagonalAdjacent (ga4_3) : " << boolalpha << ga.isDiagonalAdjacent (ga4_3) << endl;
	
	cout << "ga.isDiagonalAdjacent (ga2_4) : " << boolalpha << ga.isDiagonalAdjacent (ga2_4) << endl;
	cout << "ga.isDiagonalAdjacent (ga2_2) : " << boolalpha << ga.isDiagonalAdjacent (ga2_2) << endl;
	cout << "ga.isDiagonalAdjacent (ga4_4) : " << boolalpha << ga.isDiagonalAdjacent (ga4_4) << endl;
	cout << "ga.isDiagonalAdjacent (ga4_2) : " << boolalpha << ga.isDiagonalAdjacent (ga4_2) << endl;
	cout << endl;
	
	ga.displayInfo ();
	
	ga3_2.displayInfo ();
	ga3_4.displayInfo ();
	ga2_3.displayInfo ();
	ga4_3.displayInfo ();
	
	ga2_4.displayInfo ();
	ga2_2.displayInfo ();
	ga4_4.displayInfo ();
	ga4_2.displayInfo ();
	
	GridArea tmp;
	tmp.displayInfo ();
	
	return (0);

}
