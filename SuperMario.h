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
	//ÿ����ͼͼ��
	struct layer
	{
		char name[32];
		int *tiles;
		int width;
		int height;
	};

	//��ͼ
	struct map
	{
		int width;//��λ:ͼ��(42*42)
		int height;

		struct layer* layers;
		int layerCount;
	};

	map gameMap;
}

class SuperMario:public Games
{
public:

	//��ȡ��ͼ�ļ�
	char* getFileContent(const char* fileName);

	//������ͼ
	bool MapInit();

	//��ʾ����
	virtual void ShowGameMenu();

	//������Ϸ
	virtual void RunGame();
};

