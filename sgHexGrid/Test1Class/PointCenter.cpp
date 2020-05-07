#include "PointCenter.h"
int PointCenter::ceil(double In)
{
	int Out = (int) In;
	if (In - Out >= 0.5)
		Out = Out + 1;
	return Out;
}