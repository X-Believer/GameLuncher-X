#include "Mario.h"
namespace
{
	IMAGE Run_Red[8]; IMAGE* Idle_Red; IMAGE* Jump_Red; IMAGE Attack; IMAGE* Victory;
	IMAGE* Run_White; IMAGE* Idle_White; IMAGE* Jump_White;
	IMAGE* Run_Small; IMAGE* Idle_Small; IMAGE* Jump_Small;
	IMAGE* Change_RtoS; IMAGE* Change_RtoW; IMAGE Change_WtoS;

	string toLoad;
}

//���캯��
Mario::Mario()
{
	this->m_Health = 100;
	this->isShow = false;
	this->PicFile = "Graph/SuperMario/";
	this->m_Hei = 105;
	this->m_Wid = 70;
	this->m_Fx = 0;
	this->m_Fy = 0;
	this->m_Vx = 0;
	this->m_Vy = 0;

	//��ɫ�ܲ�ͼƬ
	for (int i = 0; i < 8; i++)
	{
		toLoad = this->PicFile + "Big/run" + to_string(i) + ".png";
		loadimage(Run_Red + i, toLoad.c_str());
	}

	//��ɫ�ܲ�ͼƬ
	for (int i = 0; i < 8; i++)
	{
		toLoad = this->PicFile + "Big/run" + to_string(i) + ".png";
		loadimage(Run_Red + i, toLoad.c_str());
	}
}

//��Ⱦ��ɫ
void Mario::Render(double x, double y, const char* file)
{
	LoadImage()
	putimagePNG()
}

//��������
Mario::~Mario()
{

}