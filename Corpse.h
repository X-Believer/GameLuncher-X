#pragma once
#include "Creature.h"
class Corpse : public Creature
{
public:
	//构造函数
	Corpse(int row, int col);

	//析构函数
	~Corpse();
};

