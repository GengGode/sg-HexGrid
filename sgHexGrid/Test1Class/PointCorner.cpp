#include "PointCorner.h"
void PointCornerH::Corner(double r)
{
	double xCos[] = { 0.866025, 0., -0.866025, -0.866025, 0., 0.866025 };
	double ySin[] = { 0.5, 1., 0.5, -0.5, -1., -0.5 };
	plusX.xy(ceil(r*xCos[0]), ceil(r*ySin[0]));
	plusY.xy(ceil(r*xCos[1]), ceil(r*ySin[1]));
	plusZ.xy(ceil(r*xCos[2]), ceil(r*ySin[2]));
	minuX.xy(ceil(r*xCos[3]), ceil(r*ySin[3]));
	minuY.xy(ceil(r*xCos[4]), ceil(r*ySin[4]));
	minuZ.xy(ceil(r*xCos[5]), ceil(r*ySin[5]));
}

void PointCornerS::Corner(double r)
{
	double xCos[] = { 1., 0.5, -0.5, -1., -0.5, 0.5 };
	double ySin[] = { 0.,0.866025,0.866025,0.,-0.866025,-0.866025 };
	plusX.xy(ceil(r*xCos[0]), ceil(r*ySin[0]));
	plusY.xy(ceil(r*xCos[1]), ceil(r*ySin[1]));
	plusZ.xy(ceil(r*xCos[2]), ceil(r*ySin[2]));
	minuX.xy(ceil(r*xCos[3]), ceil(r*ySin[3]));
	minuY.xy(ceil(r*xCos[4]), ceil(r*ySin[4]));
	minuZ.xy(ceil(r*xCos[5]), ceil(r*ySin[5]));
}