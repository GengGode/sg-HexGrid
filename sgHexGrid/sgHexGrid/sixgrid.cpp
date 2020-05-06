#include"sixgrid.h"

namespace sg
{

	Offset sgOffsettoCube(Cube cube)
	{
		Offset offset;
		offset.mode = cube.mode;
		/*switch (offset.mode.Mode0)
		{
			case (sgMode0):
			{
				switch (offset.mode.Mode1)
				{
					case (sgMode0):
					{
						offset.col = cube.x + (cube.z + (cube.z & 1)) / 2;
						offset.row = cube.z;
						break;
					}
					case (sgMode1):
					{
						offset.col = cube.x + (cube.z - (cube.z & 1)) / 2;
						offset.row = cube.z;
						break;
					}
				}
				break;
			}
			case (sgMode1):
			{
				switch (offset.mode.Mode1)
				{
					case (sgMode0):
					{
						offset.col = cube.x;
						offset.row = cube.z + (cube.x + (cube.x & 1)) / 2;
						break;
					}
					case (sgMode1):
					{
						offset.col = cube.x;
						offset.row = cube.z + (cube.x - (cube.x & 1)) / 2;
						break;
					}
				}
				break;
			}
		}*/
		/*offset.col = cube.x;
		offset.row = cube.z;*/
		switch (offset.mode.Mode0)
		{
			case (sgMode0):
			{
				switch (offset.mode.Mode1)
				{
					case (sgMode0):
					{
						offset.col = cube.x + (cube.z & 1);
						offset.row = cube.z;
						break;
					}
					case (sgMode1):
					{
						offset.col = cube.x + (cube.z - (cube.z & 1)) / 2;
						offset.row = cube.z;
						break;
					}
				}
				break;
			}
			case (sgMode1):
			{
				switch (offset.mode.Mode1)
				{
					case (sgMode0):
					{
						offset.col = cube.x;
						offset.row = cube.z + (cube.x + (cube.x & 1)) / 2;
						break;
					}
					case (sgMode1):
					{
						offset.col = cube.x;
						offset.row = cube.z + (cube.x - (cube.x & 1)) / 2;
						break;
					}
				}
				break;
			}
		}
		return offset;
	}

	int sgParity(int In)
	{
		int Out = 0;
		In % 2 ? Out = 0 : Out = 1;
		return Out;
	}
	int sgLogic(int In)
	{
		int Out = 0;
		In <= 0 ? Out = 0 : Out = 1;
		return Out;
	}
	int sgSign(int In)
	{
		//In % 2 ? return -1 : return 1;
		int Out = 0;
		In % 2 ? Out = -1 : Out = 1;
		return Out;
	}

	int sgSum6(int In[6])
	{
		int Out = 0;
		for (int i = 0; i < 6; i++)
		{
			//Out = Out + In[0][i];
			if (In[i] == 1)
			{
				Out = Out + 1;
			}
			else
			{
				Out = Out + 0;
			}

		}
		return Out;
	}
	int sgSum6(int In[1][6])
	{
		int Out = 0;
		for (int i = 0; i < 6; i++)
		{
			//Out = Out + In[0][i];
			if (In[0][i] == 1)
			{
				Out = Out + 1;
			}
			else
			{
				Out = Out + 0;
			}

		}
		return Out;
	}
	int sgSum6(int In[6][1])
	{
		int Out = 0;
		for (int i = 0; i < 6; i++)
		{
			//Out = Out + In[0][i];
			if (In[i][0] == 1)
			{
				Out = Out + 1;
			}
			else
			{
				Out = Out + 0;
			}

		}
		return Out;
	}

	int sgMaxRow(Grid In)
	{
		double maxPic[2][6] = { 0 };
		SixGrid(maxPic, In.sgRow, In.sgCol, DEFAULT_R, DEFAULT_LINEWIDTH);
		double Out = maxPic[1][0];

		for (int i = 0; i < 6; i++)
		{
			if (maxPic[1][i] > Out)
			{
				Out = maxPic[1][i];
			}
		}
		return (int) (Out + 0.5);
	}
	int sgMaxCol(Grid In)
	{
		double maxPic[2][6] = { 0 };
		SixGrid(maxPic, In.sgRow, In.sgCol, DEFAULT_R, DEFAULT_LINEWIDTH);
		double Out = maxPic[0][0];

		for (int i = 0; i < 6; i++)
		{
			if (maxPic[0][i] > Out)
			{
				Out = maxPic[0][i];
			}
		}
		return (int) (Out + 0.5);
	}
	int sgSumGrid(Grid In)
	{
		int sum = 0;
		for (int i = 0; i < In.sgRow; i++)
			for (int j = 0; j < In.sgCol; j++)
				sum += In.sgMat[i][j];
		return sum;
	}



	int sgRuleInputCount(char In[10])
	{
		int Ini = 0;
		int count = 0;
		for (int i = 0; i < 10; i++)
		{
			Ini = In[i] - 48;
			if (Ini >= 0 && Ini <= 6)
				count += 1;
		}
		if (count <= 0)
			count = 1;
		
		return count;
	}
	int* sgRuleInputLis(char In[10])
	{
		int Ini = 0;
		int count = 0;
		int Out[10] = { 0 };
		for (int i = 0; i < 10; i++)
		{
			Ini = In[i]-48;
			if (Ini >= 0 && Ini <= 6)
			{
				Out[count] = Ini;
				count += 1;
			}
		}
		
		if (count <= 0)
		{
			count = 1;
			Out[0] = 1;
		}

		int *out = new int[count];
		for (int i = 0; i < count; i++)
		{
			out[i] = Out[i];
		}
		return out;
	}

	bool sgIsSub(int N, Rule lis)
	{
		for (int i = 0; i < lis.count; i++)
			if (N == lis.lis[i])
				return true;
		return false;
	}
	bool sgIsSub(int N, int lisN[7])
	{
		for (int i = 0; i < 7; i++)
			if (N == lisN[i])
				return true;
		return false;
	}

	void reG(Grid G, Grid Gn)
	{
		int TempMat;
		int i, j;
		for (i = 0; i < G.sgRow; i++)
		{
			for (j = 0; j < G.sgCol; j++)
			{
				TempMat = G.sgMat[i][j];
				G.sgMat[i][j] = Gn.sgMat[i][j];
				Gn.sgMat[i][j] = TempMat;
			}
		}

	}

	void NextStep(sg::GridMode Mode, Grid G, Grid Gn)
	{
		int i, j;
		int sumGrid = 0;
		int NeighLocal[2][6] = { 0 };
		int NeighData[1][6] = { 0 };
		int NumE[7] = { 2,2,2,2,2,2,2};
		int NumD[7] = { 2,2,2,2,2,2,2};
		for (i = 0; i < G.sgRow; i++)
		{
			for (j = 0; j < G.sgCol; j++)
			{
				NeighborhoodLocal(Mode, i, j, NeighLocal);
				NeighborhoodData(G, NeighLocal, NeighData);
				sumGrid = sgSum6(NeighData);
				if (G.sgMat[i][j] == 1)
				{   
					//36 13
					if (sgIsSub(sumGrid, NumE))
					{
						Gn.sgMat[i][j] = 1;
					}
					else
					{
						Gn.sgMat[i][j] = 0;
					}
				}
				else if (G.sgMat[i][j] == 0)
				{
					//1235 132
					if (sgIsSub(sumGrid, NumD))
					{
						Gn.sgMat[i][j] = 1;
					}
					else
					{
						Gn.sgMat[i][j] = 0;
					}
				}
			}
		}
	}
	void NextStep(sg::GridMode Mode, Grid G, Grid Gn, Rules H)
	{
		int i, j;
		int sumGrid = 0;
		int NeighLocal[2][6] = { 0 };
		int NeighData[1][6] = { 0 };
		for (i = 0; i < G.sgRow; i++)
		{
			for (j = 0; j < G.sgCol; j++)
			{
				NeighborhoodLocal(Mode, i, j, NeighLocal);
				NeighborhoodData(G, NeighLocal, NeighData);
				sumGrid = sgSum6(NeighData);
				if (G.sgMat[i][j] == 1)
				{
					//36 13
					if (sgIsSub(sumGrid, H.hExist))
					{
						Gn.sgMat[i][j] = 1;
					}
					else
					{
						Gn.sgMat[i][j] = 0;
					}
				}
				else if (G.sgMat[i][j] == 0)
				{
					//1235 132
					if (sgIsSub(sumGrid, H.hDeath))
					{
						Gn.sgMat[i][j] = 0;
					}
					else
					{
						Gn.sgMat[i][j] = 1;
					}
				}
			}
		}
	}

	Grid GridCreate(int row, int col)
	{
		int i, j;
		Grid G;
		G.sgRow = row;
		G.sgCol = col;
		G.sgMat = new int*[row];
		for (i = 0; i < row; i++)
		{
			G.sgMat[i] = new int[col];
			for (j = 0; j < col; j++)
			{
				G.sgMat[i][j] = 0;
			}
		}
		return G;
	}
	/*
	void GridCreate(int row,int col,Grid G)
	{
		int i, j;
		G.sgRow = row;
		G.sgCol = col;
		G.sgMat = new int*[row];
		for (i=0;i<row;i++)
		{
			G.sgMat[i] = new int[col];
			for (j = 0; j < col; j++)
			{
				G.sgMat[i][j] = 0;
			}
		}
	}
	*/
	void SixGrid(double In[2][6], int m, int n, double r, int lineWidth)
	{
		double pi = 3.1415, root3 = 1.7321*(r + lineWidth);
		double theta0 = 0.5236;
		double theta[6] = { 0, 1.0471, 2.0943, 3.1415, 4.1887, 5.2359 };
		double cosTheta[6] = { 0.8660,0,-0.8660,-0.8660,0,0.8660 };
		double sinTheta[6] = { 0.5,1,0.5,-0.5,-1,-0.5 };
		double dx, dy;

		n % 2 ? dx = (m - 0.25) * root3 : dx = (m + 0.25)* root3;
		dy = (r + lineWidth) * n * 3 / 2;

		for (int k = 0; k < 6; k++)
		{
			In[0][k] = dx + r * cosTheta[k];
			In[1][k] = dy + r * sinTheta[k];
		}
	}

	void GridImg(Mat Img, int p, int q, Scalar C)
	{
		int dx = DEFAULT_R, dy = DEFAULT_R;
		Point point[1][6];
		int np[] = { 6 };
		double grid[2][6];
		const Point* pp[1] = { point[0] };

		SixGrid(grid, p, q, DEFAULT_R, DEFAULT_LINEWIDTH);

		for (int k = 0; k < 6; k++)
		{
			point[0][k] = Point(cvCeil(grid[0][k] + dx), cvCeil(grid[1][k] + dy));
		}
		fillPoly(Img, pp, np, 1, C, 1);
	}

	void GridShow(Mat Img, Grid Data)
	{
		int i, j;

		for (i = 0; i < Data.sgRow; i++)
		{
			for (j = 0; j < Data.sgCol; j++)
			{
				if (Data.sgMat[i][j] == 0)
				{
					GridImg(Img, i, j, Scalar(255, 255, 255));
				}
				else if (Data.sgMat[i][j] == 1)
				{
					GridImg(Img, i, j, Scalar(0, 0, 0));
				}

			}
		}
	}

	void NeighborhoodLocal(sg::GridMode Mode, int x, int y, int NeighLocal[2][6])
	{
		int i;
		//x = x + 1;
		//y = y + 1;
		switch (Mode.Mode0)
		{
		case sgMode0:
		{
			switch (Mode.Mode1)
			{
			case sgMode0:
			{
				i = 1;
				NeighLocal[0][i - 1] = x - sgParity(y + 1);
				NeighLocal[1][i - 1] = y + 1;
				i = 2;
				NeighLocal[0][i - 1] = x - 1;
				NeighLocal[1][i - 1] = y;
				i = 3;
				NeighLocal[0][i - 1] = x - sgParity(y + 1);
				NeighLocal[1][i - 1] = y - 1;
				i = 4;
				NeighLocal[0][i - 1] = x + sgParity(y);
				NeighLocal[1][i - 1] = y - 1;
				i = 5;
				NeighLocal[0][i - 1] = x + 1;
				NeighLocal[1][i - 1] = y;
				i = 6;
				NeighLocal[0][i - 1] = x + sgParity(y);
				NeighLocal[1][i - 1] = y + 1;
				break;
			}
			case sgMode1:
			{
				i = 1;
				NeighLocal[0][i - 1] = x - sgParity(y);
				NeighLocal[1][i - 1] = y + 1;
				i = 2;
				NeighLocal[0][i - 1] = x - 1;
				NeighLocal[1][i - 1] = y;
				i = 3;
				NeighLocal[0][i - 1] = x - sgParity(y);
				NeighLocal[1][i - 1] = y - 1;
				i = 4;
				NeighLocal[0][i - 1] = x + sgParity(y + 1);
				NeighLocal[1][i - 1] = y - 1;
				i = 5;
				NeighLocal[0][i - 1] = x + 1;
				NeighLocal[1][i - 1] = y;
				i = 6;
				NeighLocal[0][i - 1] = x + sgParity(y + 1);
				NeighLocal[1][i - 1] = y + 1;
				break;
			}
			}
			break;
		}
		case sgMode1:
		{
			switch (Mode.Mode1)
			{
			case sgMode0:
			{
				i = 1;
				NeighLocal[0][i - 1] = x;
				NeighLocal[1][i - 1] = y + 1;
				i = 2;
				NeighLocal[0][i - 1] = x - 1;
				NeighLocal[1][i - 1] = y + sgParity(x);
				i = 3;
				NeighLocal[0][i - 1] = x - 1;
				NeighLocal[1][i - 1] = y - sgParity(x + 1);
				i = 4;
				NeighLocal[0][i - 1] = x;
				NeighLocal[1][i - 1] = y - 1;
				i = 5;
				NeighLocal[0][i - 1] = x + 1;
				NeighLocal[1][i - 1] = y - sgParity(x + 1);
				i = 6;
				NeighLocal[0][i - 1] = x + 1;
				NeighLocal[1][i - 1] = y + sgParity(x);
				break;
			}
			case sgMode1:
			{
				i = 1;
				NeighLocal[0][i - 1] = x;
				NeighLocal[1][i - 1] = y + 1;
				i = 2;
				NeighLocal[0][i - 1] = x - 1;
				NeighLocal[1][i - 1] = y + sgParity(x + 1);
				i = 3;
				NeighLocal[0][i - 1] = x - 1;
				NeighLocal[1][i - 1] = y - sgParity(x);
				i = 4;
				NeighLocal[0][i - 1] = x;
				NeighLocal[1][i - 1] = y - 1;
				i = 5;
				NeighLocal[0][i - 1] = x + 1;
				NeighLocal[1][i - 1] = y - sgParity(x);
				i = 6;
				NeighLocal[0][i - 1] = x + 1;
				NeighLocal[1][i - 1] = y + sgParity(x + 1);
				break;
			}
			}
			break;
		}
		}
	}

	void NeighborhoodData(Grid Data, int NeighLocal[2][6], int NeighData[1][6])
	{
		for (int i = 0; i < 6; i++)
		{
			
			if ((NeighLocal[0][i] >= 0 && NeighLocal[0][i] < Data.sgRow) && (NeighLocal[1][i] >= 0 && NeighLocal[1][i] < Data.sgCol))
			{
				NeighData[0][i] = Data.sgMat[NeighLocal[0][i]][NeighLocal[1][i]];
			}
			else
			{
				NeighData[0][i] = 0;
			}
			if ((NeighData[0][i] != 0) && (NeighData[0][i] != 1))
			{
				NeighData[0][i] = 0;
			}
		}
	}

	BOOL CALLBACK EnumWindowsProc_0(HWND hWnd, LPARAM IProgress)
	{
		if (::FindWindowEx(hWnd, NULL, "SHELLDLL_DefView", NULL) != NULL)
		{
			HWND tempHwnd = ::FindWindowEx(NULL, hWnd, "WorkerW", NULL);
			::ShowWindow(tempHwnd, 0);
		}
		return true;
	}

	void SetDesktop(char FormName[])
	{
		HWND hWnd = ::FindWindow("Progman", NULL);
		HWND my_hWnd = ::FindWindow(NULL, FormName);

		if (hWnd != NULL && my_hWnd != NULL)
		{
			MoveWindow(my_hWnd, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), true);
			SendMessageTimeout(hWnd, 0x52c, NULL, NULL, 0, 0x3e8, NULL);
			EnumWindows(EnumWindowsProc_0, NULL);
			SetParent(my_hWnd, hWnd);
		}
	}

	void sgInitializationWindows(char fGrid[],char fBar[],char fCon[])
	{
		HWND h_FormGrid = ::FindWindow(NULL,fGrid);
		HWND h_FormBar = ::FindWindow(NULL,fBar);
		HWND h_FormCon = ::FindWindow(NULL,fCon);
		RECT rctGrid;
		RECT rctBar;
		RECT rctCon;

		if (h_FormGrid != NULL)
		{
			GetWindowRect(h_FormGrid, &rctGrid);
			MoveWindow(h_FormGrid, 10, 10, rctGrid.right - rctGrid.left, rctGrid.bottom - rctGrid.top, true);
		}
		if (h_FormBar != NULL)
		{
			GetWindowRect(h_FormBar, &rctBar);
			MoveWindow(h_FormBar, rctGrid.right + 10, rctGrid.top, rctBar.right - rctBar.left, rctBar.bottom - rctBar.top, true);
		}
		if (h_FormCon != NULL)
		{
			GetWindowRect(h_FormCon, &rctCon);
			MoveWindow(h_FormCon, rctGrid.right + 10, rctBar.bottom, 600, rctCon.bottom- rctCon.top, true);
		}
	}
	void sgGetExePath(char In[260])
	{
		//char conPath[MAX_PATH];
		GetModuleFileName(NULL, (LPSTR) In, 260);
	}
}

/*
	Gri::Gri()
	{
		;//
	}

	Gri::Gri(int lens)
	{
		dim = 1;
		row = 1;
		col = lens;
		sgMat = new int*[1];
		sgMat[0] = new int[lens];
	}

	Gri::Gri(int rows, int cols)
	{
		//int **sgMat;      //动态申请二维数组 n行 m列
		dim = 2;
		row = rows;
		col = cols;
		sgMode.Mode0 = sgMode0;
		sgMode.Mode1 = sgMode1;
		sgMat = new int*[rows];
		for (int i = 0; i < rows; i++)
			sgMat[i] = new int[cols];
	}

	Gri::Gri(int rows, int cols, GridMode Mode)
	{
		dim = 2;
		row = rows;
		col = cols;

		sgMode = Mode;
		sgMat = new int*[rows];
		for (int i = 0; i < rows; i++)
			sgMat[i] = new int[cols];
	}
	*/

