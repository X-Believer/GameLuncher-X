#pragma once
#include<iostream>
#include<graphics.h>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;

class Creature
{
public:
	int m_Health;//����
	double m_X, m_Y;//��ǰλ��
	double m_Wid, m_Hei;//��ɫ���
	double m_Vx, m_Vy;//��ɫ�ٶ�
	double m_Fx, m_Fy;//��ɫ����

	bool isShow;//�Ƿ���ʾ
	bool IsCollide(double x, double y, Creature& creature);

};

