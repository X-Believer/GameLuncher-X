#include<iostream>
#include<string>
#include"SystemManager.h"
#include"Games.h"
#include"������.h"
using namespace std;

#define WIN_WIDTH  960//�˵����ڴ�С
#define WIN_HEIGHT 540
string Choice;

int main()
{
	//������Ϸ����
	initgraph(WIN_WIDTH, WIN_HEIGHT);

	SystemManager sm;
	while (1)
	{
		Choice = sm.ShowMenu(1);

		//����������
		if (Choice == "FiveChess")
		{
			Games* player = NULL;
			player = new FiveChess("FengYuhan");
			player->RunGame();
			delete player;
		}

		//���������
		else if (Choice == "Mario")
		{
			Games* player = NULL;
			player = new FiveChess("FengYuhan");
			player->RunGame();
			delete player;
		}

		//����̰����
		else if (Choice == "Snake")
		{
			Games* player = NULL;
			player = new FiveChess("FengYuhan");
			player->RunGame();
			delete player;
		}

		//��������˹����
		else if (Choice == "RussiaBlock")
		{
			Games* player = NULL;
			player = new FiveChess("FengYuhan");
			player->RunGame();
			delete player;
		}

		//�˳�ϵͳ
		else if (Choice == "Exit")
		{
			return 0;
		}
	}

	return 0;
}