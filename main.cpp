#include<iostream>
#include<string>
#include"SystemManager.h"
#include"Games.h"
#include"五子棋.h"
using namespace std;

#define WIN_WIDTH  960//菜单窗口大小
#define WIN_HEIGHT 540
string Choice;

int main()
{
	//创建游戏窗口
	initgraph(WIN_WIDTH, WIN_HEIGHT);

	SystemManager sm;
	while (1)
	{
		Choice = sm.ShowMenu(1);

		//启动五子棋
		if (Choice == "FiveChess")
		{
			Games* player = NULL;
			player = new FiveChess("FengYuhan");
			player->RunGame();
			delete player;
		}

		//启动马里奥
		else if (Choice == "Mario")
		{
			Games* player = NULL;
			player = new FiveChess("FengYuhan");
			player->RunGame();
			delete player;
		}

		//启动贪吃蛇
		else if (Choice == "Snake")
		{
			Games* player = NULL;
			player = new FiveChess("FengYuhan");
			player->RunGame();
			delete player;
		}

		//启动俄罗斯方块
		else if (Choice == "RussiaBlock")
		{
			Games* player = NULL;
			player = new FiveChess("FengYuhan");
			player->RunGame();
			delete player;
		}

		//退出系统
		else if (Choice == "Exit")
		{
			return 0;
		}
	}

	return 0;
}