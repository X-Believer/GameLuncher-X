#pragma once
#include<vector>
using namespace std;

class FiveChessAi
{
public:

	//构造函数
	FiveChessAi();

	//Ai落子
	void PutChess(int board[][18], int& xAi, int& yAi);

	//析构函数
	~FiveChessAi();

private:

	//权值图
	int Map[18][18];

	//记录落子位置
	struct AiPos
	{
		int x;
		int y;

		AiPos(int r=0,int c=0):x(r),y(c){}
	};

	//计算权值
	void CalculateWorth(int board[][18]);

};

