#pragma once
#include"Identity.h"
#include<iostream>

class User :public Identity
{
public:
	
	//构造函数
	User(int id, string name, string pwd);

	//显示信息
	virtual void ShowInfo();

	//编辑资料
	void ChangeData();

	//重置进度
	void ResetProcess();

	//注销账户
	void CancleAccount();

	//析构函数
	~User();
};

