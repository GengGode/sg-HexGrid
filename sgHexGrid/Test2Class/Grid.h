#pragma once
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
	//�����ͼ
public:
	Map();
	~Map();

private:
	//Blocks* pb;
	Blocks blocks[255][255];
};

class Blocks:Block
{
	//��������
	/*
	unsigned char
	*/
public:
	Blocks();
	~Blocks();

private:
	//int u;
	//int v;
	//uv����
	unsigned char u;
	unsigned char v;
	//Block block;
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