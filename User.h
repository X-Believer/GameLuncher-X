#pragma once
#include"Identity.h"
#include<iostream>

class User :public Identity
{
public:
	
	//���캯��
	User(int id, string name, string pwd);

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

