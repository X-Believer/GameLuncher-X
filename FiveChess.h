#pragma once
#include<iostream>
#include<vector>
#include<graphics.h>
#include"Games.h"
#include<mmsystem.h>
#include<Windows.h>
using namespace std;

class FiveChess :public Games
{
public:

	//���캯��
	FiveChess(string name);

	//�û�����
	int UserDo();
	
	//�ж���Ӯ
	bool checkwin(int x, int y);

	//����ʵ��
	void drawchess(int m, int n);

	//��ʾ����
	virtual void ShowGameMenu();

	//������Ϸ
	virtual void RunGame();

	//��������
	~FiveChess();

};