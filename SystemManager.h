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

	//���ô���
	string SettingMenu(string page);

	//�û�����
	int UserDO(string page);
	
	//��ʾ�˵�
	string ShowMenu(int page);

	//��������
	~SystemManager();
};

