#pragma once
#include<iostream>
#include<graphics.h>
#include<vector>
#include<string>
#include<mmsystem.h>
#include<Windows.h>
#include<conio.h>
#include"Identity.h"
#pragma comment(lib,"winmm.lib")
using namespace std;

extern int MusicFlag;
extern int SoundFlag;
extern int IsLogin;

class SystemManager:public Identity
{
public:

	//默认构造
	SystemManager();

	//构造函数
	SystemManager(string name,string pwd);

	//设置菜单
	string SettingMenu(string page);

	//用户交互
	int UserDO(string page);
	
	//显示主菜单
	string ShowMenu(int page);

	//账户菜单
	string AccountMenu(string page);

	//信息窗口
	int MSGWindow(string page, const char* word);

	//显示信息(系统信息)
	virtual void ShowInfo();

	//添加账号
	void AddAccount();

	//删除账号
	void DeleteAccount();

	//析构函数
	~SystemManager();

};

