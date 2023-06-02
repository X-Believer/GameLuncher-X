#pragma once
#include<iostream>
#include<graphics.h>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;

class Creature
{
public:
	int m_Health;//生命
	double m_X, m_Y;//当前位置
	double m_Wid, m_Hei;//角色宽高
	double m_Vx, m_Vy;//角色速度
	double m_Fx, m_Fy;//角色受力

	bool isShow;//是否显示
	bool IsCollide(double x, double y, Creature& creature);

};

