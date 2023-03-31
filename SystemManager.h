#pragma once
#include<iostream>
#include<graphics.h>
#include<vector>
#include<string>
#include<mmsystem.h>
#include<Windows.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

class SystemManager
{
public:

	//构造函数
	SystemManager();

	//更新窗口
	void UpdateWindow();

	//用户交互
	int UserDO();
	
	//显示菜单
	string ShowMenu(int page);

	//选择游戏
	void SelectGame();

	//析构函数
	~SystemManager();
};

