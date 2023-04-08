#pragma once
#include<iostream>
#include<fstream>
#include<graphics.h>
#include<vector>
#include<string>
#include<mmsystem.h>
#include<Windows.h>
#include<conio.h>
#include<ctime>
#include"User.h"
#include"Identity.h"
#pragma comment(lib,"winmm.lib")
using namespace std;

extern int MusicFlag;
extern int SoundFlag;
extern int IsLogin;

class SystemManager:public Identity
{
public:

	//Ĭ�Ϲ���
	SystemManager();

	//���캯��
	SystemManager(string name,string pwd);

	//���ò˵�
	string SettingMenu(string page);

	//�û�����
	int UserDO(string page);
	
	//��ʾ���˵�
	string ShowMenu(int page);

	//�˻��˵�
	string AccountMenu(string page);

	//��Ϣ����
	int MSGWindow(string page, const char* word);

	//��ʾ��Ϣ(ϵͳ��Ϣ)
	virtual void ShowInfo();

	//��¼��֤
	string SystemLogin(string name, string pwd, string filename,int type);

	//����˺�
	void AddAccount();

	//ɾ���˺�
	void DeleteAccount();

	//��������
	~SystemManager();

};

