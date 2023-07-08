#pragma once
#include"MarioGlobal.h"
using namespace std;

class Creature
{
protected:
	
	//��������ײ
	bool CreatureCollide(double x, double y, Creature& creature);

	//����Ϸ���ײ
	pair<double, bool> UpCollide(double lastx, double lasty);

	//����·���ײ
	pair<double, bool> DownCollide(double lastx, double lasty);

	//���������ײ
	pair<double, bool> SideCollide(double lastx, double lasty);

public:

	//����λ��
	void SetPos(double x, double y, double width, double height); 

	//��Ⱦ��ɫ
	virtual void Render(double x, double y, const char* file = NULL) = 0;

	//���½�ɫ
	virtual void UpdateStatus(int type = 0,int damage=0) = 0;

	//�����ײ
	void CheckCollide(double lastx, double lasty);

	//������ײ(layer 1->ͼ��� 2->����� 3->�����)
	virtual bool ReportCollide(int direction, Creature* target = NULL, int layer=1)=0;

	//����ɱ
	virtual void Kill(int direction = 0)=0;

	//�ٶȼ���
	virtual void SpeedCal() = 0;

	int direction = 0; // ������0��, 1��
	int CreatureLayer = 3;
	int m_Health;//����
	int m_Mass;//����
	double m_X, m_Y;//��ǰλ��
	double m_Wid, m_Hei;//��ɫ���
	string m_Name = "None";

protected:

	double m_Vx, m_Vy;//��ɫ�ٶ�
	double m_Fx, m_Fy;//��ɫ����
	double max_Px, max_Py;//�����
	string PicFile;

	bool out_of_range = true; //��������ͼ��Χ
	bool isShow;//�Ƿ���ʾ
	bool isInvincible;//�Ƿ��޵�
};

