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

namespace
{
	//每个地图图层
	struct layer
	{
		char name[32];
		int *tiles;
		int width;
		int height;
		int type;
	};

	//地图
	struct map
	{
		int width;//单位:图块(42*42)
		int height;

		struct layer* layers;
		int layerCount;
	};

	map gameMap;
}

class SuperMario:public Games
{
public:

	//读取地图文件
	char* getFileContent(const char* fileName);

	//解析地图
	bool MapInit();

	//显示设置
	virtual void ShowGameMenu();

	//运行游戏
	virtual void RunGame();
};

