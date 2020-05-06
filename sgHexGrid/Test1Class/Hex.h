#pragma once
class Hex
{
public:

	int x;
	int y;
	int z;

	Hex();
	Hex(int x_);
	Hex(int x_, int y_, int z_);

	Hex(Hex& hex_);

	Hex operator+(const Hex& hex_);
	Hex operator-(const Hex& hex_);
	Hex operator+(const int& i);
	Hex operator-(const int& i);
	Hex operator*(const int& i);

	bool operator==(const Hex& hex_);
private:
	double Abs();
};