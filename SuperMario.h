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

	//��ȡ��ͼ�ļ�
	char* getFileContent(const char* fileName);

	//����ͼ�鼯
	bool TileInit();

	//������ͼ
	bool MapInit();

	//������ͼ
	void CreateMap();

	//��ʾ����
	virtual void ShowGameMenu();

	//������Ϸ
	virtual void RunGame();
};

