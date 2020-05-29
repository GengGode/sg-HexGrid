#pragma once
#include<iostream>
using namespace std;

double xCos[] = { 0.866025, 0., -0.866025, -0.866025, 0., 0.866025 };
double xSin[] = { 0.5, 1., 0.5, -0.5, -1., -0.5 };
double yCos[] = { 1., 0.5, -0.5, -1., -0.5, 0.5 };
double ySin[] = { 0.,0.866025,0.866025,0.,-0.866025,-0.866025 };

class Grid
{
	//��̨
public:
	

};
class Hex
{
	//������
public:
	Hex();
	~Hex();
	Hex(double x_,double y_,double r_);
private:
	//Coor cen;//center
	//Coor cor;//corner
	/*/ ��ͼ���� /*/
	double x;
	double y;
	//Coor corner[];
	double corner[2][6];//������


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
	//��������
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
	//��������
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
	//uv����
	unsigned char u;
	unsigned char v;
	Block block;
};
class Map
{
	//�����ͼ
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
