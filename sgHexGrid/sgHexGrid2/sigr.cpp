#include "sigr.h"
#include<Windows.h>

gh::grid::grid() :grid(4) {}

gh::grid::grid(int sgLen_):grid(sgLen_, sgLen_) {}

gh::grid::grid(int sgRow_, int sgCol_): sgRow(sgRow_), sgCol(sgCol_)
{
	sgMat256V = new unsigned char*[sgRow_];
	for (int i = 0; i < sgRow_; i++)
	{
		sgMat256V[i] = new unsigned char[sgCol_]();
	}
}

int gh::grid::row()
{
	return sgRow;
}

int gh::grid::col()
{
	return sgCol;
}

void gh::grid::Rand()
{
	for (int i = 0; i < sgRow; i++)
		for (int j = 0; j < sgCol; j++)
			if (rand() % 100 <= sgSurvivalRate)
				sgMat256V[i][j] = 1;
			else
				sgMat256V[i][j] = 0;
}

void gh::grid::Rand(double sgSurvivalRate_)
{
	for (int i = 0; i < sgRow; i++)
		for (int j = 0; j < sgCol; j++)
			if (rand() % 100 <= sgSurvivalRate_)
				sgMat256V[i][j] = 1;
			else
				sgMat256V[i][j] = 0;
}

unsigned char * gh::grid::operator[](int i)
{
	return  sgMat256V[i];
}
