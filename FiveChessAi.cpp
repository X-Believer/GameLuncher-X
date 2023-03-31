#include "FiveChessAi.h"

//构造函数
FiveChessAi::FiveChessAi()
{
	memset(Map, 0, sizeof(Map));
}

//Ai落子
void FiveChessAi::PutChess(int board[][18], int& xAi, int& yAi)
{
	CalculateWorth(board);
	vector<AiPos>arr;
	int maxWorth = 0;

	for (int row = 1; row < 18; row++)
	{
		for (int col = 1; col < 18; col++)
		{
			if (board[row][col] == 0)
			{
				if (Map[row][col] > maxWorth)
				{
					maxWorth = Map[row][col];
					arr.clear();
					arr.push_back(AiPos(row, col));
				}
				else if (Map[row][col] == maxWorth)
				{
					arr.push_back(AiPos(row,col));
				}
			}
		}
	}

	int index = rand() % arr.size();
	board[arr[index].x][arr[index].y] = 2;
	xAi = arr[index].x; yAi = arr[index].y;
}

//计算权值
void FiveChessAi::CalculateWorth(int board[][18])
{
	int BlackNum = 0;//玩家(黑)在此处有多少连子
	int WhiteNum = 0;//Ai(白)在此处有多少连子
	int emptyNum = 0;//该方向空白个数

	memset(Map, 0, sizeof(Map));

	//对每个点计算权值
	for (int row = 1; row < 18; row++)
	{
		for (int col = 1; col < 18; col++)
		{
			//判断逻辑：从4个方向及其反方向计算连子数，对不同棋形赋权值
			if (board[row][col])continue;

			for (int y = -1; y <= 0; y++)//竖直方向移动
			{
				for (int x = -1; x <= 1; x++)//水平方向移动
				{
					if (y == 0 && x == 0 || y == 0 && x != 1)continue;

					BlackNum = 0; WhiteNum = 0; emptyNum = 0;

					//假设黑棋在此落子构成的棋形
					for (int i = 1; i < 5; i++)
					{
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 1 && curRow < 18 &&
							curCol >= 1 && curCol < 18 &&
							board[curRow][curCol] == 1)
						{
							BlackNum++;
						}
						else if (curRow >= 1 && curRow < 18 &&curCol >= 1 && curCol < 18 &&board[curRow][curCol] == 0)
						{
							emptyNum++;
							break;
						}
						else if (curRow >= 1 && curRow < 18 &&curCol >= 1 && curCol < 18 &&board[curRow][curCol] == 2)
						{
							break;
						}
					}

					//反向继续计算
					for (int i = 1; i < 5; i++)
					{
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 1 && curRow < 18 &&
							curCol >= 1 && curCol < 18 &&
							board[curRow][curCol] == 1)
						{
							BlackNum++;
						}
						else if (curRow >= 1 && curRow < 18 && curCol >= 1 && curCol < 18 && board[curRow][curCol] == 0)
						{
							emptyNum++;
							break;
						}
						else if (curRow >= 1 && curRow < 18 && curCol >= 1 && curCol < 18 && board[curRow][curCol] == 2)
						{
							break;
						}
					}

					//连二
					if (BlackNum == 1)
					{
						Map[row][col] += 10;
					}
					
					//连三
					else if (BlackNum == 2)
					{
						if (emptyNum == 1)
						{
							Map[row][col] += 30;
						}
						else if (emptyNum == 2)
						{
							Map[row][col] += 40;
						}
					}

					//连四
					else if (BlackNum == 3)
					{
						if (emptyNum == 1)
						{
							Map[row][col] += 60;
						}
						else if (emptyNum == 2)
						{
							Map[row][col] += 200;
						}
					}

					//连五
					else if (BlackNum >= 4)
					{
						Map[row][col] = 20000;
					}

					//假设白棋在此落子构成的棋形
					emptyNum = 0;

					for (int i = 1; i < 5; i++)
					{
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 1 && curRow < 18 &&
							curCol >= 1 && curCol < 18 &&
							board[curRow][curCol] == 2)
						{
							WhiteNum++;
						}
						else if (curRow >= 1 && curRow < 18 && curCol >= 1 && curCol < 18 && board[curRow][curCol] == 0)
						{
							emptyNum++;
							break;
						}
						else if (curRow >= 1 && curRow < 18 && curCol >= 1 && curCol < 18 && board[curRow][curCol] == 1)
						{
							break;
						}
					}

					//反向继续计算
					for (int i = 1; i < 5; i++)
					{
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 1 && curRow < 18 &&curCol >= 1 && curCol < 18 &&board[curRow][curCol] == 2)
						{
							WhiteNum++;
						}
						else if (curRow >= 1 && curRow < 18 && curCol >= 1 && curCol < 18 && board[curRow][curCol] == 0)
						{
							emptyNum++;
							break;
						}
						else if (curRow >= 1 && curRow < 18 && curCol >= 1 && curCol < 18 && board[curRow][curCol] == 1)
						{
							break;
						}
					}

					//单子
					if (WhiteNum == 0)
					{
						Map[row][col] += 5;
					}

					//连二
					if (WhiteNum == 1)
					{
						Map[row][col] += 10;
					}

					//连三
					else if (WhiteNum == 2)
					{
						if (emptyNum == 1)
						{
							Map[row][col] += 25;
						}
						else if (emptyNum == 2)
						{
							Map[row][col] += 50;
						}
					}

					//连四
					else if (WhiteNum == 3)
					{
						if (emptyNum == 1)
						{
							Map[row][col] += 55;
						}
						else if (emptyNum == 2)
						{
							Map[row][col] += 10000;
						}
					}

					//连五
					else if (WhiteNum >= 4)
					{
						Map[row][col] = 30000;
					}
				}
			}
		}
	}
}

//析构函数
FiveChessAi::~FiveChessAi()
{

}