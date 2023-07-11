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
	//已死亡及正在下落的生物不检测
	if (this->CreatureLayer == 0 || this->m_Vy > 0) return(make_pair(lasty, false));
	int x = int(lastx / TileWid), y = int((lasty + this->m_Hei) / TileHei);//x,y是对象左下角所在格子
	int hei = int(this->m_Hei) % TileHei == 0 ? int(this->m_Hei / TileHei) : int(this->m_Hei / TileHei) + 1;
	y -= hei;
	//出界判断
	if (lasty < 10)return make_pair(10, true);
	//如果在两格中间
	if (lastx - TileWid * x + this->m_Wid > TileWid)
	{
		if (CollideVec[y][x + 1].first == 1)
		{
			return make_pair(TileHei * (y+1), true);
		}
	}
	if (CollideVec[y][x].first == 1)
	{
		return make_pair(TileHei * (y+1), true);
	}
	return make_pair(lasty,false);
}

//检测下方碰撞
pair<double, bool> Creature::DownCollide(double lastx, double lasty)
{
	//已死亡及正在跳跃的生物不检测
	if (this->CreatureLayer == 0 || this->m_Vy < 0) return(make_pair(lasty, false));
	int x = int(lastx / TileWid), y = int((lasty+this->m_Hei) / TileHei);//x,y是对象左下角所在格子
	//如果在两格中间
	if (lastx - TileWid * x + this->m_Wid > TileWid)
	{
		if (CollideVec[y][x + 1].first == 1)
		{
			return make_pair(TileHei * y - this->m_Hei, true);
		}
	}
	if (CollideVec[y][x].first == 1)
	{
		return make_pair(TileHei * y - this->m_Hei, true);
	}
	return make_pair(lasty, false);
}

//检测左右碰撞
pair<double, bool> Creature::SideCollide(double lastx, double lasty)
{
	//已死亡及正在跳跃的生物不检测
	if (this->CreatureLayer == 0) return(make_pair(lastx, false));
	int x = int(lastx / TileWid), y = int((lasty + this->m_Hei) / TileHei);//x,y是对象左下角所在格子
	if (int(lasty + this->m_Hei) % TileHei != 0)y++;
	int x1 = int((lastx+this->m_Wid) / TileWid);
	int testCnt = this->m_Hei / TileHei; if (int(this->m_Hei) % TileHei != 0)testCnt++;
	//检测左边
	for (int i = 0; i < testCnt; i++)
	{
		if (CollideVec[y - i - 1][x].first == 1)
		{
			return make_pair(TileWid * (x+1) + 0.1, true);
		}
	}
	//检测右边
	for (int i = 0; i < testCnt; i++)
	{
		if (CollideVec[y - i - 1][x1].first == 1)
		{
			return make_pair(TileWid * x1 - 0.1 - this->m_Wid, true);
		}
	}
	return make_pair(lastx, false);
}

//设置位置
void Creature::SetPos(double x, double y, double width, double height)
{

}

//速度计算
void Creature::SpeedCal()
{
	if (MarioStatus == 0)return;
	//根据最大功率计算受力
	double realFx = this->m_Fx, realFy = this->m_Fy;
	double Ax, Ay = (realFy + Gravity) / this->m_Mass;
	if (fabs(realFy) < EPS)Ay = 0;
	if (fabs(realFx * this->m_Vx) > this->max_Px)
	{
		realFx = this->max_Px / this->m_Vx;
		this->m_Fx = realFx;
	}
	if (fabs(realFy * this->m_Vy) > this->max_Py)
	{
		//Y方向达到最大功率不再上升
		realFy = 0;
		this->m_Fy = realFy;
		this->ReportCollide(TOP, NULL, 1);
	}
	//生物有速度时，考虑摩擦力
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
	this->m_Vx += LastDelay / 1000 * Ax; 
	this->m_Vy += LastDelay / 100 * Ay;
	this->m_Vx = min(this->m_Vx, this->max_Px);
	double preX = this->m_X, preY = this->m_Y;
	//this->m_X = preX + LastDelay / 1000 * this->m_Vx;
	this->m_Y = preY + LastDelay / 100 * this->m_Vy;
	if(this->m_Vy!=0)
	//出界判断
	if (!this->out_of_range)
	{
		if (this->m_X < this->m_Wid / 2)this->m_X = this->m_Wid / 2;
		if (this->m_X > MapWid * TileWid - this->m_Wid / 2)this->m_X = MapWid * TileWid - this->m_Wid / 2;
	}
	//碰撞检测
	preX = this->m_X; preY = this->m_Y;
	pair<double, bool>res = this->DownCollide(preX, preY);
	if (fabs(preY - this->m_Y) < EPS)this->m_Y = res.first;
	else this->m_Y = min(this->m_Y, res.first);
	//在地上
	if (res.second)
	{
		this->isOnFloor = true;
		this->ReportCollide(BOTTOM, NULL, 1);
	}
	//在天上
	else
	{
		this->isOnFloor = false;
		preY = this->m_Y;
		res = UpCollide(preX, preY);
		if (fabs(preY - this->m_Y) < EPS)this->m_Y = res.first;
		else this->m_Y = max(this->m_Y, res.first);
		if (res.second)
		{
			this->ReportCollide(TOP, NULL, 1);
		}
	}
	//左右碰撞
	preX = this->m_X; preY = this->m_Y;
	res = SideCollide(preX, preY);
	if (fabs(preX - this->m_X) < EPS)this->m_X = res.first;
	else this->m_X = this->m_Vx > 0.1 || (this->m_Fx > 0) ? min(this->m_X, res.first) : max(this->m_X, res.first);
	if (res.second)this->m_Vx = 0;
	if(!this->isOnFloor)this->CheckFall();
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

//检测是否往下掉
bool Creature::CheckFall()
{
	if (this->isFly)
		return false;
}