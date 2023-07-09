#include "GreenTortoise.h"

//构造函数
GreenTortoise::GreenTortoise(int row, int col)
{
	this->m_Name = "ChestNut";
	this->m_Health = 100;
	this->PicFile = "Graph/SuperMario/Tortoise/";
	this->m_Hei = 37;
	this->m_Wid = 53;
	this->m_Mass = 1;
	this->m_X = col * TileWid;
	this->m_Y = row * TileHei + 5;//补足一格高
	this->m_Fx = 0;
	this->m_Fy = 0;
	this->m_Vx = 0;
	this->m_Vy = 0;
	this->max_Px = 100;
	this->max_Py = 1000;
	this->direction = 0;
}

//析构函数
GreenTortoise::~GreenTortoise()
{

}