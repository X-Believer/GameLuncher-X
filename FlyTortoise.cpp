#include "FlyTortoise.h"

//构造函数
FlyTortoise::FlyTortoise(int row, int col)
{
	this->m_Name = "FlyTortoise";
	this->m_Health = 100;
	this->PicFile = "Graph/SuperMario/Tortoise/";
	this->m_Hei = 39;
	this->m_Wid = 55;
	this->m_Mass = 1;
	this->m_X = col * TileWid;
	this->m_Y = row * TileHei + 3;//补足一格高
	this->m_Fx = 0;
	this->m_Fy = 0;
	this->m_Vx = 0;
	this->m_Vy = 0;
	this->max_Px = 100;
	this->max_Py = 1000;
	this->direction = 0;
}

//析构函数
FlyTortoise::~FlyTortoise()
{

}