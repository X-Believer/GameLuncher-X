#pragma once
#include"Identity.h"
#include<iostream>

class User :public Identity
{
public:

	//Ĭ�Ϲ���
	User();
	
	//���캯��
	User(string id, string name, string pwd,int vip);

	//��ʾ��Ϣ
	virtual void ShowInfo();

	//�༭����
	void ChangeData();

	//���ý���
	void ResetProcess();

	//ע���˻�
	void CancleAccount();

	//��������
	~User();
};

