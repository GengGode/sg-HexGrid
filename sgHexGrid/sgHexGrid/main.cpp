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
	Offset ohex(q,r);
	Cube ctmp;
	Offset otmp;

	int Nei[2][6] = { 0 };
	int Nei2[2][6] = { 0 };
	int Nei3[2][6] = { 0 };
	int m=0, n=0;
	int tm = 0, tn = 0;
	int tm2 = 0, tn2 = 0;

	int tx = 0, ty = 0;

	//double MouseWheelStep = 0.2; 

	switch (event)
	{
	case EVENT_MOUSEMOVE:
	{
		
		tx =  x-shi.x;
		ty =  y-shi.y;
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
			sg::GridImg(mat, m, n,shi,hexType, Scalar(255, 255, 0));
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
		tx = x - shi.x;
		ty = y - shi.y;
		p = sgCeil((sqrt(3) / 3 * tx - 1 / 3 * ty) / (hexType.r + hexType.w));
		s = sgCeil(ty * 2 / 3 / (hexType.r + hexType.w));

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
		shi.tx = -shi.x+x;
		shi.ty = -shi.y+y;
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


int main()
{
	int len =200;// 100;
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
	int hDeath[] = { 6,7};
	//int hExist[] = { 2,3,4 };
	//int hDeath[] = { 3,4 };
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
	//SetDesktop(FormGrid);

	//鼠标事件
	setMouseCallback(FormGrid, on_MouseHandle, (void*)&GM);

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
				switch (MODER)
				{
					case 1:NextStep(Mode, G, Gnext, hR); break;
					case 2:NextStep2(Mode, G, Gnext, hR); break;
					case 3:NextStep3(Mode, G, Gnext, hR); break;
					default:NextStep(Mode, G, Gnext, hR); break;
				}
				reG(G, Gnext);

				GridShow(Img, G,hexType, shi);
				Img.copyTo(tempImg);
				if (FindWindowA(NULL, FormGrid) == NULL)
				{
					//imshow(FormGrid, tempImg);
					//setMouseCallback(FormGrid, on_MouseHandle, (void*) &GM);
					return 0;
				}
				else
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
					T += 50;
					if (T <= 0)T = 10;
					cout << "Change T up : " << T << "ms" << endl;
				}
				else if(key=='-')
				{
					key = '0';
					T -= 50;
					if (T <= 0)T = 10;
					cout << "Change T down : " << T << "ms" << endl;
				}
				else if (key == 'o')
				{
					key = '0';
					cout << "Stata: Exist: " << s_c[p] << " %" << " | Hex Show Size: " << hexType.r << " ，" << hexType.w << endl;
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
			cout << "Stata: Exist: "<< s_c[p] <<" %"<< " | Hex Show Size: "<< hexType.r<<" ，"<< hexType.w <<endl;
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
			cout << "Input Rules Select no more than 7 numbers from 0 to 10" << endl;
			//cout << "-----------------------------------------------------" << endl;
			//tmpkey=getchar();
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
				hE.clear();
				int* te = new int[hE.count];
				te = sgRuleInputLis(InE);
				//hD.lis = sgRuleInputLis(InD);
				hD.count = sgRuleInputCount(InD);
				hD.clear();
				int* td = new int[hD.count];
				td = sgRuleInputLis(InD);
				cout << "Exist: " <<hE.count<< endl;
				for (i = 0; i < hE.count; i++)
				{
					hE.lis[i] = te[i];
					cout << "	" << hE.lis[i];
				}
				cout << endl;
				cout << "Death: " << hD.count << endl;
				for (i = 0; i < hD.count; i++)
				{
					hD.lis[i] = td[i];
					cout << "	" << hD.lis[i];
				}
				cout << endl;
				hR.hExist = hE;
				hR.hDeath = hD;
			}
			//cout << "-------------------- Rules Over ---------------------" << endl;

		}
	}
	return 0;
}
