#include "Grid.h"
Hex::Hex() : Hex(0, 0, 1) {}
Hex::Hex(double x_, double y_, double r_)
{
	x = x_;
	y = y_;
	//double xCos[] = { 0.866025, 0., -0.866025, -0.866025, 0., 0.866025 };
	//double xSin[] = { 0.5, 1., 0.5, -0.5, -1., -0.5 };
	//for (int i = 0; i < 6; i++)
	//{
	//	corner[0][i] = x + r_ * xCos[i];
	//	corner[1][i] = y + r_ * xSin[i];
	//}
}
//Hex::~Hex() {}

Block::Block() : Block(10) {}
Block::Block(double r_) : Block(0, 0, r_) {}
Block::Block(double u_, double v_, double r_)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			hex[i][j] = Hex(u_ + i * r_, v_ + j * r_, r_);
}
//Block::~Block() {}

Blocks::Blocks() : Blocks(0, 0, 10) {}
Blocks::Blocks(unsigned char u_, unsigned char v_, double r_)
{
	u = u_;
	v = v_;
	block = Block(u_ * r_ * 8, v_ * r_ * 8, r_);
}
//Blocks::~Blocks() {}

//Map::Map() : Map(10) {}
//Map::Map(double r_)
//{
//	for (int i = 0; i < 8; i++)
//		for (int j = 0; j < 8; j++)
//			blocks[i][j] = Blocks(i, j, r_);
//}
//Map::~Map() {}