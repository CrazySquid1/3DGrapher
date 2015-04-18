#ifndef FUNCTION_H
#define FUNCTION_H

#include "mString.h"
#include "Vector.h"
#include "Mesh.h"

class Function
{
	//doesn't include "z="
	mString equation;
	bool drawable;
	
	int Xgrid;
	int Ygrid;
	
	Mesh object;

public:
	//constructors
	Function(const int& x = 6, const int& y = 6);
	//x and y change the resolution of the grid
	Function(int x, int y);
	
	bool SetGridRes(int x, int y);
	
	bool SetEquation(unsigned char * text);
	mString& GetEquation();
	
	bool UpdateGrid(Vector min, Vector max);
	int GetGrid(const int& x, const int& y);

	Mesh& GetObject();
};

#endif