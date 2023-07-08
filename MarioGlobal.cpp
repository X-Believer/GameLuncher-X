#include"MarioGlobal.h"

//碰撞图层
vector<vector<pair<int, blockInfo>>>CollideVec;

int gameIndex = 0;//游戏时间戳
int idleIndex = 0;//待机时间戳
int marioIndex = 0;//马里奥时间戳

//计时器
int AniTimer = 0;//动画计时器
int StaTimer = 0;//状态计时器
int IdleTimer = 0;//待机计时器
int LastDelay = 0;//上一帧延迟

int Gravity = 10;//重力
int Friction = 15;//摩擦力
int TileWid = 0; int TileHei = 0;//图块宽高
int MapWid = 0; int MapHei = 0;//地图宽高

int MarioStatus = 0;//马里奥状态