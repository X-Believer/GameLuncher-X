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

#define TOP 0//碰撞方向
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3
#define EPS 1e-5//浮点数误差
#define Margin 6//地图Y坐标误差,像素Y=(540+5)-方块Y*42-对象高

//检测键盘常函数
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

//图块信息
struct blockInfo
{
	string name;
	bool isCheck;//是否检测
	bool isReject;//是否排斥
	int fun;//方块功能(对应图块集ID)
};

//碰撞图层
extern vector<vector<pair<int, blockInfo>>>CollideVec;

extern int gameIndex;//游戏时间戳
extern int idleIndex;//待机时间戳
extern int marioIndex;//马里奥时间戳

//计时器
extern int AniTimer;//动画计时器
extern int StaTimer;//状态计时器
extern int IdleTimer;//待机计时器
extern int LastDelay;//上一帧延迟

extern int Gravity;//重力
extern int Friction;//摩擦力
extern int TileWid; extern int TileHei;//图块宽高
extern int MapWid; extern int MapHei;//地图宽高
extern double MapMov;

extern int MarioStatus;//马里奥状态 0->freeze 1->idle 2->run 3->jump 4->down 5->climb 6->attack 7->squat

//对象物体
struct object
{
	double x;
	double y;
	char* type;
	char* name;
};

//每个地图图层
struct layer
{
	char name[32];
	int* tiles;
	int width;
	int height;
	int type;
	//type:[0]图块层；[1]对象层；[2]图像层
	int objectsCount;
	object* objects;
};

//地图集
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

//地图
struct MarioMap
{
	int width;//单位:图块(42*42)
	int height;
	int pixelWidth;//像素宽高
	int pixelHeight;
	int x;//地图位移
	int y;

	struct tileset tileSet;
	struct layer* layers;//存储图层信息
	int layerCount;

	IMAGE imageTiles[600];//存储每个图块图片
	IMAGE imgLayer[10];//存储每个图层图片
	IMAGE imgBg;
};