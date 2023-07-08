#pragma once
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<graphics.h>
#include"Games.h"
#include<mmsystem.h>
#include<string>
#include"cJSON.h"
#include<stdio.h>
#include<string.h>
#include"tools.h"
#include<Windows.h>
#include<ctime>
#include<conio.h>
#include"SystemManager.h"
#include"Transparent.h"
#include"MarioGlobal.h"
#include"Mario.h"
#include"Creature.h"
using namespace std;

class SuperMario:public Games
{
public:

	//构造函数
	SuperMario(string name);

	//析构函数
	~SuperMario();

	//运行游戏
	virtual void RunGame();

private:

	//读取地图文件
	char* getFileContent(const char* fileName);

	//解析图块集
	bool TileInit();

	//解析地图
	bool MapInit();

	//创建地图
	void CreateMap();

	//创建图像
	void CreateImgLine(IMAGE* img, const char* name);

	//用户交互
	int UserDo(string page);
	
	//显示菜单
	virtual void ShowGameMenu();

};

