﻿// sgHexGrid2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include"sg2.h"
#include"sigr.h"
using namespace sg;
using namespace gh;


Cube cubeNei[] = {
		Cube(+1, -1, 0), Cube(+1, 0, -1), Cube(0, +1, -1),
			Cube(-1, +1, 0), Cube(-1, 0, +1), Cube(0, -1, +1),
};
int B = 2;
int q = 1;
int r = 1;
int p = 1;
int s = 1;
bool DrawLFlag = false;
bool DrawRFlag = false;
bool DrawBFlag = false;
bool DrawMFlag = false;
char FormGrid[] = "Form Grid";
GridMode MODE;
HexType hexType(4.8, 1.8);
Shifting shi(0);
WheelStep STEP(0.2);
int MODER = 3;

void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
	GridImage& gm = *(sg::GridImage*) param;
	Grid grid = gm.grid;
	Mat mat = gm.mat;
	Offset ohex(q, r);
	Cube ctmp;
	Offset otmp;

	int Nei[2][6] = { 0 };
	int Nei2[2][6] = { 0 };
	int Nei3[2][6] = { 0 };
	int m = 0, n = 0;
	int tm = 0, tn = 0;
	int tm2 = 0, tn2 = 0;

	int tx = 0, ty = 0;

	//double MouseWheelStep = 0.2; 

	switch (event)
	{
		case EVENT_MOUSEMOVE:
		{

			tx = x - shi.x;
			ty = y - shi.y;
			m = sgCeil((sqrt(3) / 3 * tx - 1 / 3 * ty) / (hexType.r + hexType.w));
			n = sgCeil(ty * 2 / 3 / (hexType.r + hexType.w));
			q = m;
			r = n;
			p = m;
			s = n;

			NeighborhoodLocal(MODE, m, n, Nei);
			NeighborhoodLocal2(MODE, m, n, Nei2);
			NeighborhoodLocal3(MODE, p, s, Nei3);

			if (DrawLFlag)
			{
				if (q >= 0 && q < grid.sgRow && r >= 0 && r < grid.sgCol)
					grid.sgMat[q][r] = 1;
				if (B >= 2)for (int i = 0; i < 6; i++)
				{
					sgGridSet6Point(grid, Nei, 1);
					if (B >= 3)
					{
						sgGridSet6Point(grid, Nei2, 1);
						if (B >= 4)
						{
							sgGridSet6Point(grid, Nei3, 1);
						}
					}
				}
			}
			if (DrawRFlag)
			{
				if (p >= 0 && p < grid.sgRow && s >= 0 && s < grid.sgCol)
					grid.sgMat[p][s] = 0;
				if (B >= 2)for (int i = 0; i < 6; i++)
				{
					sgGridSet6Point(grid, Nei, 0);
					if (B >= 3)
					{
						sgGridSet6Point(grid, Nei2, 0);
						if (B >= 4)
						{
							sgGridSet6Point(grid, Nei3, 0);
						}
					}
				}
			}
			if (DrawMFlag)
			{
				shi.x = x - shi.tx;
				shi.y = y - shi.ty;
				//cout << shi.x << " ||| " << shi.y<<endl;
			}


			if (m >= 0 && m < grid.sgRow && n >= 0 && n < grid.sgCol)
			{
				sg::GridImg(mat, m, n, shi, hexType, Scalar(255, 255, 0));
			}
			if (B >= 2)for (int i = 0; i < 6; i++)
			{
				m = Nei[0][i];
				n = Nei[1][i];
				if (m >= 0 && m < grid.sgRow && n >= 0 && n < grid.sgCol)
					sg::GridImg(mat, m, n, shi, hexType, Scalar(255, 255, 0));
				if (B >= 3)
				{
					m = Nei2[0][i];
					n = Nei2[1][i];
					if (m >= 0 && m < grid.sgRow && n >= 0 && n < grid.sgCol)
						sg::GridImg(mat, m, n, shi, hexType, Scalar(255, 255, 0));
					if (B >= 4)
					{
						m = Nei3[0][i];
						n = Nei3[1][i];
						if (m >= 0 && m < grid.sgRow && n >= 0 && n < grid.sgCol)
							sg::GridImg(mat, m, n, shi, hexType, Scalar(255, 255, 0));
					}
				}
			}
			imshow(FormGrid, mat);
		}
		break;
		case EVENT_LBUTTONDOWN:
		{
			DrawLFlag = true;
			tx = x - shi.x;
			ty = y - shi.y;
			q = sgCeil((sqrt(3) / 3 * tx - 1 / 3 * ty) / (hexType.r + hexType.w));
			r = sgCeil(ty * 2 / 3 / (hexType.r + hexType.w));

			NeighborhoodLocal(MODE, q, r, Nei);
			NeighborhoodLocal2(MODE, q, r, Nei2);
			NeighborhoodLocal3(MODE, p, s, Nei3);

			if (q >= 0 && q < grid.sgRow && r >= 0 && r < grid.sgCol)
				grid.sgMat[q][r] = 1;
			if (B >= 2)for (int i = 0; i < 6; i++)
			{
				sgGridSet6Point(grid, Nei, 1);
				if (B >= 3)
				{
					sgGridSet6Point(grid, Nei2, 1);
					if (B >= 4)
					{
						sgGridSet6Point(grid, Nei3, 1);
					}
				}
			}
		}
		break;
		case EVENT_LBUTTONUP:
		{
			DrawLFlag = false;
		}
		break;
		case EVENT_RBUTTONDOWN:
		{
			DrawRFlag = true;
			tx = x - shi.x;
			ty = y - shi.y;
			p = sgCeil((sqrt(3) / 3 * tx - 1 / 3 * ty) / (hexType.r + hexType.w));
			s = sgCeil(ty * 2 / 3 / (hexType.r + hexType.w));

			NeighborhoodLocal(MODE, p, s, Nei);
			NeighborhoodLocal2(MODE, p, s, Nei2);
			NeighborhoodLocal3(MODE, p, s, Nei3);

			if (p >= 0 && p < grid.sgRow && s >= 0 && s < grid.sgCol)
				grid.sgMat[p][s] = 0;
			if (B >= 2)for (int i = 0; i < 6; i++)
			{
				sgGridSet6Point(grid, Nei, 0);
				if (B >= 3)
				{
					sgGridSet6Point(grid, Nei2, 0);
					if (B >= 4)
					{
						sgGridSet6Point(grid, Nei3, 0);
					}
				}
			}
		}
		break;
		case EVENT_RBUTTONUP:
		{
			DrawRFlag = false;
		}
		break;
		case EVENT_MBUTTONDOWN:
		{
			DrawMFlag = true;
			shi.tx = -shi.x + x;
			shi.ty = -shi.y + y;
			//cout << shi.tx << " ||| " << shi.ty << endl;
		}
		break;
		case EVENT_MBUTTONUP:
		{
			DrawMFlag = false;
		}
		break;
		case EVENT_MOUSEWHEEL:
		{
			int value = getMouseWheelDelta(flags);

			if (value > 0)
			{
				hexType.r = hexType.r*(1 + STEP.step);
				//DEFAULT_R = DEFAULT_R + STEP.step;
				if (hexType.r <= 4.8)hexType.w = hexType.r * 0.4; else hexType.w = 3;
			}
			else if (value < 0)
			{
				//DEFAULT_R = DEFAULT_R - STEP.step;
				//if (DEFAULT_R <= 0)DEFAULT_R = 0.2;
				//if (DEFAULT_R <= 4.8)DEFAULT_LINEWIDTH = DEFAULT_R * 0.375;
				hexType.r = hexType.r*(1 - STEP.step);
				if (hexType.r <= 4.8)hexType.w = hexType.r * 0.4; else hexType.w = 3;
				if (hexType.w <= 0.5)hexType.w = 0;
				imshow(FormGrid, mat);
			}
			//cout << hexType.r << " " << hexType.w << endl;
		}
		break;
	}
}

gh::grid a(10,-1);

int main()
{
	int len = 200;// 100;
	int time = 0, T = 200, i, j;
	char key = '0';

	int sN[300] = { 0 };
	int s_c[300] = { 0 };
	double tmp = 0;
	int p = 0;
	double cN = len * len;//14400;
	//cout << cN << endl;

	//控制台程序窗口名
	char FormCon[260];
	//sgGetExePath(FormCon);

	GridMode Mode(sg::sgMode0, sg::sgMode0);
	Grid G(len), Gnext(len);
	//snow:234_34 or 34_34
	//45_56
	//5678_67
	int hExist[] = { 5,6,7,8 };
	int hDeath[] = { 6,7 };
	//int hExist[] = { 2,3,4 };
	//int hDeath[] = { 3,4 };
	Rule hE(hExist, sizeof(hExist) / sizeof(hExist[0]));
	Rule hD(hDeath, sizeof(hDeath) / sizeof(hDeath[0]));
	Rules hR(hE, hD);

	Mat Img(sgMaxRow(G), sgMaxCol(G), CV_8UC3, Scalar(128, 128, 128)), tempImg;
	Mat bar(100, 300, CV_8UC3, Scalar(0, 0, 0));
	GridImage GM(G, Img);

	imshow(FormGrid, Img);
	//鼠标事件
	setMouseCallback(FormGrid, on_MouseHandle, (void*) &GM);

	//窗口位置初始化
	//sgInitializationWindows(FormGrid, FormBar, FormCon);
	cout << "Initizal ..." << endl;

	//进入绘图
	while (1)
	{
		GridShow(Img, G, hexType, shi);
		Img.copyTo(tempImg);
		if (FindWindowA(NULL, FormGrid) == NULL)
		{
			//imshow(FormGrid, tempImg);
			//setMouseCallback(FormGrid, on_MouseHandle, (void*) &GM);
			return 0;
		}
		else
			imshow(FormGrid, tempImg);


		//检测空格，进入步进循环
		key = waitKey(10);
		if (key == 32)
		{
			key = '0';
			cout << "Loop Running... " << endl;
			while (1)
			{
				if (key == 32)
				{
					key = '0';
					cout << "Loop Pause... " << endl;
					break;
				}
				//NextStep(Mode, G, Gnext, h);
				//NextStep2(Mode, G, Gnext, hR);
				NextStep3(Mode, G, Gnext, hR);
				switch (MODER)
				{
					case 1:NextStep(Mode, G, Gnext, hR); break;
					case 2:NextStep2(Mode, G, Gnext, hR); break;
					case 3:NextStep3(Mode, G, Gnext, hR); break;
					default:NextStep(Mode, G, Gnext, hR); break;
				}
				reG(G, Gnext);

				GridShow(Img, G, hexType, shi);
				Img.copyTo(tempImg);
				if (FindWindowA(NULL, FormGrid) == NULL)
				{
					//imshow(FormGrid, tempImg);
					//setMouseCallback(FormGrid, on_MouseHandle, (void*) &GM);
					return 0;
				}
				else
					imshow(FormGrid, tempImg);
				key = waitKey(T);
				
			}
		}
	}
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
