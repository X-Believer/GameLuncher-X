#pragma once
#include<iostream>
#include<graphics.h>
#include<vector>
#include<string>
using namespace std;

class Games
{
public:

	//��ʾ��Ϸ�˵�
	virtual void ShowGameMenu() = 0;

	//������Ϸ
	virtual void RunGame() = 0;

	//�����
	string m_PlayerName;
};

