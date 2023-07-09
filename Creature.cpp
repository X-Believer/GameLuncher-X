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
	return make_pair(0,true);
}

//����·���ײ
pair<double, bool> Creature::DownCollide(double lastx, double lasty)
{
	//��������������Ծ�����ﲻ���
	if (this->CreatureLayer == 0 || this->m_Vy < 0) return(make_pair(lasty, false));
	return make_pair(0, true);
}

//���������ײ
pair<double, bool> Creature::SideCollide(double lastx, double lasty)
{
	return make_pair(0, true);
}

//����λ��
void Creature::SetPos(double x, double y, double width, double height)
{

}

//�ٶȼ���
void Creature::SpeedCal()
{

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