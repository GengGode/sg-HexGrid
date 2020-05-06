#include"sixgrid.h"

using namespace sg;


Cube cubeNei[] = {
		Cube(+1, -1, 0), Cube(+1, 0, -1), Cube(0, +1, -1),
			Cube(-1, +1, 0), Cube(-1, 0, +1), Cube(0, -1, +1),
};
int B = 1;
int q = 1;
int r = 1;
int p = 1;
int s = 1;
bool DrawLFlag = false;
bool DrawRFlag = false;
char FormGrid[] = "Form Grid";
GridMode MODE;

void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
	GridImage& gm = *(sg::GridImage*) param;
	Grid grid = gm.grid;
	Mat mat = gm.mat;
	Offset ohex(q,r);
	Cube ctmp;
	Offset otmp;

	int Nei[2][6] = { 0 };
	int m=0, n=0;
	int tm = 0, tn = 0;

	switch (event)
	{
	case EVENT_MOUSEMOVE:
	{
		m = cvCeil((sqrt(3) / 3 * x - 1 / 3 * y) / (DEFAULT_R + DEFAULT_LINEWIDTH));
		n = cvCeil(y * 2 / 3 / (DEFAULT_R + DEFAULT_LINEWIDTH));
		q = m;
		r = n;
		p = m;
		s = n;
		//ohex.col = q;
		//ohex.row = r;
		//Cube chex(ohex);
		NeighborhoodLocal(MODE, m, n, Nei);
		if (DrawLFlag)
		{
			if (q - 1 >= 0 && q - 1 < grid.sgRow && r >= 0 && r < grid.sgCol)
				grid.sgMat[q - 1][r] = 1;
			if (B==2)
				for (int i = 0; i < 6; i++)
				{
					//ctmp = chex + cubeNei[i];
					////ctmp.sgCout();
					//otmp = sgOffsettoCube(ctmp);
					//tm = otmp.col - 1;
					//tn = otmp.row;
					tm = Nei[0][i];
					tn = Nei[1][i];
					if (tm - 1 >= 0 && tm - 1 < grid.sgRow && tn >= 0 && tn < grid.sgCol)
						grid.sgMat[tm-1][tn] = 1;
				}
		}
			

		if (DrawRFlag)
		{
			if (p - 1 >= 0 && p - 1 < grid.sgRow && s >= 0 && s < grid.sgCol)
				grid.sgMat[p - 1][s] = 0;
			if (B == 2)
				for (int i = 0; i < 6; i++)
				{
					//ctmp = chex + cubeNei[i];
					////ctmp.sgCout();
					//otmp = sgOffsettoCube(ctmp);
					//tm = otmp.col - 1;
					//tn = otmp.row;
					tm = Nei[0][i];
					tn = Nei[1][i];
					if (tm - 1 >= 0 && tm - 1 < grid.sgRow && tn >= 0 && tn < grid.sgCol)
						grid.sgMat[tm - 1][tn] = 0;
				}
		}
			
		if (B == 2)
			for (int i = 0; i < 6; i++)
			{
				//ctmp = chex + cubeNei[i];
				//ctmp.sgCout();
				//otmp = sgOffsettoCube(ctmp);
				//m = otmp.col - 1;
				//n = otmp.row;
				m = Nei[0][i];
				n = Nei[1][i];
				if (m - 1 >= 0 && m - 1 < grid.sgRow && n >= 0 && n < grid.sgCol)
					sg::GridImg(mat, m - 1, n, Scalar(255, 255, 0));
			}
		if (m - 1 >= 0 && m - 1 < grid.sgRow && n >= 0 && n < grid.sgCol)
		{
			sg::GridImg(mat, m - 1, n, Scalar(255, 255, 0));
			imshow(FormGrid, mat);
		}
	}
	break;
	case EVENT_LBUTTONDOWN:
	{
		DrawLFlag = true;
		q = cvCeil((sqrt(3) / 3 * x - 1 / 3 * y) / (DEFAULT_R + DEFAULT_LINEWIDTH));
		r = cvCeil(y * 2 / 3 / (DEFAULT_R + DEFAULT_LINEWIDTH));
		//ohex.col = q;
		//ohex.row = r;
		//Cube chex(ohex);
		NeighborhoodLocal(MODE,q, r, Nei);
		if (q - 1 >= 0 && q - 1 < grid.sgRow && r >= 0 && r < grid.sgCol)
			grid.sgMat[q - 1][r] = 1;
		if (B == 2)
			for (int i = 0; i < 6; i++)
			{
				//ctmp = chex + cubeNei[i];
				////ctmp.sgCout();
				//otmp = sgOffsettoCube(ctmp);
				//tm = otmp.col - 1;
				//tn = otmp.row;
				tm = Nei[0][i];
				tn = Nei[1][i];
				if (tm - 1 >= 0 && tm - 1 < grid.sgRow && tn >= 0 && tn < grid.sgCol)
					grid.sgMat[tm - 1][tn] = 1;
			}
		
	}
	break;
	case EVENT_LBUTTONUP:
	{
		DrawLFlag = false;
		q = cvCeil((sqrt(3) / 3 * x - 1 / 3 * y) / (DEFAULT_R + DEFAULT_LINEWIDTH));
		r = cvCeil(y * 2 / 3 / (DEFAULT_R + DEFAULT_LINEWIDTH));
	}
	break;
	case EVENT_RBUTTONDOWN:
	{
		DrawRFlag = true;

		p = cvCeil((sqrt(3) / 3 * x - 1 / 3 * y) / (DEFAULT_R + DEFAULT_LINEWIDTH));
		s = cvCeil(y * 2 / 3 / (DEFAULT_R + DEFAULT_LINEWIDTH));
		//ohex.col = p;
		//ohex.row = s;
		//Cube chex(ohex);
		NeighborhoodLocal(MODE,p, s, Nei);
		if (p - 1 >= 0 && p - 1 < grid.sgRow && s >= 0 && s < grid.sgCol)
			grid.sgMat[p - 1][s] = 0;
		if (B == 2)
			for (int i = 0; i < 6; i++)
			{
				//ctmp = chex + cubeNei[i];
				////ctmp.sgCout();
				//otmp = sgOffsettoCube(ctmp);
				//tm = otmp.col - 1;
				//tn = otmp.row;
				tm = Nei[0][i];
				tn = Nei[1][i];
				if (tm - 1 >= 0 && tm - 1 < grid.sgRow && tn >= 0 && tn < grid.sgCol)
					grid.sgMat[tm - 1][tn] = 0;
			}
	}
	break;
	case EVENT_RBUTTONUP:
	{
		DrawRFlag = false;
		p = cvCeil((sqrt(3) / 3 * x - 1 / 3 * y) / (DEFAULT_R + DEFAULT_LINEWIDTH));
		s = cvCeil(y * 2 / 3 / (DEFAULT_R + DEFAULT_LINEWIDTH));
	}
	break;
	}
}


int main()
{
	int len = 100;
	int time = 0, T = 240, i, j;
	char key = '0';

	int sN[300] = { 0 };
	int s_c[300] = { 0 };
	double tmp = 0;
	int p = 0;
	int cN = 14400;

	//显示条窗口名
	char FormBar[] = "Form Bar";
	//控制台程序窗口名
	char FormCon[260];
	sgGetExePath(FormCon);

	GridMode Mode(sgMode0,sgMode0);
	Grid G(len), Gnext(len);
	int hExist[] = { 3 };
	int hDeath[] = { 0,1,2,4,5,6};
	Rule hE(hExist);
	Rule hD(hDeath);
	Rules hR(hE,hD);

	G.sgMat[40][30] = 1;

	Mat Img(sgMaxRow(G), sgMaxCol(G), CV_8UC3, Scalar(128, 128, 128)), tempImg;
	Mat bar(100, 300, CV_8UC3, Scalar(0, 0, 0));
	GridImage GM(G, Img);

	imshow(FormGrid, Img);
	//鼠标事件
	setMouseCallback(FormGrid, on_MouseHandle, (void*)&GM);

	

	//存活率显示条绘制
	for (i = 0; i < 300; i++)
	{
		s_c[i] = cvCeil(sN[i] / 144);
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

	Offset ohex(q, r, Mode);
	ohex.sgCout();
	Cube chex(ohex);
	chex.sgCout();
	//Offset(chex).sgCout();
	Offset ohex2 = sgOffsettoCube(chex);
	ohex2.sgCout();
	//进入绘图
	while(1)
	{
		GridShow(Img, G);
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
			s_c[i] = cvCeil(sN[i] / 144);
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
				NextStep(Mode, G, Gnext, hR);
				reG(G, Gnext);

				GridShow(Img, G);
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
					s_c[i] = cvCeil(sN[i] / 144);
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
				hE.lis = sgRuleInputLis(InE);
				hE.count = sgRuleInputCount(InE);
				hD.lis = sgRuleInputLis(InD);
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
