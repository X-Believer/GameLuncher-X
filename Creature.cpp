#include "Creature.h"

//��������ײ
bool Creature::CreatureCollide(double x, double y, Creature& creature)
{
	return true;
}

//����Ϸ���ײ
pair<double, bool> Creature::UpCollide(double lastx, double lasty)
{
	return make_pair(0,true);
}

//����·���ײ
pair<double, bool> Creature::DownCollide(double lastx, double lasty)
{
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

//�����ײ
void Creature::CheckCollide(double lastx, double lasty)
{

}