#include "sigr.h"

gh::grid::grid() :grid(4, false) {}

gh::grid::grid(int sgLen_):grid(sgLen_,false) {}

gh::grid::grid(int sgLen_, bool sgMode_):grid(sgLen_, sgLen_, sgMode_) {}

gh::grid::grid(int sgRow_, int sgCol_) :grid(sgRow_, sgCol_, false) {}

gh::grid::grid(int sgRow_, int sgCol_, bool sgMode_): sgRow(sgRow_), sgCol(sgCol_)
{
	sgMat256V = new unsigned char*[sgRow_];
	for (int i = 0; i < sgRow_; i++)
	{
		sgMat256V[i] = new unsigned char[sgCol_]();
	}
	/*
	sgMode = sgMode_;
	if (sgMode)
	{
		sgMat256V = new unsigned char*[sgRow_];
		for (int i = 0; i < sgRow_; i++)
		{
			sgMat256V[i] = new unsigned char[sgCol_]();
			
			sgMat256V[i] = new unsigned char[sgCol_];
			for (int j = 0; j < sgCol_; j++)
			{
				sgMat256V[i][j] = 0;
			}
			
		}
	}
	else
	{
		sgMat2V = new bool*[sgRow_];
		for (int i = 0; i < sgRow_; i++)
		{
			sgMat2V[i] = new bool[sgCol_]();
			
			sgMat2V[i] = new bool[sgCol_];
			for (int j = 0; j < sgCol_; j++)
			{
				sgMat2V[i][j] = 0;
			}
			
		}
	}
	*/
}

int gh::grid::row()
{
	return sgRow;
}

int gh::grid::col()
{
	return sgCol;
}

int gh::grid::mode()
{
	return sgMode;
}

int gh::grid::range()
{
	return sgMode ? 256 : 2;
}

unsigned char * gh::grid::operator[](int i)
{
	if (sgMode)
	{
		return  sgMat256V[i];
	}
	else
	{
		return  sgMat2V[i];
	}
}
