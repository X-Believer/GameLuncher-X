#pragma once
#include<vector>
using namespace std;

class FiveChessAi
{
public:

	//���캯��
	FiveChessAi();

	//Ai����
	void PutChess(int board[][18], int& xAi, int& yAi);

	//��������
	~FiveChessAi();

private:

	//Ȩֵͼ
	int Map[18][18];

	//��¼����λ��
	struct AiPos
	{
		int x;
		int y;

		AiPos(int r=0,int c=0):x(r),y(c){}
	};

	//����Ȩֵ
	void CalculateWorth(int board[][18]);

};

