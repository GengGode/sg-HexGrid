#include "Cube.h"

Cube::Cube()
{
	x = 0;
	y = 0;
	z = 0;
	mode = hg;
	legalFlag = true;
}
Cube::Cube(int x_) //:x(x_), y(x_), z(x_)
{
	x = x_;
	y = x_;
	z = x_;
	mode = hg;
	x_ == 0 ? legalFlag = true : legalFlag = false;
}
Cube::Cube(int x_, int y_, int z_)// : x(x_), y(y_), z(z_)
{
	x = x_;
	y = y_;
	z = z_;
	mode = hg;
	x + y + z == 0 ? legalFlag = true : legalFlag = false;
}
Cube::Cube(int x_, int y_, int z_, Mode mode_)
{
	x = x_;
	y = y_;
	z = z_;
	mode = mode_;
	x + y + z == 0 ? legalFlag = true : legalFlag = false;
}
Cube::Cube(Hex hex_)
{
	x = hex_.x;
	y = hex_.y;
	z = hex_.z;
	mode = hg;
	x + y + z == 0 ? legalFlag = true : legalFlag = false;
}
Cube::Cube(Hex hex_,Mode mode_)
{
	x = hex_.x;
	y = hex_.y;
	z = hex_.z;
	mode = mode_;
	x + y + z == 0 ? legalFlag = true : legalFlag = false;
}

Cube::Cube(Cube& cube_)
{
	x = cube_.x;
	y = cube_.y;
	z = cube_.z;
	mode = cube_.mode;
	legalFlag = cube_.legalFlag;
}

Cube::Cube(Cube& cube_, Mode mode_)
{
	x = cube_.x;
	y = cube_.y;
	z = cube_.z;
	mode = mode_;
	legalFlag = cube_.legalFlag;
}

Hex Cube::hex()
{
	Hex hex;
	hex.x = x;
	hex.y = y;
	hex.z = z;
	return hex;
}

int Cube::R()
{
	int r = x;
	if (r < y)r = y;
	if (r < z)r = z;
	return r;
}

