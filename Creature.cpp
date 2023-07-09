#include "Creature.h"

//����ͼ��
vector<Creature>CreatureVec;

//���캯��
Creature::Creature()
{

}

//��������
Creature::~Creature()
{

}

//��������ײ
bool Creature::CreatureCollide(double x, double y, Creature& creature)
{
	if (fabs(x - creature.m_X) < (this->m_Wid + creature.m_Wid) / 2 && fabs(y - creature.m_Y) < (this->m_Hei + creature.m_Hei) / 2)
	{
		return true;
	}
	return false;
}

//����Ϸ���ײ
pair<double, bool> Creature::UpCollide(double lastx, double lasty)
{
	return make_pair(lasty,false);
}

//����·���ײ
pair<double, bool> Creature::DownCollide(double lastx, double lasty)
{
	//��������������Ծ�����ﲻ���
	if (this->CreatureLayer == 0 || this->m_Vy < 0) return(make_pair(lasty, false));
	int x = int(lastx / 42), y = int((lasty+this->m_Hei) / 42);//x,y�Ƕ������½����ڸ���
	if (int(lasty + this->m_Hei) % 42 != 0)y++;
	if (fabs(42 * y - this->m_Y - this->m_Hei) < 2)
	{
		//����������м�
		if (lastx - 42 * x + this->m_Wid > 42)
		{
			if (CollideVec[y][x + 1].first == 1)
			{
				return make_pair(42 * y-this->m_Hei, true);
			}
		}
		if (CollideVec[y][x].first == 1)
		{
			return make_pair(42 * y-this->m_Hei, true);
		}
	}
	return make_pair(lasty, false);
}

//���������ײ
pair<double, bool> Creature::SideCollide(double lastx, double lasty)
{
	return make_pair(lastx, false);
}

//����λ��
void Creature::SetPos(double x, double y, double width, double height)
{

}

//�ٶȼ���
void Creature::SpeedCal()
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
	this->m_Vx += LastDelay / 1000 * Ax; this->m_Vy += LastDelay / 1000 * Ay;
	this->m_Vx = min(this->m_Vx, this->max_Px);
	double preX = this->m_X, preY = this->m_Y;
	this->m_X = preX + LastDelay / 1000 * this->m_Vx;
	//�����ж�
	if (!this->out_of_range)
	{
		if (this->m_X < this->m_Wid / 2)this->m_X = this->m_Wid / 2;
		if (this->m_X > MapWid*42 - this->m_Wid / 2)this->m_X = MapWid*42 - this->m_Wid / 2;
	}
	//��ײ���
	preX = this->m_X; preY = this->m_Y;
	pair<double, bool>res = this->DownCollide(preX, preY);
	if (fabs(preY - this->m_Y) < EPS)this->m_Y = res.first;
	else this->m_Y = min(this->m_Y, res.first);
	//�ڵ���
	if (res.second)
	{
		this->m_Vy = 0;
		this->isOnFloor = true;
	}
	//������
	else
	{
		this->isOnFloor = false;
		preY = this->m_Y;
		res = UpCollide(preX, preY);
		if (fabs(preY - this->m_Y) < EPS)this->m_Y = res.first;
		else this->m_Y = max(this->m_Y, res.first);
	}
	//������ײ
	preX = this->m_X;
	res = SideCollide(preX, preY);
	if (fabs(preX - this->m_X) < EPS)this->m_X = res.first;
	else this->m_X = this->m_Vx > 0.1 || (this->m_Fx > 0) ? min(this->m_X, res.first) : max(this->m_X, res.first);
	if (res.second)this->m_Vx = 0;
}

//��Ⱦ��ɫ
void Creature::Render(double x, double y, const char* file)
{

}

//���½�ɫ
void Creature::UpdateStatus(int type, int damage)
{

}

//������ײ(layer 1->ͼ��� 2->����� 3->�����)
bool Creature::ReportCollide(int direction, Creature* target, int layer)
{
	return false;
}

//����ɱ
void Creature::Kill(int direction)
{

}

//�����ײ
void Creature::CheckCollide(double lastx, double lasty)
{

}