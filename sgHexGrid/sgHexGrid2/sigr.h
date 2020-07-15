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

	enum sgMode
	{
		sgX = 0,
		sgY = 1,
		sgJ = 0,
		sgP = 1
	};

	class sgGridMode
	{
		//网格参数
	public:
		sgGridMode();
		sgGridMode(sgMode u, sgMode v);

	private:
		sgMode sgU = sgX;
		sgMode sgV = sgJ;
	};
	
	class sgCoor
	{
	public:
		sgCoor();
		sgCoor(double x, double y);

		double x();
		double y();
	private:
		double sgX;
		double sgY;
	};

	class sgStateColor
	{
		const Scalar white = Scalar(255, 255, 255);
		const Scalar black = Scalar(0, 0, 0);
	public:
		sgStateColor();
		sgStateColor(int n);
		~sgStateColor();

		Scalar get(int state);
	private:
		unsigned char sgN;
		Scalar *sgColor = nullptr;
		Scalar sgStartStateColor = Scalar(255, 255, 255);
		Scalar sgEndStateColor = Scalar(0, 0, 0);
	};

	class sgUV
	{
	public:
		sgUV();
		sgUV(int u, int v);

	private:
		int sgU;
		int sgV;
	};

	class sgBlock
	{
	public:
		sgBlock();

	private:
		sgUV sgCoor;
		unsigned char sgMat[127][127];
	};

	class sgBlocks
	{
	public:
		sgBlocks();

	private:

		
	};

	class sgRenderRange
	{
	public:
		sgRenderRange();
	private:

	};

	class rule
	{
	public:
		rule();
		rule(int sgNeighborhood_);
		rule(int sgNeighborhood_, int sgState_);

		~rule();

		void set(int sState_, int eState_, int tNeighbor_);
		void set(int sState_, int eState_, int sNeighbor_, int eNeighbor_);

	private:
		sgStateColor sgColor;
		unsigned char sgState;
		unsigned char sgNeighborhood;
		bool ***sgStateTransitionTable;

	};
	
	class conf
	{
	public:
		conf();

		Scalar bgc();
	private:
		Scalar sgBGC = Scalar(128, 128, 128);
		
		sgGridMode sgGM;
		int sgSecConX = 640;
		int sgSecConY = 360;
		double sgTarConX = 0;
		double sgTarConY = 0;
		double r;
		double w;
		double b;
		double dr;
	};
	class grid
	{
	public:
		grid();
		grid(int sgLen_);
		grid(int sgRow_, int sgCol_);
		grid(grid &grid_);
		grid operator =(const grid&grid_);
		unsigned char * operator [](int i);

		~grid();

		int row();
		int col();
		int mat(int i, int j);
		
		void One();
		void Zero();
		void Rand();
		void Rand(double sgSurvivalRate_);
		void SetRow(int sgRow_);
		void SetCol(int sgCol_);
		void SetMat(int i, int j, int n);

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
		
		void set(Scalar c);
		void set(int sgRow_, int sgCol_);
		Mat img();
	private:
		int sgRow = 1280;
		int sgCol = 720;
		Mat sgImg = Mat(1280, 720, CV_8UC3);
		
	};

	class sigr
	{
	public:
		sigr();
		sigr(int pRow_, int pCol_,int gRow_,int gCol_);

		void bgc();
		void draw();
		void show();
	private:
		pic p;
		grid g;
		rule r;
		conf c;
		char *sgWindowName = (char*)"Undefined";
		HWND sgMainForm = nullptr;
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