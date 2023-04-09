#pragma once
#include"Identity.h"
#include<iostream>

class User :public Identity
{
public:

	//默认构造
	User();
	
	//构造函数
	User(string id, string name, string pwd,int vip);

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

