#pragma once
#include<iostream>
#include<graphics.h>
#include<vector>
#include<string>
#include<mmsystem.h>
#include<Windows.h>
#include<conio.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

extern int MusicFlag;
extern int SoundFlag;
extern int IsLogin;

class SystemManager
{
public:

	//���캯��
	SystemManager();

	//���ò˵�
	string SettingMenu(string page);

	//�û�����
	int UserDO(string page);
	
	//��ʾ�˵�
	string ShowMenu(int page);

	//��������
	~SystemManager();

};

