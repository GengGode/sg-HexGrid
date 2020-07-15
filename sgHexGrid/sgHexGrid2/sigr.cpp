#include "sigr.h"

gh::sgGridMode
xj(gh::sgX, gh::sgJ), 
xp(gh::sgX, gh::sgP), 
yj(gh::sgY, gh::sgJ), 
yp(gh::sgY, gh::sgP);

static double cosTheta[6] = { 0.8660,0,-0.8660,-0.8660,0,0.8660 };
static double sinTheta[6] = { 0.5,1,0.5,-0.5,-1,-0.5 };
static double xjCos[] = { 0.866025, 0., -0.866025, -0.866025, 0., 0.866025 };
static double yjSin[] = { 0.5, 1., 0.5, -0.5, -1., -0.5 };
static double xpCos[] = { 1., 0.5, -0.5, -1., -0.5, 0.5 };
static double ypSin[] = { 0.,0.866025,0.866025,0.,-0.866025,-0.866025 };

gh::rule::rule():rule(2,6) {}

gh::rule::rule(int sgNeighborhood_):rule(2,sgNeighborhood_) {}

gh::rule::rule(int sgNeighborhood_, int sgState_): sgNeighborhood(sgNeighborhood_), sgState(sgState_)
{
	if (sgState_ < 2 )throw sgException("The number of States must be greater than or equal to two !");
	if (sgState_ > 256)throw sgException("The number of States cannot be more than 256 !");
	if (sgNeighborhood_ < 1)throw sgException("The number of Neighborhood must be greater than or equal to 1 !");
	if (sgNeighborhood_ > 256)throw sgException("The number of Neighborhood cannot be more than 256 !");

	sgStateTransitionTable = new bool**[sgState_];
	for (int i = 0; i < sgState_; i++)
	{
		sgStateTransitionTable[i] = new bool*[sgState_];
		for (int j = 0; j < sgState_; j++)
		{
			sgStateTransitionTable[i][j] = new bool[sgNeighborhood_];
		}
	}

}

gh::rule::~rule()
{
	for (int i = 0; i < sgState; i++)
	{
		for (int j = 0; j < sgState; j++)
		{
			delete[] sgStateTransitionTable[i][j];
			sgStateTransitionTable[i][j] = nullptr;
		}
		delete[] sgStateTransitionTable[i];
		sgStateTransitionTable[i] = nullptr;
	}
	delete sgStateTransitionTable;
	sgStateTransitionTable = nullptr;
}

void gh::rule::set(int sState_, int eState_, int tNeighbor_)
{
	if (sState_ >= 2 || eState_ <= sgState)throw sgException("Start state and target state need to be between 2 and number of states !");
	if (tNeighbor_ >= 1 || tNeighbor_ <= 256)throw sgException("Setting the starting point and setting the end point should be within the neighborhood !");
	sgStateTransitionTable[sState_][eState_][tNeighbor_] = true;
}

void gh::rule::set(int sState_, int eState_, int sNeighbor_, int eNeighbor_)
{
	if (sState_ >= 2 || eState_ <= sgState)throw sgException("Start state and target state need to be between 2 and number of states !");
	if (sNeighbor_ >= 1 || eNeighbor_<=256)throw sgException("The setting target needs to be within the neighborhood !");
	for (int i = sNeighbor_; i <= eNeighbor_; i++)
		sgStateTransitionTable[sState_][eState_][i] = true;

}

gh::grid::grid() :grid(4) {}

gh::grid::grid(int sgLen_):grid(sgLen_, sgLen_) {}

gh::grid::grid(int sgRow_, int sgCol_): sgRow(sgRow_), sgCol(sgCol_)
{
	if (sgRow_ <= 0 || sgCol_ <= 0)throw sgException("Size cannot be less than or equal to zero !");
	sgMat256V = new unsigned char*[sgRow_];
	for (int i = 0; i < sgRow_; i++)
	{
		sgMat256V[i] = new unsigned char[sgCol_]();
	}
}

gh::grid::grid(grid & grid_)
{
	grid tmp(grid_.row(),grid_.col());
	for (int i = 0; i < sgRow; i++)
	{
		for (int j = 0; j < sgCol; j++)
		{
			tmp.SetMat(i, j,sgMat256V[i][j]);
		}
	}

}

gh::grid gh::grid::operator=(const grid & grid_)
{
	grid tmp(grid_.sgRow, grid_.sgCol);
	for (int i = 0; i < sgRow; i++)
	{
		for (int j = 0; j < sgCol; j++)
		{
			tmp.SetMat(i, j, sgMat256V[i][j]);
		}
	}
	return tmp;
}

int gh::grid::row()
{
	return sgRow;
}

int gh::grid::col()
{
	return sgCol;
}

int gh::grid::mat(int i, int j)
{
	return sgMat256V[i][j];
}

void gh::grid::One()
{
	for (int i = 0; i < sgRow; i++)
		for (int j = 0; j < sgCol; j++)
			sgMat256V[i][j] = 1;
}

void gh::grid::Zero()
{
	for (int i = 0; i < sgRow; i++)
		for (int j = 0; j < sgCol; j++)
			sgMat256V[i][j] = 0;
}

/*
* Ëæ»úÅÅ²¼
* 
*/
void gh::grid::Rand()
{
	for (int i = 0; i < sgRow; i++)
		for (int j = 0; j < sgCol; j++)
			if (rand() % 100 <= 20)
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

void gh::grid::SetRow(int sgRow_)
{
	unsigned char **tmp = new unsigned char*[sgRow_];
	for (int i = 0; i < sgRow_; i++)
	{
		tmp[i] = new unsigned char[sgCol]();
	}

	for (int i = 0; i < min(sgRow, sgRow_); i++)
		for (int j = 0; j < sgCol; j++)
			tmp[i][j] = sgMat256V[i][j];
	for (int i = 0; i < sgRow; i++)
	{
		delete[] sgMat256V[i];
		sgMat256V[i] = nullptr;
	}
	delete sgMat256V;
	sgMat256V = tmp;
}

void gh::grid::SetCol(int sgCol_)
{
	unsigned char **tmp = new unsigned char*[sgRow];
	for (int i = 0; i < sgRow; i++)
	{
		tmp[i] = new unsigned char[sgCol_]();
	}
	for (int i = 0; i < sgRow; i++)
		for (int j = 0; j < min(sgCol,sgCol_); j++)
			tmp[i][j] = sgMat256V[i][j];
	for (int i = 0; i < sgRow; i++)
	{
		delete[] sgMat256V[i];
		sgMat256V[i] = nullptr;
	}
	delete sgMat256V;
	sgMat256V = tmp;
}

void gh::grid::SetMat(int i, int j, int n)
{
	sgMat256V[i][j] = n;
}

unsigned char * gh::grid::operator[](int i)
{
	return  sgMat256V[i];
}

gh::grid::~grid()
{
	for (int i = 0; i < sgRow; i++)
	{
		delete[] sgMat256V[i];
		sgMat256V[i] = nullptr;
	}
	delete sgMat256V;
	sgMat256V = nullptr;
}

gh::pic::pic():pic(1280,720) {}

gh::pic::pic(int sgLen_):pic(sgLen_,sgLen_) {}

gh::pic::pic(int sgRow_, int sgCol_):sgRow(sgRow_), sgCol(sgCol_)
{
	if (sgRow_ <= 0 || sgCol_ <= 0)throw sgException("Size cannot be less than or equal to zero !");
	sgImg = Mat(sgRow_, sgCol_,CV_8UC3);
}

void gh::pic::set(Scalar c)
{
	sgImg = c;
}

void gh::pic::set(int sgRow_, int sgCol_)
{
	if (sgRow_ <= 0 || sgCol_ <= 0)throw sgException("Size cannot be less than or equal to zero !");
	sgImg = Mat(sgRow_, sgCol_, CV_8UC3);
}

Mat gh::pic::img()
{
	return sgImg;
}

gh::sigr::sigr()
{
}

gh::sigr::sigr(int pRow_, int pCol_, int gRow_, int gCol_)
{
	p = pic(pRow_, pCol_);
	g = grid(gRow_, gCol_);
}

void gh::sigr::bgc()
{
	p.set(c.bgc());
}

void gh::sigr::draw()
{
	//getRect();
	//sgRenderRect ActivationRect(0,0,127,127);
	/******/
	bgc();
	static double cosTheta[6] = { 0.866025, 0., -0.866025, -0.866025, 0., 0.866025 };
	static double sinTheta[6] = { 0.5,1,0.5,-0.5,-1,-0.5 };
	int tmpx = 0, tmpy = 0;
	double dx, dy;
	int m, n;
	double root3 = 1.7321*c.R();
	double In[2][6] = { 0 };
	Point point[1][6];
	int np[] = { 6 };
	const Point* pp[1] = { point[0] };
	Scalar black(0, 0, 0);
	double t = (double) cv::getTickCount();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m = i;
			n = j;
			n % 2 ? dx = (m - 0.25) * root3 : dx = (m + 0.25)* root3;
			dy = c.R() * n * 3 / 2;
			for (int k = 0; k < 6; k++)
			{
				In[0][k] = dx + (c.R()+2) * cosTheta[k];
				In[1][k] = dy + (c.R()+2) * sinTheta[k];
				point[0][k].x = cvRound(In[0][k] + dx);
				point[0][k].y = cvRound(In[1][k] + dy);
			}
			//polylines(p.sgImg, pp,np,1,1,Scalar(255,255,0),4,LINE_AA);
			fillConvexPoly(p.sgImg,*pp, *np,black , LINE_AA);// , LINE_AA);

		}
		for (int j = 0; j < 10; j++)
		{
			m = i;
			n = j;
			n % 2 ? dx = (m - 0.25) * root3 : dx = (m + 0.25)* root3;
			dy = c.R()* n * 3 / 2;
			for (int k = 0; k < 6; k++)
			{
				In[0][k] = dx + (c.R()-2) * cosTheta[k];
				In[1][k] = dy + (c.R() -2)* sinTheta[k];
				point[0][k].x = cvRound(In[0][k] + dx);
				point[0][k].y = cvRound(In[1][k] + dy);
			}
			//polylines(p.sgImg, pp, np, 1, 1, Scalar(255, 255, 0), 4, LINE_AA);
			fillConvexPoly(p.sgImg, *pp, *np, Scalar(255, 255, 255), LINE_AA);// , LINE_AA);

		}
	}
	t = ((double) cv::getTickCount() - t) / cv::getTickFrequency();
	cout << "cost time A: " << t << endl;
	t = (double) cv::getTickCount();
	for (int i = 10; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m = i;
			n = j;
			n % 2 ? dx = (m - 0.25) * root3 : dx = (m + 0.25)* root3;
			dy = c.R() * n * 3 / 2;
			for (int k = 0; k < 6; k++)
			{
				In[0][k] = dx + c.R() * cosTheta[k];
				In[1][k] = dy + c.R() * sinTheta[k];
				point[0][k].x = cvRound(In[0][k] + dx);
				point[0][k].y = cvRound(In[1][k] + dy);
			}
			//fillPoly(p.sgImg, pp, np, 1, black,LINE_AA);
			polylines(p.sgImg, pp, np, 1, 1, Scalar(255, 255, 0), 4, LINE_AA);

		}
		//for (int j = 0; j < 10; j++)
		//{
		//	m = i;
		//	n = j;
		//	n % 2 ? dx = (m - 0.25) * (root3 + 1) : dx = (m + 0.25)* (root3 + 1);
		//	dy = (c.R() + 1) * n * 3 / 2;
		//	for (int k = 0; k < 6; k++)
		//	{
		//		In[0][k] = dx + c.R() * cosTheta[k];
		//		In[1][k] = dy + c.R() * sinTheta[k];
		//		point[0][k].x = cvRound(In[0][k] + dx);
		//		point[0][k].y = cvRound(In[1][k] + dy);
		//	}
		//	polylines(p.sgImg, pp, np, 1, 1, Scalar(255, 255, 0), 4, LINE_AA);

		//	//fillPoly(p.sgImg, pp, np, 1, Scalar(255, 255, 255), LINE_AA);
		//}
	}
	t = ((double) cv::getTickCount() - t) / cv::getTickFrequency();
	cout << "cost time B: " << t << endl;
	//imshow(sgWindowName, p.img());
	//waitKey(2000);
}

void gh::sigr::show()
{
	if (sgMainForm == nullptr)
	{
		namedWindow(sgWindowName);//p.img());
	}
	else if (sgMainForm != FindWindowA(NULL, sgWindowName))
	{
		sgMainForm = FindWindowA(NULL, sgWindowName);
	}
	imshow(sgWindowName, p.img());
}

gh::sgGridMode::sgGridMode()
{
}

gh::sgGridMode::sgGridMode(sgMode u, sgMode v)
{
	sgU = u;
	sgV = v;
}

gh::conf::conf()
{
}

Scalar gh::conf::bgc()
{
	return sgBGC;
}

double gh::conf::r()
{
	return sgHexR;
}

double gh::conf::w()
{
	return sgSpaceW;
}

double gh::conf::R()
{
	return sgHexR + sgSpaceW;
}

gh::sgStateColor::sgStateColor()
{
	sgN = 2;
	sgColor = new Scalar[2];
	sgColor[0] = sgStartStateColor;
	sgColor[1] = sgEndStateColor;
}

gh::sgStateColor::sgStateColor(int n)
{
	sgN = n;
	sgColor = new Scalar[n];
	sgColor[0] = sgStartStateColor;
	sgColor[n - 1] = sgEndStateColor;
	for (int i = 1; i < n-1; i++)
	{
		for (int k = 0; k < 3; k++)
			sgColor[i].val[k] = sgStartStateColor.val[k] + (sgEndStateColor.val[k] - sgStartStateColor.val[k])*i / (n - 1);
	}
}

gh::sgStateColor::~sgStateColor()
{
	delete sgColor;
	sgColor = nullptr;
}

Scalar gh::sgStateColor::get(int state)
{
	return sgColor[state];
}

gh::sgCoor::sgCoor()
{
	sgX = 0;
	sgY = 0;
}

gh::sgCoor::sgCoor(double x, double y)
{
	sgX = x;
	sgY = y;
}

double gh::sgCoor::x()
{
	return sgX;
}

double gh::sgCoor::y()
{
	return sgY;
}

gh::sgRenderRect::sgRenderRect() :sgRenderRect(0,0,1,1) {}

gh::sgRenderRect::sgRenderRect(int tx, int ty, int bx, int by)
{
	sgTopLeftX = tx;
	sgTopLeftY = ty;
	sgBotRighX = bx;
	sgBotRighY = by;
}

gh::sgRect::sgRect() :sgRect(0, 0, 1, 1) {}

gh::sgRect::sgRect(int tx, int ty, int bx, int by)
{
	sgLef = tx;
	sgTop = ty;
	sgRig = bx;
	sgBot = by;
}

gh::sgBlocks::sgBlocks()
{
	sgGrid = new sgBlock*[1];
	sgGrid[0] = new sgBlock[1];
	sgGrid[0][0];

}

gh::sgBlock::sgBlock()
{
}

unsigned char * gh::sgBlock::operator[](int i)
{
	return sgMat[i];
}

gh::sgUV::sgUV():sgUV(0,0) {}

gh::sgUV::sgUV(int u, int v)
{
	sgU = u;
	sgV = v;
}
