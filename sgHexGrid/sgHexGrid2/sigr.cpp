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

gh::rule::rule() :rule(2, 6) {}

gh::rule::rule(int sgNeighborhood_) : rule(2, sgNeighborhood_) {}

gh::rule::rule(int sgNeighborhood_, int sgState_) : sgNeighborhood(sgNeighborhood_), sgState(sgState_)
{
	if (sgState_ < 2)throw sgException("The number of States must be greater than or equal to two !");
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
	if (sNeighbor_ >= 1 || eNeighbor_ <= 256)throw sgException("The setting target needs to be within the neighborhood !");
	for (int i = sNeighbor_; i <= eNeighbor_; i++)
		sgStateTransitionTable[sState_][eState_][i] = true;

}

gh::grid::grid() :grid(4) {}

gh::grid::grid(int sgLen_) : grid(sgLen_, sgLen_) {}

gh::grid::grid(int sgRow_, int sgCol_) : sgRow(sgRow_), sgCol(sgCol_)
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
	grid tmp(grid_.row(), grid_.col());
	for (int i = 0; i < sgRow; i++)
	{
		for (int j = 0; j < sgCol; j++)
		{
			tmp.SetMat(i, j, sgMat256V[i][j]);
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
		for (int j = 0; j < min(sgCol, sgCol_); j++)
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

gh::pic::pic() :pic(1280, 720) {}

gh::pic::pic(int sgLen_) : pic(sgLen_, sgLen_) {}

gh::pic::pic(int sgRow_, int sgCol_) : sgRow(sgRow_), sgCol(sgCol_)
{
	if (sgRow_ <= 0 || sgCol_ <= 0)throw sgException("Size cannot be less than or equal to zero !");
	sgImg = Mat(sgRow_, sgCol_, CV_8UC3);
}

void gh::pic::set(Mat m)
{
	sgImg = m;
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

int gh::pic::row()
{
	return sgRow;
}

int gh::pic::col()
{
	return sgCol;
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
	c.setSecCon(pCol_ / 2, pRow_ / 2);
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
	SetCsetSecCon();

	static double cosTheta[6] = { 0.866025, 0., -0.866025, -0.866025, 0., 0.866025 };
	static double sinTheta[6] = { 0.5,1,0.5,-0.5,-1,-0.5 };

	double dx, dy;

	Point point[1][6];
	int np[] = { 6 };
	const Point* pp[1] = { point[0] };

	double tx = c.secConX(), ty = c.secConY();
	double tax = c.tarConX(), tay = c.tarConY();
	double t = (double) cv::getTickCount();

	Scalar C;

	for (int i = -c.rl.sgM; i <= c.rl.sgM; i++)
	{
		for (int j = -c.rl.sgN; j <= c.rl.sgN; j++)
		{
			j % 2 ? dx = (i - 0.5) * c.root3R() : dx = i * c.root3R();
			dy = c.R() * j * 1.5;
			for (int k = 0; k < 6; k++)
			{
				point[0][k].x = cvRound(dx + tax + tx + c.r() * cosTheta[k]);
				point[0][k].y = cvRound(dy + tay + ty + c.r() * sinTheta[k]);
			}

			C = r.sgColor.get(b[64 + i][64 + j]);

			if (c.R() <= 0.5)
			{
				circle(p.sgImg, point[0][0], 2, C, -1);
			}
			else if (c.R() < 1.2)
			{
				polylines(p.sgImg, pp, np, 1, 1, C);
			}
			else
			{
				fillConvexPoly(p.sgImg, *pp, *np, C, LINE_AA);
			}
			fillhex(c.BlockAddress.sgM - c.rl.sgM, c.BlockAddress.sgN - c.rl.sgN, Scalar(200,200,255));
		}
	}

	circle(p.sgImg, Point(tx, ty), 3, Scalar(0, 0, 255));
	circle(p.sgImg, Point(c.mouseX(), c.mouseY()), 4, Scalar(0, 0, 255));
	//cout <<"Main "<< &p.sgImg << endl;

	t = ((double) cv::getTickCount() - t) / cv::getTickFrequency();
	statusBar(t);

	show();
}

void on_MouseMain(int event, int x, int y, int flags, void *parm)
{
	gh::sigr& s = *(gh::sigr*)parm;
	gh::pic& p = s.p;
	gh::conf& c = s.c;
	double tmpc = c.r();
	Mat tmpm = p.sgImg;
	Mat mat(100, 200, CV_8UC3, Scalar(0, 255, 0));
	imshow("123", tmpm);
	switch (event)
	{
		case EVENT_MOUSEMOVE:
		{
			c.setMouse(x, y);
			//p.sgImg = Scalar(0, 0, 123);
			circle(p.sgImg, Point(x, y), 6, Scalar(0, 0, 255));
			circle(mat, Point(x,y), 6, Scalar(0, 0, 255));
			//cout <<"     "<< &p.sgImg << endl;
			//cout << "Mouse : " << x << ":" << y << endl;
			imshow("123", mat);
		}
		break;
		case EVENT_MOUSEWHEEL:
		{
			int value = getMouseWheelDelta(flags);

			if (value > 0)
			{
				tmpc *= 1.1;
				c.setR(tmpc);
			}
			else if (value < 0)
			{
				tmpc *= 0.9;
				c.setR(tmpc);
			}

		}
		break;
	}
}
void gh::sigr::show()
{
	if (sgMainForm == nullptr)
	{
		namedWindow(sgWindowName, WINDOW_NORMAL);
		resizeWindow(sgWindowName, p.col(), p.row());
		sgMainForm = FindWindowA(NULL, sgWindowName);
		setMouseCallback(sgWindowName, on_MouseMain, (void*) this);// (void*) &c);
		reRect();
	}
	else if (sgMainForm != FindWindowA(NULL, sgWindowName))
	{
		namedWindow(sgWindowName, WINDOW_NORMAL);
		sgMainForm = FindWindowA(NULL, sgWindowName);
		setMouseCallback(sgWindowName, on_MouseMain, (void*) this);// (void*) &c);
		reRect();
	}
	if (!EqualRect(&sgFormSize, &getClientRect()))
	{
		rePic();
	}

	imshow(sgWindowName, p.img());
	
}

void gh::sigr::SetCsetSecCon()
{
	c.setSecCon(p.col() / 2, p.row() / 2);
}

void gh::sigr::fillhex(int i, int j, Scalar color)
{
	static double cosTheta[6] = { 0.866025, 0., -0.866025, -0.866025, 0., 0.866025 };
	static double sinTheta[6] = { 0.5,1,0.5,-0.5,-1,-0.5 };

	Point point[1][6];
	int np[] = { 6 };
	const Point* pp[1] = { point[0] };

	double tx = c.secConX(), ty = c.secConY();
	double tax = c.tarConX(), tay = c.tarConY();
	double dx, dy;

	j % 2 ? dx = (i - 0.5) * c.root3R() : dx = i * c.root3R();
	dy = c.R() * j * 1.5;
	for (int k = 0; k < 6; k++)
	{
		point[0][k].x = cvRound(dx + tax + tx + c.r() * cosTheta[k]);
		point[0][k].y = cvRound(dy + tay + ty + c.r() * sinTheta[k]);
	}

	if (c.R() <= 0.5)
	{
		circle(p.sgImg, point[0][0], 2, color, -1);
	}
	else if (c.R() < 1.2)
	{
		polylines(p.sgImg, pp, np, 1, 1, color);
	}
	else
	{
		fillConvexPoly(p.sgImg, *pp, *np, color, LINE_AA);
	}
}

char * gh::sigr::name()
{
	return sgWindowName;
}

HWND gh::sigr::handle()
{
	return sgMainForm;
}

RECT gh::sigr::rect()
{
	return sgFormSize;
}

void gh::sigr::statusBar(double time)
{
	Mat red(70,170,CV_8UC3,Scalar(255,255,0));
	Mat tmp = p.sgImg(Rect(5, p.row()-75, 170, 70));
	addWeighted(tmp, 0.1, red, 0.9, 0, tmp);
	putText(p.sgImg, "Fps:" + to_string(1.0 / time), Point(10, p.row() - 10), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255), 1, LINE_AA);

	putText(p.sgImg, "X:"+to_string(c.mouseX()), Point(10, p.row() - 25), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255), 1, LINE_AA);
	putText(p.sgImg, "Y:"+to_string(c.mouseY()), Point(55, p.row() - 25), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255), 1, LINE_AA);

	putText(p.sgImg, "M:" + to_string(c.rl.sgM), Point(10, p.row() - 40), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255), 1, LINE_AA);
	putText(p.sgImg, "N:" + to_string(c.rl.sgN), Point(55, p.row() - 40), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255), 1, LINE_AA);
	putText(p.sgImg, "i:" + to_string(c.BlockAddress.sgM), Point(10, p.row() - 55), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255), 1, LINE_AA);
	putText(p.sgImg, "j:" + to_string(c.BlockAddress.sgN), Point(55, p.row() - 55), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255), 1, LINE_AA);
}

void gh::sigr::evolution()
{

}

void gh::sigr::rePic()
{
	reRect();
	int newSizeX = sgFormSize.bottom - sgFormSize.top - 2;
	int newSizeY = sgFormSize.right - sgFormSize.left - 2;
	if (newSizeX < 120)newSizeX = 120;
	if (newSizeY < 180)newSizeY = 180;
	pic tmp(newSizeX, newSizeY);
	p = tmp;
}

void gh::sigr::reRect()
{
	GetClientRect(sgMainForm, &sgFormSize);
}

RECT gh::sigr::getClientRect()
{
	RECT out;
	GetClientRect(sgMainForm,&out);
	return out;
}

void gh::sigr::on_MouseHandle(int event, int x, int y, int flags, void *)
{
	switch (event)
	{
		case EVENT_MOUSEMOVE:
		{

		}
		break;
		case EVENT_LBUTTONDOWN:
		{
		}
		break;
		case EVENT_LBUTTONUP:
		{
		}
		break;
		case EVENT_RBUTTONDOWN:
		{
		}
		break;
		case EVENT_RBUTTONUP:
		{
		}
		break;
		case EVENT_MBUTTONDOWN:
		{
		}
		break;
		case EVENT_MBUTTONUP:
		{

		}
		break;
		case EVENT_MOUSEWHEEL:
		{
			int value = getMouseWheelDelta(flags);

			if (value > 0)
			{
				c.setR(c.r() + 1);
			}
			else if (value < 0)
			{
				c.setR(c.r() - 1);
			}

		}
		break;
	}
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
	setR(6);
}

gh::conf gh::conf::operator=(const conf & c_)
{
	conf c(c_);
	return c;
}

void gh::conf::setSecCon(int x, int y)
{
	sgSecConX = x;
	sgSecConY = y;
	reRenderLimit();
}

void gh::conf::reRenderLimit()
{
	//sgSecConX / sgRoot3R;//
	//(sgSecConX - (sgRoot3R / 2)) / sgRoot3R + 0.5
	//rl.sgM = cvCeil(sgSecConX / sgRoot3R) + 1;
	//rl.sgN = cvCeil(sgSecConY / R());
	rl.sgM = cvCeil((sqrt(3) / 3 * sgSecConX - 1 / 3 * sgSecConY) / R());
	rl.sgN = cvCeil(sgSecConY * 2 / 3 / R());
	if (rl.sgM < 0)rl.sgM = 0;
	if (rl.sgN < 0)rl.sgN = 0;
}

void gh::conf::reBlockAddress()
{
	BlockAddress.sgM = cvCeil((sqrt(3) / 3 * sgMouseX - 1 / 3 * sgMouseY) / R());
	BlockAddress.sgN = cvCeil(sgMouseY * 2 / 3 / R());
}

void gh::conf::reTheta()
{
	for (int k = 0; k < 6; k++)
	{
		ThetaX[k] = r() * cosTheta[k];
		ThetaY[k] = r() * sinTheta[k];
	}
}

void gh::conf::reRoot3R()
{
	sgRoot3R = 1.73205 * (sgHexR + sgSpaceW);
}

void gh::conf::setR(double r)
{
	sgHexR = r;
	if (r <= 0) r = -r;
	setW(sgHexR*0.2);
	reTheta();
	reRoot3R();
	reBlockAddress();
	reRenderLimit();
}

void gh::conf::setW(double w)
{
	sgSpaceW = w;
	if (sgSpaceW >= 3)sgSpaceW = 3;

}

void gh::conf::setMouse(int x, int y)
{
	sgMouseX = x;
	sgMouseY = y;
	reBlockAddress();
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

double gh::conf::root3R()
{
	return sgRoot3R;
}

int gh::conf::mouseX()
{
	return sgMouseX;
}

int gh::conf::mouseY()
{
	return sgMouseY;
}

int gh::conf::secConX()
{
	return sgSecConX;
}

int gh::conf::secConY()
{
	return sgSecConY;
}

double gh::conf::tarConX()
{
	return sgTarConX;
}

double gh::conf::tarConY()
{
	return sgTarConY;
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
	for (int i = 1; i < n - 1; i++)
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

gh::sgRenderRect::sgRenderRect() :sgRenderRect(0, 0, 1, 1) {}

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

void gh::sgBlock::Rand()
{
	for (int i = 0; i < 127; i++)
		for (int j = 0; j < 127; j++)
			if (rand() % 100 <= 20)
				sgMat[i][j] = 1;
			else
				sgMat[i][j] = 0;
}

void gh::sgBlock::Rand(double sgSurvivalRate_)
{
	for (int i = 0; i < 127; i++)
		for (int j = 0; j < 127; j++)
			if (rand() % 100 <= sgSurvivalRate_)
				sgMat[i][j] = 1;
			else
				sgMat[i][j] = 0;
}

gh::sgUV::sgUV() :sgUV(0, 0) {}

gh::sgUV::sgUV(int u, int v)
{
	sgU = u;
	sgV = v;
}

gh::sgRenderLimit::sgRenderLimit() :sgRenderLimit(0, 0) {}

gh::sgRenderLimit::sgRenderLimit(int m, int n) : sgM(m), sgN(n) {}