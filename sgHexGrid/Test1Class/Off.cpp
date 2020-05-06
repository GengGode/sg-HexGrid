#include "Off.h"
Off::Off()
{
	p = 0;
	q = 0;
	mode = hgt;
}
Off::Off(int p_)
{
	p = p_;
	q = p_;
	mode = hgt;
}
Off::Off(int p_, int q_)
{
	p = p_;
	q = q_;
	mode = hgt;
}
Off::Off(int p_, Mode mode_)
{
	p = p_;
	q = p_;
	mode = mode_;
}
Off::Off(int p_, int q_, Mode mode_)
{
	p = p_;
	q = q_;
	mode = mode_;
}
Off::Off(Vec vec_)
{
	p = vec_.p;
	q = vec_.q;
	mode = hgt;
}
Off::Off(Vec vec_, Mode mode_)
{
	p = vec_.p;
	q = vec_.q;
	mode = mode_;
}
Off::Off(Off& off_)
{
	p = off_.p;
	q = off_.q;
	mode = off_.mode;
}
Off::Off(Off& off_, Mode mode_)
{
	p = off_.p;
	q = off_.q;
	mode = mode_;
}
Vec Off::vec()
{
	Vec vec;
	vec.p = p;
	vec.q = q;
	return vec;
}