#pragma once
class Vec
{
public:
	int p;
	int q;

	Vec();
	Vec(int p_);
	Vec(int p_, int q_);

	Vec(Vec& vec_);

	Vec operator+(const Vec& vec_);
	Vec operator-(const Vec& vec_);

	Vec operator+(const int& i);
	Vec operator-(const int& i);
	Vec operator*(const int& i);

	bool operator==(const Vec& vec_);

	Vec Tra();
private:
	double Abs();
};

