#pragma once
#include"MarioGlobal.h"
using namespace std;

class Creature
{
protected:
	
	//与生物碰撞
	bool CreatureCollide(double x, double y, Creature& creature);

	//检测上方碰撞
	pair<double, bool> UpCollide(double lastx, double lasty);

	//检测下方碰撞
	pair<double, bool> DownCollide(double lastx, double lasty);

	//检测左右碰撞
	pair<double, bool> SideCollide(double lastx, double lasty);

public:
	//构造函数
	Creature();

	//析构函数
	~Creature();

	//设置位置
	void SetPos(double x, double y, double width, double height); 

	//渲染角色
	virtual void Render(double x, double y, const char* file = NULL);

	//更新角色
	virtual void UpdateStatus(int type = 0, int damage = 0);

	//检测是否往下掉
	virtual  bool CheckFall();

	//报告碰撞(layer 1->图块层 2->对象层 3->生物层)
	virtual bool ReportCollide(int direction, Creature* target = NULL, int layer = 1);

	//被击杀
	virtual void Kill(int direction = 0);

	//速度计算
	virtual void SpeedCal();

	int direction = 0; // 面向方向，0左, 1右
	int CreatureLayer = 3;//1图块层 2对象层 3生物层 0空气层
	int m_Health;//生命
	int m_Mass;//质量
	double m_X, m_Y;//当前位置
	double m_Wid, m_Hei;//角色宽高
	string m_Name = "None";

protected:

	double m_Vx, m_Vy;//角色速度
	double m_Fx, m_Fy;//角色受力
	double max_Px, max_Py;//最大功率
	string PicFile;

	bool out_of_range = true; //允许超出地图范围
	bool isShow = false;//是否显示
	bool isOnFloor = false;//是否在地面
	bool isFly = false;//是否可以飞行
	bool isInvincible = false;//是否无敌
};

//生物图层
extern vector<Creature>CreatureVec;

