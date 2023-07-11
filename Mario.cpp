#include "Mario.h"
namespace
{
	IMAGE Run_Red[8]; IMAGE Idle_Red[4]; IMAGE Jump_Red[2]; IMAGE Climb_Red[6]; IMAGE Squat_Red[2]; IMAGE Down_Red[2];
	IMAGE Run_White[8]; IMAGE Idle_White[4]; IMAGE Jump_White[2]; IMAGE Climb_White[6]; IMAGE Squat_White[2]; IMAGE Down_White[2];
	IMAGE Change_RtoS; IMAGE Change_RtoW[2]; IMAGE Change_WtoS;
	IMAGE Attack[2]; IMAGE Victory[2]; IMAGE Gas[2];

	string toLoad; 
	//MarioMode 0->Red 1->White
	int MarioMode = 0;
}

//构造函数
Mario::Mario()
{
	this->m_Name = "Mario";
	this->m_Health = 100;
	this->isShow = true;
	this->PicFile = "Graph/SuperMario/";
	this->m_Hei = 76;
	this->m_Wid = 50;
	this->m_Mass = 1;
	this->m_X = 8.0 * TileWid;
	this->m_Y = 540 + Margin - 2.0 * 42 - this->m_Hei;
	this->m_Fx = 0;
	this->m_Fy = -Gravity;//初始状态与重力平衡
	this->m_Vx = 0;
	this->m_Vy = 0;
	this->max_Px = 100;
	this->max_Py = 1850;
	this->isInvincible = false;

	this->out_of_range = false;
	this->direction = 1;

	//加载图片
	if (1)
	{
		//红色跑步图片
		for (int i = 0; i < 8; i++)
		{
			toLoad = this->PicFile + "Red/run_" + to_string(i) + ".png";
			loadimage(Run_Red + i, toLoad.c_str());
		}

		//白色跑步图片
		for (int i = 0; i < 8; i++)
		{
			toLoad = this->PicFile + "White/run_" + to_string(i) + ".png";
			loadimage(Run_White + i, toLoad.c_str());
		}

		//红色待机图片
		for (int i = 0; i < 4; i++)
		{
			toLoad = this->PicFile + "Red/idle" + to_string(i) + ".png";
			loadimage(Idle_Red + i, toLoad.c_str());
		}

		//白色待机图片
		for (int i = 0; i < 4; i++)
		{
			toLoad = this->PicFile + "White/idle" + to_string(i) + ".png";
			loadimage(Idle_White + i, toLoad.c_str());
		}

		//红色攀爬图片
		for (int i = 0; i < 6; i++)
		{
			toLoad = this->PicFile + "Red/climb_" + to_string(i) + ".png";
			loadimage(Climb_Red + i, toLoad.c_str());
		}

		//白色攀爬图片
		for (int i = 0; i < 6; i++)
		{
			toLoad = this->PicFile + "White/climb_" + to_string(i) + ".png";
			loadimage(Climb_White + i, toLoad.c_str());
		}

		//红色蹲下图片
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "Red/squat" + to_string(i) + ".png";
			loadimage(Squat_Red + i, toLoad.c_str());
		}

		//白色蹲下图片
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "White/squat" + to_string(i) + ".png";
			loadimage(Squat_White + i, toLoad.c_str());
		}

		//红色跳跃图片
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "Red/jump" + to_string(i) + ".png";
			loadimage(Jump_Red + i, toLoad.c_str());
		}

		//白色跳跃图片
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "White/jump" + to_string(i) + ".png";
			loadimage(Jump_White + i, toLoad.c_str());
		}

		//红色降落图片
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "Red/down" + to_string(i) + ".png";
			loadimage(Down_Red + i, toLoad.c_str());
		}

		//白色降落图片
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "White/down" + to_string(i) + ".png";
			loadimage(Down_White + i, toLoad.c_str());
		}

		//红白转换图片
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "White/change" + to_string(i) + ".png";
			loadimage(Change_RtoW + i, toLoad.c_str());
		}

		//攻击图片
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "White/attack" + to_string(i) + ".png";
			loadimage(Attack + i, toLoad.c_str());
		}

		//胜利图片
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "Red/victory" + to_string(i) + ".png";
			loadimage(Victory + i, toLoad.c_str());
		}

		//呼气图片
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "Red/gas" + to_string(i) + ".png";
			loadimage(Gas + i, toLoad.c_str());
		}
	}
	
}

//渲染角色
void Mario::Render(double x, double y,const char* file)
{
	x = (int)x; y = (int)y;

	//静止状态
	if (MarioStatus == 0)
	{
		if (MarioMode == 0)
		{
			putimagePNG(NULL, x, y, &Idle_Red[this->direction * 2]);
		}
		else if (MarioMode == 1)
		{
			putimagePNG(NULL, x, y, &Idle_White[this->direction * 2]);
		}
	}

	//待机状态
	else if (MarioStatus == 1)
	{
		if (MarioMode == 0)
		{
			putimagePNG(NULL, x, y, &Idle_Red[this->direction * 2 + idleIndex %2]);
			if (idleIndex % 2)
			{
				if (this->direction == 1)
					putimagePNG(NULL, x + 45, y + 30, &Gas[this->direction]);
				else
					putimagePNG(NULL, x - 10, y + 30, &Gas[this->direction]);
			}
		}
		else if (MarioMode == 1)
		{
			putimagePNG(NULL, x, y, &Idle_White[this->direction * 2 + idleIndex %2]);
			if (idleIndex % 2)
			{
				if (this->direction == 1)
					putimagePNG(NULL, x + 45, y + 30, &Gas[this->direction]);
				else
					putimagePNG(NULL, x - 10, y + 30, &Gas[this->direction]);
			}
		}
	}

	//跑步状态
	else if (MarioStatus == 2)
	{
		if (MarioMode == 0)
		{
			putimagePNG(NULL, x, y, &Run_Red[this->direction * 4 + marioIndex % 4]);
		}
		else if (MarioMode == 1)
		{
			putimagePNG(NULL, x, y, &Run_White[this->direction * 4 + marioIndex % 4]);
		}
	}

	//跳跃状态
	else if (MarioStatus == 3)
	{
		if (MarioMode == 0)
		{
			putimagePNG(NULL, x, y, &Jump_Red[this->direction]);
		}
		else if (MarioMode == 1)
		{
			putimagePNG(NULL, x, y, &Jump_White[this->direction]);
		}
	}

	//降落状态
	else if (MarioStatus == 4)
	{
		if (MarioMode == 0)
		{
			putimagePNG(NULL, x, y, &Jump_Red[this->direction]);
		}
		else if (MarioMode == 1)
		{
			putimagePNG(NULL, x, y, &Jump_White[this->direction]);
		}
	}

	//攀爬状态
	else if (MarioStatus == 5)
	{
		if (MarioMode == 0)
		{
			putimagePNG(NULL, x, y, &Climb_Red[this->direction * 3 + marioIndex % 3]);
		}
		else if (MarioMode == 1)
		{
			putimagePNG(NULL, x, y, &Climb_White[this->direction * 3 + marioIndex % 3]);
		}
	}

	//攻击状态
	else if (MarioStatus == 6)
	{
		putimagePNG(NULL, x, y, &Climb_White[this->direction]);
	}

	//下蹲状态
	else if (MarioStatus == 7)
	{
		if (MarioMode == 0)
		{
			putimagePNG(NULL, x, y, &Squat_Red[this->direction * 2]);
		}
		else if (MarioMode == 1)
		{
			putimagePNG(NULL, x, y, &Squat_White[this->direction * 2]);
		}
	}
	
}

//更新角色
void Mario::UpdateStatus(int type, int damage)
{
	//受到伤害
	this->m_Health -= damage;
	if (this->m_Health <= 0)
	{
		this->Kill(this->direction);
		return;
	}

	//静止
	if (type == 0)
	{
		MarioStatus = 0;
		this->m_Fx = 0;
		this->m_Fy = 0;
		this->m_Vx = 0;
		this->m_Vy = 0;
	}

	//待机
	else if (type == 1)
	{
		//之前在下落或者攀爬
		if (MarioStatus == 4 || MarioStatus == 5)
		{
			MarioStatus = 1;
			this->m_Fy = -Gravity;
			this->m_Vy = 0;
		}
		//之前在奔跑
		else if (MarioStatus == 2)
		{
			MarioStatus = 1;
			this->m_Fx = 0;
			this->m_Vx = 0;
		}
		else
		{
			MarioStatus = 1;
		}
	}

	//跑步
	else if (type == 2)
	{
		//只有待机状态可以开始奔跑
		if (MarioStatus == 1)
		{
			//无敌受力更大
			if (this->isInvincible)
			{
				this->m_Fx = 15;
			}
			else
			{
				this->m_Fx = 10;
			}
			MarioStatus = 2;
		}
	}

	//跳跃
	else if (type == 3)
	{
		if (MarioStatus != 0 && MarioStatus != 4 && MarioStatus != 5 && MarioStatus != 8 && MarioStatus != 3)
		{
			//之前在下蹲
			if (MarioStatus == 7)
			{
				this->m_Fy = -15;
			}
			else
			{
				this->m_Fy = -30;
			}
			if (this->isInvincible)
			{
				this->m_Fy -= 5;
			}
			MarioStatus = 3;
		}
	}

	//降落
	else if (type == 4)
	{
		if (MarioStatus != 0 && MarioStatus != 4 && MarioStatus != 8)
		{
			this->m_Fy = -Gravity;
			this->m_Vy = 30;//匀速下落
			MarioStatus = 4;
		}
	}

	//攀爬
	else if (type == 5)
	{
		MarioStatus = 5;
	}

	//攻击
	else if (type == 6)
	{
		MarioStatus = 6;
	}

	//下蹲
	else if (type == 7)
	{
		if (MarioStatus != 7 && MarioStatus != 4 && MarioStatus != 3 && MarioStatus != 0 && MarioStatus != 5)
		{
			this->max_Px = 50;
			this->max_Py = 500;
			MarioStatus = 7;
		}
	}
}

//检测是否往下掉
bool Mario::CheckFall()
{
	if (!this->isFly)
	{
		if (MarioStatus == 2 || MarioStatus == 1 || MarioStatus == 7)
		{
			this->UpdateStatus(4);
			return true;
		}
	}
	return false;
}

//报告碰撞
bool Mario::ReportCollide(int direction, Creature* target, int layer)
{
	//图块层
	if (layer == 1)
	{
		//跳跃
		if (direction == TOP && MarioStatus == 3)
		{
			if (!this->jumpSound) {
				this->jumpSound = true;
				mciSendString("play Audio/SuperMario/small_jump.mp3", 0, 0, 0);
			}
			//状态改为下落
			this->UpdateStatus(4);
			return true;
		}

		//下落至地面
		else if (direction == BOTTOM && MarioStatus == 4)
		{
			//状态改为待机
			UpdateStatus(1);
			return true;
		}
	}

	//若遇到道具
	else if (layer == 2)
	{
		//碰到问号砖
		if (target->m_Name == "QuestionBrick")
		{
			target->Kill();
			return true;
		}
		//碰到蘑菇
		else if (target->m_Name == "MushRoom")
		{
			this->MarioChange(1);
			target->Kill();
			return true;
		}
		//碰到花朵
		else if (target->m_Name == "Flower")
		{
			this->m_Health = 100;
			return true;
		}
	}

	//生物层
	else if (layer == 3)
	{
		//若处于无敌状态
		if (this->isInvincible)
		{
			target->Kill((direction+2)&3);
			target->Kill();
			return true;
		}
		//若跳在怪物头上
		if (direction == BOTTOM)
		{
			m_Vy = 20;
			target->m_Health -= 50;
			this->m_Y = target->m_Y;
			mciSendString("play Audio/SuperMario/stomp.mp3", 0, 0, 0);
			return true;
		}
		else
		{
			this->m_Health -= 25;
			mciSendString("play Audio/SuperMario/stomp.mp3", 0, 0, 0);
			return true;
		}
	}
}

//起立
bool Mario::MarioStand()
{
	return true;
}

//下蹲
bool Mario::MarioSquat()
{
	return true;
}

//跳跃
bool Mario::MarioJump()
{
	return true;
}

//被击杀
void Mario::Kill(int direction)
{

}

//变身
bool Mario::MarioChange(int type)
{
	return true;
}

//析构函数
Mario::~Mario()
{

}