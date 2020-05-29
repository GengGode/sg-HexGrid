#include <opencv2/opencv.hpp>
#include<Windows.h>
#include<iostream>
using  namespace std;
using namespace cv;
#include"Cube.h"
#include"Vec.h"

#include"Rander.h"

void Out(Hex hex)
{
	cout << "Hex: | " << hex.x << " , " << hex.y << " , " << hex.z << " |" << endl;
}
void Out(Cube cube)
{
	cout << "Cube: | " << cube.x << " , " << cube.y << " , " << cube.z << " | " << cube.mode << " | " << cube.legalFlag <<" |"<< endl;
}
int main()
{
	Cube c(2,-2,0);
	Hex h1(1, 2, 3);
	Hex h2(1);
	Out(h1);
	Out(h2);
	Cube c2(h2);
	Out(c2);
	//Hex h3 = h2 + h1;
	//Out(h3);
	//Out(h2 - h1);
	//Out(h1 - h2);
	//Vec v1(1, 2);
	//Vec v2(v1);

	char name[] = "img";
	Rander rander;
	rander.show(name);

	system("pause");
	return 0;
}
