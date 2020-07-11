#include "Config.h"

Config::Config()
{
}

globalConfig Config::global()
{
	return gl;
}

gridConfig Config::grid()
{
	return gr;
}

renderConfig Config::render()
{
	return re;
}

globalConfig::globalConfig()
{
}

gridConfig::gridConfig()
{
}

renderConfig::renderConfig()
{
}

Color::Color()
{
	r = 128;
	g = 128;
	b = 128;
}

Color::Color(double i_) :Color(i_, i_, i_) {}

Color::Color(double r_, double g_, double b_)
{
	R(r_);
	G(g_);
	B(b_);
}

void Color::R(double i_)
{
	if (i_ > 0)
	{
		if (i_ < 1)
		{
			r = (int) (i_ * 255);
		}
		else
		{
			if (i_ < 256)
			{
				r = (int) i_;
			}
			else
			{
				r = 255;
			}
		}
	}
	else
	{
		r = 0;
	}
}

void Color::G(double i_)
{
	if (i_ > 0)
	{
		if (i_ < 1)
		{
			g = (int) (i_ * 255);
		}
		else
		{
			if (i_ < 256)
			{
				g = (int) i_;
			}
			else
			{
				g = 255;
			}
		}
	}
	else
	{
		g = 0;
	}
}

void Color::B(double i_)
{
	if (i_ > 0)
	{
		if (i_ < 1)
		{
			b = (int) (i_ * 255);
		}
		else
		{
			if (i_ < 256)
			{
				b = (int) i_;
			}
			else
			{
				b = 255;
			}
		}
	}
	else
	{
		b = 0;
	}
}

//unsigned char Color::R()
//{
//	return r;
//}
//
//unsigned char Color::G()
//{
//	return g;
//}
//
//unsigned char Color::B()
//{
//	return b;
//}

