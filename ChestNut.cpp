#include "ChestNut.h"

//���캯��
ChestNut::ChestNut(int row,int col)
{
	this->m_Name = "ChestNut";
	this->m_Health = 50;
	this->PicFile = "Graph/SuperMario/ChestNut/";
	this->m_Hei = 39;
	this->m_Wid = 36;
	this->m_Mass = 1;
	this->m_X = col * TileWid;
	this->m_Y = row * TileHei + 3;//����һ���
	this->m_Fx = 0;
	this->m_Fy = 0;
	this->m_Vx = 0;
	this->m_Vy = 0;
	this->max_Px = 100;
	this->max_Py = 1000;
	this->direction = 0;
}

//��������
ChestNut::~ChestNut()
{

}