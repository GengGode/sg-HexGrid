#pragma once
#include"Axi.h"
#include"Off.h"
#include"Cube.h"
class Cell:public Axi,public Off,public Cube 
{
	enum Coor { ax, of, cu };
public:
	Cell();
	Cell(int u_, int v_);
	Cell(int u_, int v_, Coor coor_);
	Cell(int u_,int v_,Coor coor_,int mode_);
	Cell(int u_, int v_, int w_);
	Cell(int u_, int v_, int w_, Coor coor_);
	Cell(int u_, int v_, int w_, Coor coor_, int mode_);
	Cell(Axi axi);
	Cell(Off off);
	Cell(Cube cube);

	Axi axi();
	Axi off2Axi();
	Axi cube2Axi();

	Off off();
	Off axi2Off();
	Off cube2Off();

	Cube cube();
	Cube axi2Cube();
	Cube off2Cube();
private:
	
	int u;
	int v;
	int w;
	Coor coor;
	int mode;
	//Mode axiMode;
	//Mode offMode;
	//Mode cubeMode;

};

