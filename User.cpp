#include "User.h"

//默认构造
User::User()
{

}

//构造函数
User::User(string id, string name, string pwd, int vip)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->m_isVip = vip;
}

//显示信息
void User::ShowInfo()
{

}

//编辑资料
void User::ChangeData()
{

}

//重置进度
void User::ResetProcess()
{

}

//注销账户
void User::CancleAccount()
{

}

//析构函数
User::~User()
{

}
