#pragma once
#include "BasePointCenter.h"
class PointCenter :
	public BasePointCenter
{
public:
	int ceil(double In);
	virtual void Corter(double r);
protected:
	BasePointCenter plusX;
	BasePointCenter plusY;
	BasePointCenter plusZ;
	BasePointCenter minuX;
	BasePointCenter minuY;
	BasePointCenter minuZ;
};

