#include "Creature.h"

//生物图层
vector<Creature>CreatureVec;

//构造函数
Creature::Creature()
{

}

//析构函数
Creature::~Creature()
{

}

//与生物碰撞
bool Creature::CreatureCollide(double x, double y, Creature& creature)
{
	if (fabs(x - creature.m_X) < (this->m_Wid + creature.m_Wid) / 2 && fabs(y - creature.m_Y) < (this->m_Hei + creature.m_Hei) / 2)
	{
		return true;
	}
	return false;
}

//检测上方碰撞
pair<double, bool> Creature::UpCollide(double lastx, double lasty)
{
	return make_pair(0,true);
}

//检测下方碰撞
pair<double, bool> Creature::DownCollide(double lastx, double lasty)
{
	//已死亡及正在跳跃的生物不检测
	if (this->CreatureLayer == 0 || this->m_Vy < 0) return(make_pair(lasty, false));
	return make_pair(0, true);
}

//检测左右碰撞
pair<double, bool> Creature::SideCollide(double lastx, double lasty)
{
	return make_pair(0, true);
}

//设置位置
void Creature::SetPos(double x, double y, double width, double height)
{

}

//速度计算
void Creature::SpeedCal()
{

}

//渲染角色
void Creature::Render(double x, double y, const char* file)
{

}

//更新角色
void Creature::UpdateStatus(int type, int damage)
{

}

//报告碰撞(layer 1->图块层 2->对象层 3->生物层)
bool Creature::ReportCollide(int direction, Creature* target, int layer)
{
	return false;
}

//被击杀
void Creature::Kill(int direction)
{

}

//检测碰撞
void Creature::CheckCollide(double lastx, double lasty)
{

}