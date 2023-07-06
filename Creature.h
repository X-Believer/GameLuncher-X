#pragma once
#include<iostream>
#include<graphics.h>
#include<set>
#include<vector>
#include<algorithm>
#include<string>
#include"Transparent.h"
using namespace std;

class Creature
{
public:
	int m_Health;//生命
	double m_X, m_Y;//当前位置
	double m_Wid, m_Hei;//角色宽高
	double m_Vx, m_Vy;//角色速度
	double m_Fx, m_Fy;//角色受力
	string PicFile;

	bool out_of_range = true; //允许超出地图范围
	bool last_direction = false; // 面向方向，false右, true 左

	bool isShow;//是否显示
	bool IsCollide(double x, double y, Creature& creature);
	void SetPos(double x, double y, double width, double height); //设置位置

	virtual void Render(double x, double y, const char* file)=0; //渲染角色
	virtual void Kill(int direction)=0; //被击杀
};

