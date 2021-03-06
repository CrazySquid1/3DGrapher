#include "Function.h"

Function::Function()
{
	this->Xgrid = 0;
	this->Ygrid = 0;
	
	this->SetDrawable(false);
	//"equation" string takes care of itself
}

bool Function::SetGridRes(int x, int y)
{
	//first check if the equation has been entered
	if (!drawable)
	{
		uString::ErrorPrint("Equation isn't drawable, won't set the grid res");
		return false;
	}
	this->Xgrid = x;
	this->Ygrid = y;

	//update mesh
	int verticesNo = x * y;
	//squares need vertexs on both side. hence can't have squares on the bounderies
	int squareNo = (x - 1) * (y - 1);

	//two triangles make up a square
	int triNo = 2 * squareNo;

	//triangles are made up of three sides
	int indicesNo = triNo * 3;
	return object.SetSpace(verticesNo, indicesNo);
}

int Function::CalculateSpaceRequired(int x, int y)
{
	//update mesh
	int verticesNo = x * y;
	//squares need vertexs on both side. hence can't have squares on the bounderies
	int squareNo = (x - 1) * (y - 1);

	//two triangles make up a square
	int triNo = 2 * squareNo;

	//triangles are made up of three sides
	int indicesNo = triNo * 3;

	int spaceRequired = (sizeof(float) * 4 + sizeof(Vector) + sizeof(Matrix)) * verticesNo + sizeof(int) * indicesNo;

	return spaceRequired;

}


void Function::ClearGrid()
{
	object.ClearSpace();
}

bool Function::SetEquation(uString& text)
{
	equation = text;
	return true;
}

uString& Function::GetEquation()
{
	return this->equation;
}

bool Function::UpdateGrid(Vector& min, Vector& max)
{
	//first check if the equation has been entered
	if (!drawable)
	{
		uString::ErrorPrint("Equation isn't drawable, therefore can't update function grid");
		return false;
	}
	
	if(Xgrid <= 1 || Ygrid <= 1)
	{
		uString::ErrorPrint("Invalid grid resolution. Maybe it hasn't been set");
		return false;
	}
	
	//work out how much to add to x and y to get to the next line
	float Ystep = (float) (max(1) - min(1)) / ((float)this->Ygrid - 1.0);
	float Xstep = (float) (max(0) - min(0)) / ((float)this->Xgrid - 1.0);
	
	/*
	//workout the increase in percentage after each loop (just for loading screen)
	float perStep = 1.0 / (Ystep * this->Xgrid);
	*/

	float Xvalue = min(0);
	int counter = 0;
	for(int x = 0; x < Xgrid; x++)
	{
		//when start new x row reset the y value
		float Yvalue = min(1);
		for (int y = 0; y < Ygrid; y++)
		{
			int eCode = 0;
			float result = 0.0;
			result = Evaluate::Eval(this->GetEquation(), Xvalue, Yvalue, &eCode);
			
			
			float Zvalue = result;
			
			//store results
			object.GetVertex(GetGrid(x, y))(0) = Xvalue;
			object.GetVertex(GetGrid(x, y))(1) = Yvalue;
			object.GetVertex(GetGrid(x, y))(2) = Zvalue;

			//compute next y value
			Yvalue += Ystep;
			
			
			if(Yvalue > (max(1) + Ystep) + 0.5) //+0.5 because floats round
			{
				uString::ErrorPrint("y variable exceeding Ymax");
				return false;
			}
			
			counter++;
			
			if(counter > 72000)
			{
				uString::ErrorPrint("looping too many times");
				return false;
			}
		}
		//compute next x value
		Xvalue += Xstep;
		
		if(Xvalue > (max(0) + Xstep) + 0.5) //+0.5 because floats round
		{
			uString::ErrorPrint("x variable exceeding Xmax");
			return false;
		}
	}


	//update Object

	int index = 0;
	int NumTriRow = Xgrid - 1;
	int NumTriCol = Ygrid - 1;
	for (int rowTri = 0; rowTri < NumTriRow; rowTri++)
	{
		for (int colTri = 0; colTri < NumTriCol; colTri++)
		{
			//two types of triangles
			//types with two vertexes on y - type 1
			//or types with two vertexes on x - type 2

			//type 1
			object.GetIndice(index) = GetGrid(rowTri + 1, colTri);
			index++;

			object.GetIndice(index) = GetGrid(rowTri, colTri);
			index++;

			object.GetIndice(index) = GetGrid(rowTri, colTri + 1);
			index++;



			//type 2
			object.GetIndice(index) = GetGrid(rowTri, colTri + 1);
			index++;

			object.GetIndice(index) = GetGrid(rowTri + 1, colTri + 1);
			index++;

			object.GetIndice(index) = GetGrid(rowTri + 1, colTri);
			index++;
		}
	}

	//store the upper and lower boundaries
	lowerBoundary = min;
	UpperBoundary = max;
	return true;
}


int Function::GetGrid(const int& x, const int& y)
{
	//do some checks first
	if (x < 0 || x >= Xgrid)
	{
		uString::ErrorPrint("Trying to acess a grid location outofboundies on the x axis");
	}
	else if (y < 0 || y >= Ygrid)
	{
		uString::ErrorPrint("Trying to acess a grid location outofboundies on the y axis");
	}

	return x * Ygrid + y;
}



Mesh& Function::GetObject()
{
	return object;
}

void Function::SetDrawable(bool state)
{
	
	if(state == true)
	{
		//can on draw a function if there is an equation to draw
		if(equation.GetLen() != 0)
		{
			this->drawable = true;
		}
		else
		{
			this->drawable = false;
		}
	}
	else
	{
		this->drawable = false;
	}
}


bool Function::IsDrawable()
{
	return this->drawable;
}


Vector Function::GetLowerBoundary()
{
	return this->lowerBoundary;
}


Vector Function::GetUpperBoundary()
{
	return this->UpperBoundary;
}