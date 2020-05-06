#include "Axi.h"

Axi::Axi()
{
	p = 0;
	q = 0;
	mode = xy;
}
Axi::Axi(int p_)
{
	p = p_;
	q = p_;
	mode = xy;
}
Axi::Axi(int p_, int q_)
{
	p = p_;
	q = q_;
	mode = xy;
}
Axi::Axi(int p_, Mode mode_)
{
	p = p_;
	q = p_;
	mode = mode_;
}
Axi::Axi(int p_, int q_, Mode mode_)
{
	p = p_;
	q = q_;
	mode = mode_;
}
Axi::Axi(Vec vec_)
{
	p = vec_.p;
	q = vec_.q;
	mode = xy;
}
Axi::Axi(Vec vec_, Mode mode_)
{
	p = vec_.p;
	q = vec_.q;
	mode = mode_;
}
Axi::Axi(Axi& axi_)
{
	p = axi_.p;
	q = axi_.q;
	mode = axi_.mode;
}
Axi::Axi(Axi& axi_, Mode mode_)
{
	p = axi_.p;
	q = axi_.q;
	mode = mode_;
}
Vec Axi::vec()
{
	Vec vec;
	vec.p = p;
	vec.q = q;
	return vec;
}