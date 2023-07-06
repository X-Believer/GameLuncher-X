#pragma once
#include<iostream>
#include<graphics.h>
#include<set>
#include<vector>
#include<algorithm>
#include<string>
#include"Transparent.h"
using namespace std;

class Creature
{
public:
	int m_Health;//����
	double m_X, m_Y;//��ǰλ��
	double m_Wid, m_Hei;//��ɫ���
	double m_Vx, m_Vy;//��ɫ�ٶ�
	double m_Fx, m_Fy;//��ɫ����
	string PicFile;

	bool out_of_range = true; //��������ͼ��Χ
	bool last_direction = false; // ������false��, true ��

	bool isShow;//�Ƿ���ʾ
	bool IsCollide(double x, double y, Creature& creature);
	void SetPos(double x, double y, double width, double height); //����λ��

	virtual void Render(double x, double y, const char* file)=0; //��Ⱦ��ɫ
	virtual void Kill(int direction)=0; //����ɱ
};

