#include"MarioGlobal.h"

//��ײͼ��
vector<vector<pair<int, blockInfo>>>CollideVec;

int gameIndex = 0;//��Ϸʱ���
int idleIndex = 0;//����ʱ���
int marioIndex = 0;//�����ʱ���

//��ʱ��
int AniTimer = 0;//������ʱ��
int StaTimer = 0;//״̬��ʱ��
int IdleTimer = 0;//������ʱ��
int LastDelay = 0;//��һ֡�ӳ�

int Gravity = 10;//����
int Friction = 15;//Ħ����
int TileWid = 0; int TileHei = 0;//ͼ����
int MapWid = 0; int MapHei = 0;//��ͼ���

int MarioStatus = 0;//�����״̬