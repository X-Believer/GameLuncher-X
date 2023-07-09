#pragma once
#include"Creature.h"

class Mario : public Creature
{
	friend class SuperMario;
public:

	//构造函数
	Mario();
	
	//渲染角色
	void Render(double x, double y, const char* file = NULL);

	//更新角色 0->freeze 1->idle 2->run 3->jump 4->down 5->climb 6->attack 7->squat
	void UpdateStatus(int type = 0, int damage = 0);

	//检测碰撞
	void CheckCollide(double lastx, double lasty);

	//报告碰撞
	bool ReportCollide(int direction, Creature* target = NULL, int layer=1);

	//被击杀
	void Kill(int direction = 0);

	//析构函数
	~Mario();

private:
	int animationTime = 0;      //动画时间戳
	int changeTime = 0;         //改变等级时间戳
	int invincibleTime = 0; //无敌动画闪烁时间戳
	int fireTime = 0; //发射火焰时间
	bool jumpKey = false;
	bool jumpSound = false;
	bool flagDirection;     //摸旗方向
	bool isSquat = false; //是否下蹲
	bool isDash = false; //是否处于冲刺状态
	bool changeSize = false; //是否改变状态大小

	//起立
	bool MarioStand();

	//下蹲
	bool MarioSquat();

	//跳跃
	bool MarioJump();

	//变身
	bool MarioChange(int type);

};

