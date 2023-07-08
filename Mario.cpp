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

//���캯��
Mario::Mario()
{
	this->m_Health = 100;
	this->isShow = true;
	this->PicFile = "Graph/SuperMario/";
	this->m_Hei = 76;
	this->m_Wid = 50;
	this->m_Mass = 1;
	this->m_X = 8.0 * TileWid;
	this->m_Y = 545 - 2.0 * 42 - this->m_Hei;
	this->m_Fx = 0;
	this->m_Fy = 0;
	this->m_Vx = 0;
	this->m_Vy = 0;
	this->max_Px = 100;
	this->max_Py = 1000;
	this->isInvincible = true;

	this->out_of_range = false;
	this->direction = 1;

	//����ͼƬ
	if (1)
	{
		//��ɫ�ܲ�ͼƬ
		for (int i = 0; i < 8; i++)
		{
			toLoad = this->PicFile + "Red/run_" + to_string(i) + ".png";
			loadimage(Run_Red + i, toLoad.c_str());
		}

		//��ɫ�ܲ�ͼƬ
		for (int i = 0; i < 8; i++)
		{
			toLoad = this->PicFile + "White/run_" + to_string(i) + ".png";
			loadimage(Run_White + i, toLoad.c_str());
		}

		//��ɫ����ͼƬ
		for (int i = 0; i < 4; i++)
		{
			toLoad = this->PicFile + "Red/idle" + to_string(i) + ".png";
			loadimage(Idle_Red + i, toLoad.c_str());
		}

		//��ɫ����ͼƬ
		for (int i = 0; i < 4; i++)
		{
			toLoad = this->PicFile + "White/idle" + to_string(i) + ".png";
			loadimage(Idle_White + i, toLoad.c_str());
		}

		//��ɫ����ͼƬ
		for (int i = 0; i < 6; i++)
		{
			toLoad = this->PicFile + "Red/climb_" + to_string(i) + ".png";
			loadimage(Climb_Red + i, toLoad.c_str());
		}

		//��ɫ����ͼƬ
		for (int i = 0; i < 6; i++)
		{
			toLoad = this->PicFile + "White/climb_" + to_string(i) + ".png";
			loadimage(Climb_White + i, toLoad.c_str());
		}

		//��ɫ����ͼƬ
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "Red/squat" + to_string(i) + ".png";
			loadimage(Squat_Red + i, toLoad.c_str());
		}

		//��ɫ����ͼƬ
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "White/squat" + to_string(i) + ".png";
			loadimage(Squat_White + i, toLoad.c_str());
		}

		//��ɫ��ԾͼƬ
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "Red/jump" + to_string(i) + ".png";
			loadimage(Jump_Red + i, toLoad.c_str());
		}

		//��ɫ��ԾͼƬ
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "White/jump" + to_string(i) + ".png";
			loadimage(Jump_White + i, toLoad.c_str());
		}

		//��ɫ����ͼƬ
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "Red/down" + to_string(i) + ".png";
			loadimage(Down_Red + i, toLoad.c_str());
		}

		//��ɫ����ͼƬ
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "White/down" + to_string(i) + ".png";
			loadimage(Down_White + i, toLoad.c_str());
		}

		//���ת��ͼƬ
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "White/change" + to_string(i) + ".png";
			loadimage(Change_RtoW + i, toLoad.c_str());
		}

		//����ͼƬ
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "White/attack" + to_string(i) + ".png";
			loadimage(Attack + i, toLoad.c_str());
		}

		//ʤ��ͼƬ
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "Red/victory" + to_string(i) + ".png";
			loadimage(Victory + i, toLoad.c_str());
		}

		//����ͼƬ
		for (int i = 0; i < 2; i++)
		{
			toLoad = this->PicFile + "Red/gas" + to_string(i) + ".png";
			loadimage(Gas + i, toLoad.c_str());
		}
	}
	
}

//��Ⱦ��ɫ
void Mario::Render(double x, double y,const char* file)
{
	x = (int)x; y = (int)y;

	//��ֹ״̬
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

	//����״̬
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

	//�ܲ�״̬
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

	//��Ծ״̬
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

	//����״̬
	else if (MarioStatus == 4)
	{
		if (MarioMode == 0)
		{
			putimagePNG(NULL, x, y, &Down_Red[this->direction]);
		}
		else if (MarioMode == 1)
		{
			putimagePNG(NULL, x, y, &Down_White[this->direction]);
		}
	}

	//����״̬
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

	//����״̬
	else if (MarioStatus == 6)
	{
		putimagePNG(NULL, x, y, &Climb_White[this->direction]);
	}

	//�¶�״̬
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

//���½�ɫ
void Mario::UpdateStatus(int type, int damage)
{
	//�ܵ��˺�
	this->m_Health -= damage;
	if (this->m_Health <= 0)
	{
		this->Kill(this->direction);
		return;
	}

	//��ֹ
	if (type == 0)
	{
		MarioStatus = 0;
		this->m_Fx = 0;
		this->m_Fy = 0;
		this->m_Vx = 0;
		this->m_Vy = 0;
	}

	//����
	else if (type == 1)
	{
		//֮ǰ�������������
		if (MarioStatus == 4 || MarioStatus == 5)
		{
			MarioStatus = 1;
			this->m_Fy = Gravity;
		}

		//֮ǰ�ڱ���
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

	//�ܲ�
	else if (type == 2)
	{
		MarioStatus = 2;
		//�޵���������
		if (this->isInvincible)
		{
			this->m_Fx = 15;
		}
		else
		{
			this->m_Fx = 10;
		}
	}

	//��Ծ
	else if (type == 3)
	{
		MarioStatus = 3;
		//֮ǰ�ڱ���
		if (MarioStatus == 2)
		{
			this->m_Fy = 20;
			this->m_Fx = 0;
		}
		else
		{
			this->m_Fy = 20;
		}

		if (this->isInvincible)
		{
			this->m_Fy += 5;
		}
	}

	//����
	else if (type == 4)
	{
		MarioStatus = 4;
		this->m_Fy = 0;
	}

	//����
	else if (type == 5)
	{
		MarioStatus = 5;
	}

	//����
	else if (type == 6)
	{
		MarioStatus = 6;
	}

	//�¶�
	else if (type == 7)
	{
		MarioStatus = 7;
		this->max_Px = 75;
		this->max_Py = 500;
		this->m_Vx = 5;
	}
}

//�����ײ
void Mario::CheckCollide(double lastx, double lasty)
{
	//����Ϸ�
	if (this->UpCollide(this->m_X, this->m_Y).second)
	{
		this->ReportCollide(TOP, NULL, 1);
	}
	//����·�
	if (this->DownCollide(this->m_X, this->m_Y).second)
	{
		this->ReportCollide(BOTTOM, NULL, 1);
	}
	//�������
	if (this->SideCollide(this->m_X, this->m_Y).second)
	{
		this->ReportCollide(LEFT, NULL, 1);
	}
	//�������
	if (this->CreatureCollide(this->m_X, this->m_Y,*this))
	{
		
	}
}

//������ײ
bool Mario::ReportCollide(int direction, Creature* target, int layer)
{
	//ͼ���
	if (layer == 1)
	{
		//��Ծ
		if (direction==TOP && target->CreatureLayer == 1 && MarioStatus == 3)
		{
			if (!this->jumpSound) {
				this->jumpSound = true;
				mciSendString("play Audio/SuperMario/small_jump.mp3", 0, 0, 0);
			}
			//״̬��Ϊ����
			UpdateStatus(4);
			return true;
		}

		//����������
		else if (direction == BOTTOM && target->CreatureLayer == 1 && MarioStatus == 4)
		{
			//״̬��Ϊ����
			UpdateStatus(1);
			return true;
		}
	}

	//����������
	else if (layer == 2)
	{
		//�����ʺ�ש
		if (target->m_Name == "QuestionBrick")
		{
			target->Kill();
			return true;
		}
		//����Ģ��
		else if (target->m_Name == "MushRoom")
		{
			this->MarioChange(1);
			target->Kill();
			return true;
		}
		//��������
		else if (target->m_Name == "Flower")
		{
			this->m_Health = 100;
			return true;
		}
	}

	//�����
	else if (layer == 3)
	{
		//�������޵�״̬
		if (this->isInvincible)
		{
			target->Kill((direction+2)&3);
			target->Kill();
			return true;
		}
		//�����ڹ���ͷ��
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

//�ٶȼ���
void Mario::SpeedCal()
{
	if (MarioStatus == 0)return;
	//��������ʼ�������
	double realFx = this->m_Fx, realFy = this->m_Fy;
	double Ax, Ay = realFy / this->m_Mass + Gravity;
	if (realFx * this->m_Vx > this->max_Px)
	{
		realFx = this->max_Px / this->m_Vx;
	}
	//�������ٶ�ʱ������Ħ����
	if (fabs(this->m_Vx) > 1)
	{
		Ax = (this->m_Vx > 0 ? realFx - Friction : realFx + Friction) / this->m_Mass;
	}
	else
	{
		if (fabs(realFx) > Friction)
		{
			Ax = realFx / this->m_Mass;
		}
		else
		{
			Ax = 0;
			this->m_Vx = 0;
		}
	}
	this->m_Vx += LastDelay / 1000 * Ax; this->m_Vy += LastDelay / 1000 *Ay;
	this->m_Vx = min(this->m_Vx, this->max_Px);
	double preX = this->m_X, preY = this->m_Y;
	this->m_X = preX + LastDelay / 1000 * this->m_Vx;
	//�����ж�
	if (!this->out_of_range)
	{
		if (this->m_X < this->m_Wid / 2)this->m_X = this->m_Wid / 2;
		if(this->m_X>)
	}
}

//����
bool Mario::MarioStand()
{
	return true;
}

//�¶�
bool Mario::MarioSquat()
{
	return true;
}

//��Ծ
bool Mario::MarioJump()
{
	return true;
}

//����ɱ
void Mario::Kill(int direction)
{

}

//����
bool Mario::MarioChange(int type)
{
	return true;
}

//��������
Mario::~Mario()
{

}