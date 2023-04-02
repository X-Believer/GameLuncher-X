#pragma once
#include<iostream>
#include<graphics.h>
#include<vector>
#include<string>
#include<mmsystem.h>
#include<Windows.h>
#include<conio.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

class SystemManager
{
public:

	//构造函数
	SystemManager();

	//设置菜单
	string SettingMenu(string page);

	//用户交互
	int UserDO(string page);
	
	//显示菜单
	string ShowMenu(int page);

	//析构函数
	~SystemManager();
};

