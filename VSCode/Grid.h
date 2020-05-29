#pragma once
#include<iostream>
using namespace std;

double xCos[] = { 0.866025, 0., -0.866025, -0.866025, 0., 0.866025 };
double xSin[] = { 0.5, 1., 0.5, -0.5, -1., -0.5 };
double yCos[] = { 1., 0.5, -0.5, -1., -0.5, 0.5 };
double ySin[] = { 0.,0.866025,0.866025,0.,-0.866025,-0.866025 };

class Grid
{
	//后台
public:
	

};
class Hex
{
	//六边形
public:
	Hex();
	~Hex();
	Hex(double x_,double y_,double r_);
private:
	//Coor cen;//center
	//Coor cor;//corner
	/*/ 绘图坐标 /*/
	double x;
	double y;
	//Coor corner[];
	double corner[2][6];//顶点组


};

class Coor
{
	//坐标点
public:
	double x;
	double y;
	Coor();
};
enum Mode
{
	x = 0,
	y = 1,
	j = 0,
	p = 1
};

class GridMode
{
	//网格参数
public:
	Mode u;
	Mode v;

	GridMode();
private:

};

class Rule
{

};

class Block
{
	//单个区块
	/*
	unsigned char
	*/
public:
	Block();
	~Block();
	Block(double r_);
	Block(double u_,double v_,double r_);
private:
	//unsigned char i;
	//unsigned char j;
	Hex hex[255][255];
};
class Blocks//:Block
{
	//单个区块
	/*
	unsigned char
	*/
public:
	Blocks();
	~Blocks();
	Blocks(unsigned char u_,unsigned char v_,double r_);
private:
	//int u;
	//int v;
	//uv坐标
	unsigned char u;
	unsigned char v;
	Block block;
};
class Map
{
	//网格地图
public:
	Map();
	~Map();
	Map(double r_);
	void out()
	{
		cout<<sizeof(blocks)<<endl;
	}
private:
	//Blocks* pb;
	Blocks blocks[255][255];
};
class Maps
{
public:
	Maps();
	~Maps();

private:
	Map* map[10];
};


//class HexGrid
//{
//public:
//	HexGrid();
//
//private:
//
//};
