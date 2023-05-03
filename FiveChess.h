#pragma once
#include<iostream>
#include<vector>
#include<graphics.h>
#include"Games.h"
#include<mmsystem.h>
#include<Windows.h>
using namespace std;

class FiveChess :public Games
{
public:

	//构造函数
	FiveChess(string name);

	//析构函数
	~FiveChess();

	//运行游戏
	virtual void RunGame();

private:

	//用户交互
	int UserDo();
	
	//判断输赢
	bool checkwin(int x, int y);

	//落子实现
	void drawchess(int m, int n);

	//显示设置
	virtual void ShowGameMenu();

};