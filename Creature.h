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
	//���캯��
	Creature();

	//��������
	~Creature();

	//����λ��
	void SetPos(double x, double y, double width, double height); 

	//��Ⱦ��ɫ
	virtual void Render(double x, double y, const char* file = NULL);

	//���½�ɫ
	virtual void UpdateStatus(int type = 0, int damage = 0);

	//����Ƿ����µ�
	virtual  bool CheckFall();

	//������ײ(layer 1->ͼ��� 2->����� 3->�����)
	virtual bool ReportCollide(int direction, Creature* target = NULL, int layer = 1);

	//����ɱ
	virtual void Kill(int direction = 0);

	//�ٶȼ���
	virtual void SpeedCal();

	int direction = 0; // ������0��, 1��
	int CreatureLayer = 3;//1ͼ��� 2����� 3����� 0������
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
	bool isShow = false;//�Ƿ���ʾ
	bool isOnFloor = false;//�Ƿ��ڵ���
	bool isFly = false;//�Ƿ���Է���
	bool isInvincible = false;//�Ƿ��޵�
};

//����ͼ��
extern vector<Creature>CreatureVec;

