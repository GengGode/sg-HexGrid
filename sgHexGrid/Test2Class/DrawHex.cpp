#include "DrawHex.h"
DrawHex::DrawHex()
{

}
DrawHex::~DrawHex()
{

}

void DrawHex::show(char * name)
{
	cvNamedWindow(name);
	cvShowImage(name,render.mat)
}
