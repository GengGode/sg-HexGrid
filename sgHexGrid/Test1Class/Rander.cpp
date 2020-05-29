#include "Rander.h"

Rander::Rander():cols(800),rows(600) 
{
	mat = Mat(rows, cols, CV_8UC3, Scalar(128, 128, 128));
}
Rander::Rander(Mat imat)
{
	mat = imat;
	cols = imat.cols;
	rows = imat.rows;
}
Rander::Rander(int x, int y) : cols(x), rows(y)
{
	mat = Mat(rows, cols, CV_8UC3, Scalar(128, 128, 128));
}
Rander::Rander(int x, int y, Scalar C)
{
	cols = x;
	rows = y;
	mat = Mat(rows, cols, CV_8UC3, C);
}
void Rander::show(char name[])
{
	if (FindWindow(NULL, name) == NULL)
		namedWindow(name);
	imshow(name, mat);

}