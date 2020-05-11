#include"sixgrid.h"

using namespace sg;


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
bool DrawMFlag = false;
char FormGrid[] = "Form Grid";
GridMode MODE;
HexType hexType(4.8, 1.8);
WheelStep STEP(0.2);

void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
	GridImage& gm = *(sg::GridImage*) param;
	Grid grid = gm.grid;
	Mat mat = gm.mat;
	Offset ohex(q,r);
	Cube ctmp;
	Offset otmp;

	int Nei[2][6] = { 0 };
	int Nei2[2][6] = { 0 };
	int Nei3[2][6] = { 0 };
	int m=0, n=0;
	int tm = 0, tn = 0;
	int tm2 = 0, tn2 = 0;

	//double MouseWheelStep = 0.2; 

	switch (event)
	{
	case EVENT_MOUSEMOVE:
	{
		m = sgCeil((sqrt(3) / 3 * x - 1 / 3 * y) / (hexType.r + hexType.w));
		n = sgCeil(y * 2 / 3 / (hexType.r + hexType.w));
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

		if (m >= 0 && m < grid.sgRow && n >= 0 && n < grid.sgCol)
		{
			sg::GridImg(mat, m, n,hexType, Scalar(255, 255, 0));
		}
		if (B >= 2)for (int i = 0; i < 6; i++)
		{
			m = Nei[0][i];
			n = Nei[1][i];
			if (m >= 0 && m < grid.sgRow && n >= 0 && n < grid.sgCol)
				sg::GridImg(mat, m, n, hexType, Scalar(255, 255, 0));
			if (B >= 3)
			{
				m = Nei2[0][i];
				n = Nei2[1][i];
				if (m >= 0 && m < grid.sgRow && n >= 0 && n < grid.sgCol)
					sg::GridImg(mat, m, n, hexType, Scalar(255, 255, 0));
				if (B >= 4)
				{
					m = Nei3[0][i];
					n = Nei3[1][i];
					if (m >= 0 && m < grid.sgRow && n >= 0 && n < grid.sgCol)
						sg::GridImg(mat, m, n, hexType, Scalar(255, 255, 0));
				}
			}
		}
		imshow(FormGrid, mat);
	}
	break;
	case EVENT_LBUTTONDOWN:
	{
		DrawLFlag = true;
		q = sgCeil((sqrt(3) / 3 * x - 1 / 3 * y) / (hexType.r + hexType.w));
		r = sgCeil(y * 2 / 3 / (hexType.r + hexType.w));

		NeighborhoodLocal(MODE,q, r, Nei);
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
		p = sgCeil((sqrt(3) / 3 * x - 1 / 3 * y) / (hexType.r + hexType.w));
		s = sgCeil(y * 2 / 3 / (hexType.r + hexType.w));

		NeighborhoodLocal(MODE,p, s, Nei);
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
			hexType.r = hexType.r + STEP.step;
			//DEFAULT_R = DEFAULT_R + STEP.step;
			if (hexType.r <= 4.8)hexType.w = hexType.r * 0.4; else hexType.w = 2;
		}
		else if (value < 0)
		{
			//DEFAULT_R = DEFAULT_R - STEP.step;
			//if (DEFAULT_R <= 0)DEFAULT_R = 0.2;
			//if (DEFAULT_R <= 4.8)DEFAULT_LINEWIDTH = DEFAULT_R * 0.375;
			hexType.r = hexType.r - STEP.step;
			if (hexType.r <= 4.8)hexType.w = hexType.r * 0.4; else hexType.w = 2;
			imshow(FormGrid, mat);
		}
		cout << hexType.r << " " << hexType.w << endl;
	}
	break;
	}
}


int main()
{
	int len =120;// 100;
	int time = 0, T = 200, i, j;
	char key = '0';

	int sN[300] = { 0 };
	int s_c[300] = { 0 };
	double tmp = 0;
	int p = 0;
	double cN =  len * len;//14400;
	//cout << cN << endl;
	//显示条窗口名
	char FormBar[] = "Form Bar";
	//控制台程序窗口名
	char FormCon[260];
	sgGetExePath(FormCon);

	GridMode Mode(sgMode0,sgMode0);
	Grid G(len), Gnext(len);
	//snow:234_34 or 34_34
	//45_56
	//5678_67
	int hExist[] = { 5,6,7,8};
	int hDeath[] = { 6,7};//{4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
	Rule hE(hExist, sizeof(hExist) / sizeof(hExist[0]));
	Rule hD(hDeath, sizeof(hDeath) / sizeof(hDeath[0]));
	//hE.out();
	//hD.out();
	Rules hR(hE,hD);

	//G.sgMat[40][30] = 1;

	Mat Img(sgMaxRow(G), sgMaxCol(G), CV_8UC3, Scalar(128, 128, 128)), tempImg;
	Mat bar(100, 300, CV_8UC3, Scalar(0, 0, 0));
	GridImage GM(G, Img);

	imshow(FormGrid, Img);
	//鼠标事件
	setMouseCallback(FormGrid, on_MouseHandle, (void*)&GM);

	
	//{
	//	Grid TestG(10);
	//	Mat TestImg(sgMaxRow(TestG), sgMaxCol(TestG), CV_8UC3, Scalar(128, 128, 128));
	//	GridImage TestGM(TestG, TestImg);

	//	double dx = 5, dy = 1;
	//	Point point[1][6];
	//	int np[] = { 6 };
	//	double grid[2][6];
	//	const Point* pp[1] = { point[0] };

	//	SixGrid(grid, 5, 5, dx,dy);

	//	for (int k = 0; k < 6; k++)
	//	{
	//		point[0][k] = Point(sgCeil(grid[0][k] + dx), sgCeil(grid[1][k] + dy));
	//		cout << " " << point[0][k] << " " << grid[0][k] << " " << grid[1][k] <<" " << dx << " " << dy<< endl;
	//		//point[0][k] = Point(cvCeil(grid[0][k] + dx), cvCeil(grid[1][k] + dy));
	//	}
	//	fillPoly(TestImg, pp, np, 1, Scalar(255,255,255), 1);
	//	SixGrid(grid, 6, 5, dx, dy);

	//	for (int k = 0; k < 6; k++)
	//	{
	//		//point[0][k] = Point(sgCeil(grid[0][k] + dx), sgCeil(grid[1][k] + dy));
	//		point[0][k] = Point(cvCeil(grid[0][k] + dx), cvCeil(grid[1][k] + dy));
	//	}
	//	fillPoly(TestImg, pp, np, 1, Scalar(255, 255, 255), 1);
	//	imshow("Test", TestImg);
	//}

	//存活率显示条绘制
	for (i = 0; i < 300; i++)
	{
		s_c[i] = sgCeil(sN[i] / cN * 100);
		for (j = 0; j < 100; j++)
		{
			if (s_c[i] == j)
			{
				bar.at<Vec3b>(j, i)[0] = 0;
				bar.at<Vec3b>(j, i)[1] = 255;
				bar.at<Vec3b>(j, i)[2] = 255;
			}
			else
			{
				bar.at<Vec3b>(j, i)[0] = 0;
				bar.at<Vec3b>(j, i)[1] = 0;
				bar.at<Vec3b>(j, i)[2] = 0;
			}
		}
	}
	imshow(FormBar, bar);

	//窗口位置初始化
	sgInitializationWindows(FormGrid, FormBar, FormCon);
	cout << "Initizal ..." <<endl;

	//进入绘图
	while(1)
	{
		GridShow(Img, G, hexType);
		Img.copyTo(tempImg);
		imshow(FormGrid, tempImg);
		
		p += 1;
		if (p >= 300)
		{
			p -= 1;
			for (i = 1; i < 300; i++)
				sN[i - 1] = sN[i];
		}
		sN[p] = sgSumGrid(G);
		
		for (i = 0; i < 300; i++)
		{
			s_c[i] = sgCeil(sN[i] / cN * 100);
			for (j = 0; j < 100; j++)
			{
				if (s_c[i] == j)
				{
					bar.at<Vec3b>(j, i)[0] = 0;
					bar.at<Vec3b>(j, i)[1] = 255;
					bar.at<Vec3b>(j, i)[2] = 255;
				}
				else
				{
					bar.at<Vec3b>(j, i)[0] = 0;
					bar.at<Vec3b>(j, i)[1] = 0;
					bar.at<Vec3b>(j, i)[2] = 0;
				}
			}
		}
		imshow(FormBar, bar);

		








		//检测空格，进入步进循环
		key = waitKey(10);
		if (key == 32)
		{
			key = '0';
			cout << "Loop Running... "<< endl;
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
				reG(G, Gnext);

				GridShow(Img, G,hexType);
				Img.copyTo(tempImg);
				imshow(FormGrid, tempImg);

				p += 1;
				if (p >= 300)
				{
					p -= 1;
					for (i = 1; i < 300; i++)
						sN[i - 1] = sN[i];
				}
				sN[p]=sgSumGrid(G);
				
				for (i = 0; i < 300; i++)
				{
					s_c[i] = sgCeil(sN[i] / cN * 100);
					for (j = 0; j < 100; j++)
					{
						if (s_c[i] == j)
						{
							bar.at<Vec3b>(j, i)[0] = 0;
							bar.at<Vec3b>(j, i)[1] = 255;
							bar.at<Vec3b>(j, i)[2] = 255;
						}
						else
						{
							bar.at<Vec3b>(j, i)[0] = 0;
							bar.at<Vec3b>(j, i)[1] = 0;
							bar.at<Vec3b>(j, i)[2] = 0;
						}
					}
				}
				//printf("%d %d %lf\n", sN[p],s_c[p],sN[p]/144.0);

				imshow(FormBar, bar);
				
				key = waitKey(T);
				if ( key== '+')
				{
					key = '0';
					T += 10;
					if (T <= 0)T = 10;
					cout << "Change T up : " << T << "ms" << endl;
				}
				else if(key=='-')
				{
					key = '0';
					T -= 10;
					if (T <= 0)T = 10;
					cout << "Change T down : " << T << "ms" << endl;
				}
				else if (key == 'o')
				{
					key = '0';
					cout << "Stata: Exist: " << s_c[p] << " %" << endl;
				}
				
			}
		}
		else if (key == 'c')
		{
			key = '0';
			for (i = 0; i < G.sgRow; i++)
				for (j = 0; j < G.sgCol; j++)
					G.sgMat[i][j] = 0;
			cout << "Stata: Clear " << endl;
		}
		else if (key == 'r')
		{
			key = '0';
			G.Rand();
			cout << "Stata: Random Create " << endl;
		}
		else if (key == 'o')
		{
			key = '0';
			cout << "Stata: Exist: "<< s_c[p] <<" %"<< endl;
		}
		if (key == '+')
		{
			key = '0';
			B += 1;
			if (B >= 10)B = 10;
			cout << "Change B up : " << B << "pix" << endl;
		}
		else if (key == '-')
		{
			key = '0';
			B -= 1;
			if (B <= 0)B = 1;
			cout << "Change B down : " << B << "pix" << endl;
		}
		else if (key == 'i')
		{
			key = '0';
			char InE[10],InD[10];
			char tmpkey;
			cout << "Rule Change->" << endl;
			cout << "Rule Hold Exist::" << endl;
			for (i = 0; i < hE.count; i++)
				cout << "	" << hE.lis[i];
			cout << endl;
			cout << "Rule Hold Death::" << endl;
			for (i = 0; i < hD.count; i++)
				cout << "	" << hD.lis[i];
			cout << endl;
			hR.hExist = hE;
			hR.hDeath = hD;
			//cout << "-----------------------------------------------------" << endl;
			cout << "Input Rules Select no more than 7 numbers from 0 to 6" << endl;
			//cout << "-----------------------------------------------------" << endl;
			tmpkey=getchar();
			cin >> InE;
			cin >> InD;
			//cout << "-------------------- Input Over ---------------------" << endl;
			cout << "Rule Hold Exist::" << InE<< endl;
			cout << "Rule Hold Death::" << InD << endl;
			//cout << "-----------------------------------------------------" << endl;
			cout << "Yes(Y) or No(N)" << endl;
			//cout << "-----------------------------------------------------" << endl;
			cin >> tmpkey;
			if (tmpkey == 'y' || tmpkey == 'Y')
			{
				//hE.lis = sgRuleInputLis(InE);
				hE.count = sgRuleInputCount(InE);
				//hD.lis = sgRuleInputLis(InD);
				hD.count = sgRuleInputCount(InD);
				cout << "Exist: " <<hE.count<< endl;
				for (i = 0; i < hE.count; i++)
					cout << "	" << hE.lis[i];
				cout << endl;
				cout << "Death: " << hD.count << endl;
				for (i = 0; i < hD.count; i++)
					cout << "	" << hD.lis[i];
				cout << endl;
				hR.hExist = hE;
				hR.hDeath = hD;
			}
			//cout << "-------------------- Rules Over ---------------------" << endl;

		}
	}
	return 0;
}
