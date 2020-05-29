#pragma once
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

class Maps
{
public:
	Maps();
	~Maps();

private:
	Map* map[];
};
class Map
{
	//网格地图
public:
	Map();
	~Map();

private:
	//Blocks* pb;
	Blocks blocks[255][255];
};

class Blocks:Block
{
	//单个区块
	/*
	unsigned char
	*/
public:
	Blocks();
	~Blocks();

private:
	//int u;
	//int v;
	//uv坐标
	unsigned char u;
	unsigned char v;
	//Block block;
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

private:
	//unsigned char i;
	//unsigned char j;
	Hex hex[255][255];
};
//class HexGrid
//{
//public:
//	HexGrid();
//
//private:
//
//};