#pragma once
#ifndef DRAWHEX_H

#include"Config.h"
#include"Render.h"
#include"Grid.h"

class DrawHex
{
public:
	DrawHex();
	~DrawHex();
	void show(char* name);
private:
	Render render;//前台
	Grid grid;//后台
	Config config;//
	//参数
};

#endif // !DRAWHEX_H