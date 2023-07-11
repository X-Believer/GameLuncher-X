#pragma once
#include<string>
#include<iostream>
#include<graphics.h>
#include<set>
#include<vector>
#include<cstring>
#include<map>
#include<algorithm>
#include<Windows.h>
#include<string>
#include<cmath>
#include"Transparent.h"
using namespace std;

#define TOP 0//��ײ����
#define RIGHT 2
#define BOTTOM 1
#define LEFT 3
#define EPS 1e-5//���������
#define Margin 6//��ͼY�������,����Y=(540+5)-����Y*42-�����

//�����̳�����
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

//ͼ����Ϣ
struct blockInfo
{
	string name;
	bool isCheck;//�Ƿ���
	bool isReject;//�Ƿ��ų�
	int fun;//���鹦��(��Ӧͼ�鼯ID)
};

//��ײͼ��
extern vector<vector<pair<int, blockInfo>>>CollideVec;

extern int gameIndex;//��Ϸʱ���
extern int idleIndex;//����ʱ���
extern int marioIndex;//�����ʱ���

//��ʱ��
extern double AniTimer;//������ʱ��
extern double StaTimer;//״̬��ʱ��
extern double IdleTimer;//������ʱ��
extern double LastDelay;//��һ֡�ӳ�

extern int Gravity;//����
extern int Friction;//Ħ����
extern int TileWid; extern int TileHei;//ͼ����
extern int MapWid; extern int MapHei;//��ͼ���
extern double MapMov;

//�����״̬ 0->freeze 1->idle 2->run 3->jump 4->down 5->climb 6->attack 7->squat 8->die
extern int MarioStatus;

//��������
struct object
{
	double x;
	double y;
	char* type;
	char* name;
};

//ÿ����ͼͼ��
struct layer
{
	char name[32];
	int* tiles;
	int width;
	int height;
	int type;
	//type:[0]ͼ��㣻[1]����㣻[2]ͼ���
	int objectsCount;
	object* objects;
};

//��ͼ��
struct tileset
{
	int tileWidth;
	int tileHeight;
	int margin;

	int row;
	int col;
	int tileCount;

	string tileFile;
};

//��ͼ
struct MarioMap
{
	int width;//��λ:ͼ��(42*42)
	int height;
	int pixelWidth;//���ؿ��
	int pixelHeight;
	int x;//��ͼλ��
	int y;

	struct tileset tileSet;
	struct layer* layers;//�洢ͼ����Ϣ
	int layerCount;

	IMAGE imageTiles[600];//�洢ÿ��ͼ��ͼƬ
	IMAGE imgLayer[10];//�洢ÿ��ͼ��ͼƬ
	IMAGE imgBg;
};