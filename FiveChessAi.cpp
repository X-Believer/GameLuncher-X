#include "FiveChessAi.h"

//���캯��
FiveChessAi::FiveChessAi()
{
	memset(Map, 0, sizeof(Map));
}

//Ai����
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

//����Ȩֵ
void FiveChessAi::CalculateWorth(int board[][18])
{
	int BlackNum = 0;//���(��)�ڴ˴��ж�������
	int WhiteNum = 0;//Ai(��)�ڴ˴��ж�������
	int emptyNum = 0;//�÷���հ׸���

	memset(Map, 0, sizeof(Map));

	//��ÿ�������Ȩֵ
	for (int row = 1; row < 18; row++)
	{
		for (int col = 1; col < 18; col++)
		{
			//�ж��߼�����4�������䷴����������������Բ�ͬ���θ�Ȩֵ
			if (board[row][col])continue;

			for (int y = -1; y <= 0; y++)//��ֱ�����ƶ�
			{
				for (int x = -1; x <= 1; x++)//ˮƽ�����ƶ�
				{
					if (y == 0 && x == 0 || y == 0 && x != 1)continue;

					BlackNum = 0; WhiteNum = 0; emptyNum = 0;

					//��������ڴ����ӹ��ɵ�����
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

					//�����������
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

					//����
					if (BlackNum == 1)
					{
						Map[row][col] += 10;
					}
					
					//����
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

					//����
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

					//����
					else if (BlackNum >= 4)
					{
						Map[row][col] = 20000;
					}

					//��������ڴ����ӹ��ɵ�����
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

					//�����������
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

					//����
					if (WhiteNum == 0)
					{
						Map[row][col] += 5;
					}

					//����
					if (WhiteNum == 1)
					{
						Map[row][col] += 10;
					}

					//����
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

					//����
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

					//����
					else if (WhiteNum >= 4)
					{
						Map[row][col] = 30000;
					}
				}
			}
		}
	}
}

//��������
FiveChessAi::~FiveChessAi()
{

}