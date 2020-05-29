#include<Windows.h>
#include<opencv2/opencv.hpp>
using namespace cv;
#pragma once

class Rander
{
public:
	Rander();
	Rander(Mat imat);
	Rander(int x, int y);
	Rander(int x, int y, Scalar C);
	void show(char name[]);
private:
	Mat mat;
	int cols;//->x
	int rows;//->y
	HWND hRander;
};
