#pragma once
#include<iostream>
#include<graphics.h>
#include<vector>
#include<string>
#include<mmsystem.h>
#include<Windows.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

class SystemManager
{
public:

	//���캯��
	SystemManager();

	//���´���
	void UpdateWindow();

	//�û�����
	int UserDO();
	
	//��ʾ�˵�
	string ShowMenu(int page);

	//ѡ����Ϸ
	void SelectGame();

	//��������
	~SystemManager();
};

