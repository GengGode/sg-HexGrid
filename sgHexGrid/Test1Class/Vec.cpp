#include "Vec.h"

Vec::Vec()
{
	p = 0;
	q = 0;
}
Vec::Vec(int p_) :p(p_), q(p_) {}
Vec::Vec(int p_, int q_) : p(p_), q(q_) {}
Vec::Vec(Vec& vec_)
{
	p = vec_.p;
	q = vec_.q;
}
Vec Vec::operator+(const Vec& vec_)
{
	Vec vec;
	vec.p = p + vec_.p;
	vec.q = q + vec_.q;
	return vec;
}
Vec Vec::operator-(const Vec& vec_)
{
	Vec vec;
	vec.p = p - vec_.p;
	vec.q = q - vec_.q;
	return vec;
}

Vec Vec::operator+(const int& i)
{
	Vec vec;
	vec.p = p + i;
	vec.q = q + i;
	return vec;
}
Vec Vec::operator-(const int& i)
{
	Vec vec;
	vec.p = p - i;
	vec.q = q - i;
	return vec;
}
Vec Vec::operator*(const int& i)
{
	Vec vec;
	vec.p = p * i;
	vec.q = q * i;
	return vec;
}
bool Vec::operator==(const Vec& vec_)
{
	if (p == vec_.p&&q == vec_.q)
		return true;
	else 
		return false;
}
Vec Vec::Tra()
{
	Vec vec;
	vec.p = q;
	vec.q = p;
	return vec;
}
double Vec::Abs()
{
	int w = p * p + q * q;
	float whalf = 0.5f * w;

	int i = *(int*) &w;           // get bits for floating VALUE 
	i = 0x5f3759df - (i >> 1);     // gives initial guess y0
	w = *(float*) &i;             // convert bits BACK to float
	w = w * (1.5f - whalf * w*w);    // Newton step, repeating increases accuracy
	w = w * (1.5f - whalf * w*w);    // Newton step, repeating increases accuracy
	w = w * (1.5f - whalf * w*w);    // Newton step, repeating increases accuracy
	return (1 / w);
}