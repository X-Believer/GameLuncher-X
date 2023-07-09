#include "QuestionBlock.h"

//���캯��
QuestionBlock::QuestionBlock(int row, int col)
{
	this->m_Name = "QuestionBlock";
	this->m_Health = 50;
	this->PicFile = "Graph/SuperMario/Brick/";
	this->m_Hei = 40;
	this->m_Wid = 40;
	this->m_Mass = 1;
	this->m_X = col * TileWid;
	this->m_Y = row * TileHei + 2;//����һ���
	this->m_Fx = 0;
	this->m_Fy = 0;
	this->m_Vx = 0;
	this->m_Vy = 0;
	this->max_Px = 0;
	this->max_Py = 0;
	this->direction = 0;
}

//��������
QuestionBlock::~QuestionBlock()
{

}