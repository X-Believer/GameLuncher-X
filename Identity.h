#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Identity
{
public:

	//��ʾ�û���Ϣ
	virtual void ShowInfo() = 0;

	//�û��˺�
	string m_Id;

	//�û���
	string m_Name;

	//����
	string m_Pwd;

	//VIP
	int m_isVip;
};

