#include "Cell.h"
Cell::Cell()
{
	u = 0;
	v = 0;
	w = 0;
	coor = ax;
	mode = 0;
}
Cell::Cell(int u_, int v_):u(u_),v(v_)
{
	coor = ax;
	mode = 0;
}
Cell::Cell(int u_, int v_, Coor coor_) : u(u_), v(v_), coor(coor_)
{
	mode = 0;
}
Cell::Cell(int u_, int v_, Coor coor_, int mode_) : u(u_), v(v_), coor(coor_), mode(mode_) {}
Cell::Cell(int u_, int v_, int w_) : u(u_), v(v_),w(w_)
{
	coor = cu;
	mode = 0;
}
Cell::Cell(int u_, int v_, int w_, Coor coor_) : u(u_), v(v_), w(w_), coor(coor_)
{
	mode = 0;
}
Cell::Cell(int u_, int v_, int w_, Coor coor_, int mode_) : u(u_), v(v_), w(w_), coor(coor_), mode(mode_){}
Cell::Cell(Axi axi)
{
	u = axi.p;
	v = axi.q;
	coor = ax;
	mode = axi.mode;
}
Cell::Cell(Off off)
{
	u = off.p;
	v = off.q;
	coor = of;
	mode = off.mode;
}
Cell::Cell(Cube cube)
{
	u = cube.x;
	v = cube.y;
	w = cube.z;
	coor = cu;
	mode = cube.mode;
}
Axi Cell::axi()
{
	Axi out;
	if (coor == ax)
	{
		out.p = u;
		out.q = v;
		out.mode = Axi::Mode(mode);
	}
	else if (coor = of)
	{
		out = off2Axi();
	}
	else if (coor = cu)
	{
		out = cube2Axi();
	}
	return out;
}
Axi Cell::off2Axi()
{

}
Axi Cell::cube2Axi()
{
	Axi out(u, v);
	return out;
}

Off Cell::off()
{
	Off out;
	if (coor == ax)
	{
		out = axi2Off();
	}
	else if (coor = of)
	{
		out.p = u;
		out.q = v;
		out.mode = Off::Mode(mode);
	}
	else if (coor = cu)
	{
		out = cube2Off();
	}
	return out;
}
Off Cell::axi2Off()
{

}
Off Cell::cube2Off()
{

}

Cube Cell::cube()
{
	Cube out;
	if (coor == ax)
	{
		out = axi2Cube();
	}
	else if (coor = of)
	{
		out = off2Cube();
		
	}
	else if (coor = cu)
	{
		out.x = u;
		out.y = v;
		out.z = w;
		out.mode = Cube::Mode(mode);
	}
	return out;

}
Cube Cell::axi2Cube()
{
	Cube out;
	out.x = u;
	out.y = v;
	out.z = -u - v;
	out.mode = hg;
	return out;
}
Cube Cell::off2Cube()
{

}