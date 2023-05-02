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
#include<conio.h>
#include"SystemManager.h"
#include"Transparent.h"
using namespace std;

class SuperMario:public Games
{
public:

	//���캯��
	SuperMario(string name);

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

	//���½���
	void UpdateWindow();

	//�û�����
	int UserDo(string page);
	
	//��ʾ�˵�
	virtual void ShowGameMenu();

	//������Ϸ
	virtual void RunGame();

	//��������
	~SuperMario();
};

