#include<Windows.h>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#ifndef SIXGRID_H
#define SIXGRID_H

#define DEFAULT_R 4.2  //3.6
#define DEFAULT_LINEWIDTH 1.2  //1.8

namespace sg
{
	enum SixGridMode
	{
		sgMode0=0,
		sgMode1=1
	};

	struct GridMode
	{
		SixGridMode Mode0;
		SixGridMode Mode1;
		GridMode(){
			Mode0 = sgMode0;
			Mode1 = sgMode0;
		}
		GridMode(SixGridMode Mode0_) :Mode0(Mode0_), Mode1(Mode0_) {}
		GridMode(SixGridMode Mode0_, SixGridMode Mode1_):Mode0(Mode0_), Mode1(Mode1_) {}
		bool operator ==(const GridMode In)
		{
			if (this->Mode0 == In.Mode0&&this->Mode1 == In.Mode1)
				return true;
			else
				return false;
		}
	};
	
	struct Grid
	{
		//int sgDim;
		int sgRow;
		int sgCol;
		int **sgMat;
		Grid() {}
		Grid(int len_) :sgRow(len_), sgCol(len_) {
			sgMat = new int*[len_];
			for (int i = 0; i < len_; i++)
			{
				sgMat[i] = new int[len_];
				for (int j = 0; j < len_; j++)
				{
					sgMat[i][j] = 0;
				}
			}
		}
		Grid(int sgRow_, int sgCol_) :sgRow(sgRow_),sgCol(sgCol_) {
			sgMat = new int*[sgRow_];
			for (int i = 0; i < sgRow_; i++)
			{
				sgMat[i] = new int[sgCol_];
				for (int j = 0; j < sgCol_; j++)
				{
					sgMat[i][j] = 0;
				}
			}
		}
		void Rand()
		{
			for (int i = 0; i < sgRow; i++)
				for (int j = 0; j < sgCol; j++)
					if (rand() % 100 <= 20)
						sgMat[i][j] = 1;
					else
						sgMat[i][j] = 0;
		}
		void Rand(int k)
		{
			for (int i = 0; i < sgRow; i++)
				for (int j = 0; j < sgCol; j++)
					if (rand() % 100 <= k)
						sgMat[i][j] = 1;
					else
						sgMat[i][j] = 0;
		}
	}; 

	struct GridImage
	{
		Grid grid;
		Mat mat;
		GridImage(Grid grid_, Mat mat_) :grid(grid_), mat(mat_) {}
	};

	struct Rule
	{
		int *lis;
		int count;
		Rule(){}
		Rule(int Lis_[20])
		{
			int tmp[20];
			for (int i = 0; i < 20; i++)tmp[i] = Lis_[i];
			count=sizeof(Lis_) / sizeof(Lis_[0]);
			if (count > 20)count = 20;
			for(int i=0;i<count;i++)
				lis[i] = Lis_[i];
		}
		Rule(int *lis_,int count_):count(count_) {
			//if (count != sizeof(lis_) / sizeof(lis_[0]))
			//	if (count <= sizeof(lis_) / sizeof(lis_[0]))
			//		count = sizeof(lis_) / sizeof(lis_[0]);
			lis = new int[count];
			for (int i = 0; i < count; i++)
				lis[i] = lis_[i];
			//cout << lis << endl;
		}
		void out()
		{
			for (int i = 0; i < count; i++)
				cout << " " << lis[i];
			cout << "\n" << count << endl;
		}
	};

	struct Rules
	{
		Rule hExist;
		Rule hDeath;
		Rules() {}
		Rules(Rule hExist_,Rule hDeath_):hExist(hExist_), hDeath(hDeath_) {}
	};

	
	struct Offset
	{
		int col;
		int row;
		GridMode mode;
		Offset() {}
		Offset(int col_,int row_):col(col_),row(row_){
			mode.Mode0 = sgMode0;
			mode.Mode1 = sgMode0;
		}
		Offset(int col_, int row_, GridMode mode_):col(col_), row(row_),mode(mode_) {}
		Offset(int col_, int row_, SixGridMode mode0_) :col(col_), row(row_) {
			mode.Mode0 = mode0_;
			mode.Mode1 = mode0_;
		}
		Offset(int col_, int row_, SixGridMode mode0_, SixGridMode mode1_) :col(col_), row(row_) {
			mode.Mode0 = mode0_;
			mode.Mode1 = mode1_;
		}
		//Offset(Cube cube_)
		/*Offset(Cube cube_) {
			mode = cube_.mode;
			switch (mode.Mode0)
			{
				case (sgMode0):
				{
					switch (mode.Mode1)
					{
						case (sgMode0):
						{
							q = cube_.x + (cube_.z + (cube_.z & 1)) / 2;
							r = cube_.z;
							break;
						}
						case (sgMode1):
						{
							q = cube_.x + (cube_.z - (cube_.z & 1)) / 2;
							r = cube_.z;
							break;
						}
					}
					break;
				}
				case (sgMode1):
				{
					switch (mode.Mode1)
					{
						case (sgMode0):
						{
							q = cube_.x ;
							r = cube_.z + (cube_.x + (cube_.x & 1)) / 2;
							break;
						}
						case (sgMode1):
						{
							q = cube_.x;
							r = cube_.z + (cube_.x - (cube_.x & 1)) / 2;
							break;
						}
					}
					break;
				}
			}
		}*/
		void sgCout()
		{
			cout << "Offset: " << col << " , " << row<< endl;
		}
	};
	
	struct Cube
	{
		int x;
		int y;
		int z;
		GridMode mode;
		Cube() {}
		Cube(int x_,int y_,int z_):x(x_),y(y_),z(z_){
			mode.Mode0 = sgMode0;
			mode.Mode1 = sgMode0;
		}
		Cube(int x_, int y_, int z_, GridMode mode_) :x(x_), y(y_), z(z_), mode(mode_) {}
		Cube(int x_, int y_, int z_, SixGridMode mode0_) :x(x_), y(y_), z(z_) {
			mode.Mode0 = mode0_;
			mode.Mode1 = mode0_;
		}
		Cube(int x_, int y_, int z_, SixGridMode mode0_, SixGridMode mode1_) :x(x_), y(y_), z(z_) {
			mode.Mode0 = mode0_;
			mode.Mode1 = mode1_;
		}
		Cube(Offset offset_){
			mode = offset_.mode;
			/*switch (mode.Mode0)
			{
				case (sgMode0):
				{
					switch (mode.Mode1)
					{
						case (sgMode0):
						{
							x = offset_.col - (offset_.col + (offset_.col & 1)) / 2;
							z = offset_.row;
							y = -x - z;
							break;
						}
						case (sgMode1):
						{
							x = offset_.col - (offset_.row - (offset_.row & 1)) / 2;
							z = offset_.row;
							y = -x - z;
							break;
						}
					}
					break;
				}
				case (sgMode1):
				{
					switch (mode.Mode1)
					{
						case (sgMode0):
						{
							x = offset_.col;
							z = offset_.row - (offset_.col + (offset_.col & 1)) / 2;
							y = -x - z;
							break;
						}
						case (sgMode1):
						{
							x = offset_.col;
							z = offset_.row - (offset_.col - (offset_.col & 1)) / 2;
							y = -x - z;
							break;
						}
					}
					break;
				}
			}*/
			x = offset_.col;
			z = offset_.row;
			y = -x - z;
		}

		void sgCout()
		{
			cout << "Cube: " << x << " , " << y << " , " << z << endl;
		}
		Cube operator + (const Cube In) const 
		{
			Cube cube;
			cube.mode = this->mode;
			if (this->mode.Mode0 == In.mode.Mode0&&this->mode.Mode1 == In.mode.Mode1)
			{
				cube.x = In.x + this->x;
				cube.y = In.y + this->y;
				cube.z = In.z + this->z;
			}
			else
			{
				cube.x = 0;
				cube.y = 0;
				cube.z = 0;
			}

			return cube;

		}
	};
	
	Offset sgOffsettoCube(Cube cube);

	int sgCeil(double In);

	int sgParity(int In);
	int sgLogic(int In);
	int sgSign(int In);

	int sgSum6(int In[6]);
	int sgSum6(int In[1][6]);
	int sgSum6(int In[6][1]);

	int sgMaxRow(Grid In);
	int sgMaxCol(Grid In);
	int sgSumGrid(Grid In);

	int sgRuleInputCount(char In[10]);
	int* sgRuleInputLis(char In[10]);


	bool sgIsSub(int N, Rule lis);
	bool sgIsSub(int N, int lisN[7]);

	void reG(Grid G, Grid Gn);

	void NextStep(sg::GridMode Mode, Grid G, Grid Gn);
	void NextStep(sg::GridMode Mode, Grid G, Grid Gn, Rules H);

	Grid GridCreate(int row, int col);
	//void GridCreate(int row, int col, Grid G);
	void SixGrid(double In[2][6], int m, int n, double r, double lineWidth);
	void GridImg(Mat Img, int p, int q, Scalar C);

	void GridShow(Mat Img, Grid Data);

	void sgGridSet6Point(Grid G, int In[2][6], int Stata);

	void NeighborhoodLocal(sg::GridMode Mode, int x, int y, int NeighLocal[2][6]);
	void NeighborhoodData(Grid Data, int NeighLocal[2][6], int NeighData[1][6]);


	void NextStep2(sg::GridMode Mode, Grid G, Grid Gn, Rules H);
	void NeighborhoodLocal2(sg::GridMode Mode, int x, int y, int NeighLocal[2][6]);

	void NextStep3(sg::GridMode Mode, Grid G, Grid Gn, Rules H);
	void NeighborhoodLocal3(sg::GridMode Mode, int x, int y, int NeighLocal[2][6]);


	BOOL CALLBACK EnumWindowsProc_0(HWND hWnd, LPARAM IProgress);
	void SetDesktop(char FormName[]);
	void sgInitializationWindows(char fGrid[], char fBar[], char fCon[]);
	void sgGetExePath(char In[260]);
}
#elif SIXGRID_H_TEST
/*
namespace sg
{
	struct GridMode
	{
		char Mode0;
		char Mode1;
	};
	void SixGrid(double In[2][6], int m, int n, double r, int lineWidth);
	void GridImg(Mat Img, int p, int q, Scalar C);
}
*/
#endif

/*
class Gri
{
public:
	Gri();

	Gri(int lens);

	Gri(int rows, int cols);

	Gri(int rows, int cols, GridMode Mode);

private:
	int dim;
	int row;
	int col;
	GridMode sgMode;
	int **sgMat;
};
*/
