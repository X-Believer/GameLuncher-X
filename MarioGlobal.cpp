#include"MarioGlobal.h"

//��ײͼ��
vector<vector<pair<int, blockInfo>>>CollideVec;

int gameIndex = 0;//��Ϸʱ���
int idleIndex = 0;//����ʱ���
int marioIndex = 0;//�����ʱ���

//��ʱ��
double AniTimer = 0;//������ʱ��
double StaTimer = 0;//״̬��ʱ��
double IdleTimer = 0;//������ʱ��
double LastDelay = 0;//��һ֡�ӳ�

int Gravity = 1;//����
int Friction = 1;//Ħ����
int TileWid = 0; int TileHei = 0;//ͼ����
int MapWid = 0; int MapHei = 0;//��ͼ���
double MapMov = 0;//��ͼλ��

int MarioStatus = 0;//�����״̬