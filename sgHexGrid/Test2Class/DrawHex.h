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
	Render render;//ǰ̨
	Grid grid;//��̨
	Config config;//
	//����
};

#endif // !DRAWHEX_H