#pragma once
#include"Creature.h"

class Mario :public Creature
{
	//构造函数
	Mario();
	
	//渲染角色
	void Render(double x, double y, const char* file);

	//析构函数
	~Mario();
};

