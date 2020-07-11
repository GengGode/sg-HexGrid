#pragma once
#include<iostream>
#include<Windows.h>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

namespace gh
{
	class sgException
	{
	public:
		string msg;
		sgException(string s) : msg(s) {}
	};

	enum SixGridMode
	{
		sgMode0 = 0,
		sgMode1 = 1
	};
	class grid
	{
	public:
		grid();
		grid(int sgLen_);
		grid(int sgRow_, int sgCol_);
		unsigned char * operator [](int i);

		~grid();

		int row();
		int col();

		void One();
		void Zero();
		void Rand();
		void Rand(double sgSurvivalRate_);
		void SetRow(int sgRow_);
		void SetCol(int sgCol_);
	private:
		int sgRow = 0;
		int sgCol = 0;
		unsigned char **sgMat256V = nullptr;
	};

	class pic
	{
	public:
		pic();
		pic(int sgLen_);
		pic(int sgRow_, int sgCol_);
		
		void set(int sgRow_, int sgCol_);
	private:
		int sgRow = 1280;
		int sgCol = 720;
		Mat sgImg = Mat(1280, 720, CV_8UC3);
		
	};
	class sigr
	{
	public:
		sigr();
		sigr(int pRow_, int pCol_);

	private:
		grid g;
		pic p;
		char *sgWindowName = (char*)"Undefined";
	};

}
/*
namespace ghm
{
	class sgArray;

	class Matrix
	{
	public:
		Matrix(int r = 0, int c = 0);
		class sgArray
		{
			friend class Matrix;
		public:
			int & operator[](int j) const; //列标
		private:
			int row;
			int * sgArr;
		};
		sgArray & operator[](int i) const //行标
		{
			return sgArr[i];
		}
	private:
		int row;
		int col;
		sgArray * sgArr;
	};

	Matrix::Matrix(int r, int c)
	{

		row = r;
		col = c;
		int i, j;
		row = r;
		sgArr = new sgArray[r];
		for (i = 0; i < c; i++)
		{
			sgArr[i].sgArr = new int[c];
			sgArr[i].row = c;
		}
		for (i = 0; i < r; i++)
		{
			for (j = 0; j < c; j++)
			{
				sgArr[i].sgArr[j] = i * col + j;
			}
		}
	}

	int & Matrix::sgArray::operator [](int j) const
	{
		return sgArr[j];
	}
}
*/