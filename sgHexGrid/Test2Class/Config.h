#pragma once
#ifndef CONFIG_H

#include<opencv2/opencv.hpp>
//extern double xCos[] = { 0.866025, 0., -0.866025, -0.866025, 0., 0.866025 };
//extern double xSin[] = { 0.5, 1., 0.5, -0.5, -1., -0.5 };
//extern double yCos[] = { 1., 0.5, -0.5, -1., -0.5, 0.5 };
//extern double ySin[] = { 0.,0.866025,0.866025,0.,-0.866025,-0.866025 };

class Config
{
public:
	Config();
	globalConfig global();
	gridConfig grid();
	renderConfig render();
private:
	globalConfig gl;
	gridConfig gr;
	renderConfig re;
};
class globalConfig
{
public:
	globalConfig();
private:

};

class gridConfig
{
public:
	gridConfig();
private:
};

class renderConfig
{
public:
	renderConfig();
private:
	Color BackgroundC;
};

class Color
{
public:
	Color();
	Color(double i_);
	Color(double r_, double g_, double b_);
	void R(double i_);
	void G(double i_);
	void B(double i_);
	//unsigned char R();
	//unsigned char G();
	//unsigned char B();

private:
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

#endif // !CONFIG_H

