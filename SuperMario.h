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
using namespace std;

class SuperMario:public Games
{
public:

	//读取地图文件
	char* getFileContent(const char* fileName);

	//解析图块集
	bool TileInit();

	//解析地图
	bool MapInit();

	//创建地图
	void CreateMap();

	//显示设置
	virtual void ShowGameMenu();

	//运行游戏
	virtual void RunGame();
};

