#pragma once
#include"Creature.h"

class Mario :public Creature
{
	//���캯��
	Mario();
	
	//��Ⱦ��ɫ
	void Render(double x, double y, const char* file);

	//��������
	~Mario();
};

