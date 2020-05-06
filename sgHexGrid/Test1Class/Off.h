#pragma once
#include "Vec.h"
class Off :
	public Vec
{
public:
	enum Mode{hgt,hgo,sgt,sgo};
	Mode mode;

	Off();
	Off(int p_);
	Off(int p_,int q_);
	Off(int p_,Mode mode_);
	Off(int p_,int q_,Mode mode_);
	
	Off(Vec vec_);
	Off(Vec vec_, Mode mode_);

	Off(Off& off_);
	Off(Off& off_,Mode mode_);

	Vec vec();
};

