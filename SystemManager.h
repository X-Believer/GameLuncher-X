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

	//��������
	~SystemManager();

	//���ò˵�
	string SettingMenu(string page);

	//��ʾ���˵�
	string ShowMenu(int page);

	//����ҳ��
	string LoadingMenu();

	//��Ϣ����
	int MSGWindow(string page, const char* word);

private:

	//�û�����
	int UserDO(string page);

	//�˻��˵�
	string AccountMenu(string page);

	//��ʾ��Ϣ(����Ա����)
	virtual void ShowInfo();

	//��¼��֤
	string SystemLogin(string name, string pwd, string filename,int type);

	//ɾ���˺�
	void DeleteAccount(int pos,string filename);

};

