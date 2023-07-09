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
#include"ChestNut.h"
#include"GreenTortoise.h"
#include"FlyTortoise.h"
#include"Flower.h"
#include"Mushroom.h"
#include"QuestionBlock.h"
#include"MarioCoin.h"
#include"Corpse.h"
#include"MarioFlag.h"
#include"Creature.h"
using namespace std;

class SuperMario:public Games
{
public:

	//���캯��
	SuperMario(string name);

	//��������
	~SuperMario();

	//������Ϸ
	virtual void RunGame();

private:

	//��ȡ��ͼ�ļ�
	char* getFileContent(const char* fileName);

	//����ͼ�鼯
	bool TileInit();

	//������ͼ
	bool MapInit();

	//������ͼ
	void CreateMap();

	//����ͼ��
	void CreateImgLine(IMAGE* img, const char* name);

	//�û�����
	int UserDo(string page);
	
	//��ʾ�˵�
	virtual void ShowGameMenu();

};

