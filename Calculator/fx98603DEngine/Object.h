#ifndef OBJECT_H
#define OBJECT_H



#include "Matrix.h"

class Object
{
	Matrix TransMat;
	//needUpdate
	bool needUpdate;
	Matrix InverseMat;
public:

	//constructor
	Object();
	
	bool Scale(const float& x, const float& y, const float& z);
	
	//in degrees
	virtual bool Rotate(const float& angdX, const float& angdY, const float& angdZ);
	
	bool Translation(const float& x, const float& y, const float& z);
	
	Matrix& GetMat();

	Matrix& GetInverse();
};

#endif //OBJECT_H