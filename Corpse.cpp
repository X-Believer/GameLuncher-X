#include "Corpse.h"

//���캯��
Corpse::Corpse(int row, int col)
{
	this->m_Name = "Corpse";
	this->m_Health = 50;
	this->PicFile = "Graph/SuperMario/Plant/";
	this->m_Hei = 56;
	this->m_Wid = 49;
	this->m_Mass = 1;
	this->m_X = col * TileWid;
	this->m_Y = row * TileHei;//����һ���
	this->m_Fx = 0;
	this->m_Fy = 0;
	this->m_Vx = 0;
	this->m_Vy = 0;
	this->max_Px = 0;
	this->max_Py = 0;
	this->direction = 0;
}

//��������
Corpse::~Corpse()
{

}