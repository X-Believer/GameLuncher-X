#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Identity
{
public:

	//显示用户信息
	virtual void ShowInfo() = 0;

	//用户账号
	string m_Id;

	//用户名
	string m_Name;

	//密码
	string m_Pwd;

	//VIP
	int m_isVip;
};

