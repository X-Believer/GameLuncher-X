#pragma once
#include<string>
#include<iostream>
#include<graphics.h>
#include<set>
#include<vector>
#include<map>
#include<algorithm>
#include<Windows.h>
#include<string>
#include<cmath>
#include"Transparent.h"
using namespace std;

//ͼ����Ϣ
struct blockInfo
{
	string name;
	bool isCheck;//�Ƿ���
	bool isReject;//�Ƿ��ų�
	int fun;//���鹦��(����㹦�ܴ�101��ʼ)
};

//��ײͼ��
extern vector<vector<pair<int, blockInfo>>>CollideVec;

extern int gameIndex;//��Ϸʱ���
extern int idleIndex;//����ʱ���
extern int marioIndex;//�����ʱ���

//��ʱ��
extern int AniTimer;//������ʱ��
extern int StaTimer;//״̬��ʱ��
extern int IdleTimer;//������ʱ��
extern int LastDelay;//��һ֡�ӳ�

//��ײ����
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

//����
extern int Gravity;
//Ħ����
extern int Friction;
//ͼ����
extern int TileWid; extern int TileHei;
//��ͼ���
extern int MapWid; extern int MapHei;

//�����״̬ 0->freeze 1->idle 2->run 3->jump 4->down 5->climb 6->attack 7->squat
extern int MarioStatus;

//�����̳�����
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

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