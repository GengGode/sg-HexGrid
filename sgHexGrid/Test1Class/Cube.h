#pragma once
#include "Hex.h"
class Cube :
	public Hex
{
public:
	enum Mode { hg, sg };
	Mode mode;
	bool legalFlag;

	Cube();
	Cube(int x_);
	Cube(int x_, int y_, int z_);
	Cube(int x_, int y_, int z_, Mode mode_);

	Cube(Hex hex_);
	Cube(Hex hex_,Mode mode_);

	Cube(Cube& cube_);
	Cube(Cube& cube_, Mode mode_);

	Hex hex();
	int R();
private:
	//int mod;
	
	
};

