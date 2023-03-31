#pragma once
#include<iostream>
#include<graphics.h>
#include<vector>
#include<string>
using namespace std;

class Games
{
public:

	//显示游戏菜单
	virtual void ShowGameMenu() = 0;

	//运行游戏
	virtual void RunGame() = 0;

	//玩家名
	string m_PlayerName;
};

