#pragma once
#include "Vec.h"
class Axi :
	public Vec
{
public:
	enum Mode{xy,yz,zx};
	Mode mode;

	Axi();
	Axi(int p_);
	Axi(int p_, int q_);
	Axi(int p_, Mode mode_);
	Axi(int p_, int q_,Mode mode_);

	Axi(Vec vec_);
	Axi(Vec vec_,Mode mode_);

	Axi(Axi& axi_);
	Axi(Axi& axi_, Mode mode_);

	Vec vec();
};

