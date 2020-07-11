#pragma once
#ifndef GRID_H

#include"Config.h"
#include<iostream>
using namespace std;

//extern double xCos[] = { 0.866025, 0., -0.866025, -0.866025, 0., 0.866025 };
//extern double xSin[] = { 0.5, 1., 0.5, -0.5, -1., -0.5 };
//extern double yCos[] = { 1., 0.5, -0.5, -1., -0.5, 0.5 };
//extern double ySin[] = { 0.,0.866025,0.866025,0.,-0.866025,-0.866025 };


class Hex
{
	//������
public:
	Hex();
	//~Hex();
	Hex(double x_, double y_, double r_);
private:
	//Coor cen;//center
	//Coor cor;//corner
	/*/ ��ͼ���� /*/
	double x, y;
	//int x, y;
	//Coor corner[];
	//double corner[2][6];//������


};

class Coor
{
	//�����
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
	//�������
public:


	GridMode();
private:
	Mode u;
	Mode v;
};

class Rule
{
public:
	Rule();
private:
	unsigned char *lis;
	unsigned char count;
};
class Rules
{
public:
	Rules();
	Rule exist() { return Exist; }
	Rule death() { return Death; }
private:
	Rule Exist;
	Rule Death;
};
class RanderMode
{
public:
	RanderMode();

private:
	Coor coff;
	double r;
	double w;
	double b;
	double dr;
	//double step;
};
class GridSet
{
public:
	GridSet();

private:
	GridMode gm;
	Rules gr;
	RanderMode grm;
};

class Block
{
	//��������
	/*
	unsigned char
	*/
public:
	bool randerflag[8][8];

	Block();
	//~Block();
	Block(double r_);
	Block(double u_, double v_, double r_);
private:
	//unsigned char i;
	//unsigned char j;
	Hex hex[8][8];
};
class Blocks//:Block
{
	//��������
	/*
	unsigned char
	*/
public:
	Blocks();
	//~Blocks();
	Blocks(unsigned char u_, unsigned char v_, double r_);
private:
	//int u;
	//int v;
	//uv����
	unsigned char u;
	unsigned char v;
	Block block;
};


class Grid
{
	//��̨
public:
	Grid();
private:
	GridSet gs;
	Blocks bs;

};

#endif // !GRID_H

//class Map
//{
//	//�����ͼ
//public:
//	Map();
//	//~Map();
//	Map(double r_);
//	void out()
//	{
//		cout << sizeof(blocks)/sizeof(Block) << endl<<sizeof(Block) << endl;;
//	}
//private:
//	//Blocks* pb;
//	Blocks blocks[8][8];
//};
//class Maps
//{
//public:
//	Maps();
//	//~Maps();
//
//private:
//	Map* map[10];
//};


//class HexGrid
//{
//public:
//	HexGrid();
//
//private:
//
//};
