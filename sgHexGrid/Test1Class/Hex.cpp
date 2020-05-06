#include "Hex.h"

Hex::Hex()
{
	x = 0;
	y = 0;
	z = 0;
}
Hex::Hex(int x_) :x(x_), y(x_), z(x_) {}
Hex::Hex(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
Hex::Hex(Hex& hex_)
{
	x = hex_.x;
	y = hex_.y;
	z = hex_.z;
}
Hex Hex::operator+(const Hex& hex_)
{
	Hex hex;
	hex.x = x + hex_.x;
	hex.y = y + hex_.y;
	hex.z = z + hex_.z;
	return hex;
}
Hex Hex::operator-(const Hex& hex_)
{
	Hex hex;
	hex.x = x - hex_.x;
	hex.y = y - hex_.y;
	hex.z = z - hex_.z;
	return hex;
}
Hex Hex::operator+(const int& i)
{
	Hex hex;
	hex.x = x + i;
	hex.y = y + i;
	hex.z = z + i;
	return hex;
}
Hex Hex::operator-(const int& i)
{
	Hex hex;
	hex.x = x - i;
	hex.y = y - i;
	hex.z = z - i;
	return hex;
}
Hex Hex::operator*(const int& i)
{
	Hex hex;
	hex.x = x * i;
	hex.y = y * i;
	hex.z = z * i;
	return hex;
}
bool Hex::operator==(const Hex& hex_)
{
	if (x == hex_.x&&y == hex_.y&&z == hex_.z)
		return true;
	else
		return false;
}
double Hex::Abs()
{
	int w = x * x + y * y + z * z;
	float whalf = 0.5f * w;

	int i = *(int*) &w;           // get bits for floating VALUE 
	i = 0x5f3759df - (i >> 1);     // gives initial guess y0
	w = *(float*) &i;             // convert bits BACK to float
	w = w * (1.5f - whalf * w*w);    // Newton step, repeating increases accuracy
	w = w * (1.5f - whalf * w*w);    // Newton step, repeating increases accuracy
	w = w * (1.5f - whalf * w*w);    // Newton step, repeating increases accuracy
	return (1 / w);
}

