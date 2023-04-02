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

	//全屏显示
	/*HWND hwnd = GetHWnd();
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CXSCREEN), SWP_SHOWWINDOW);*/

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

		//回到主菜单
		else if (Choice == "MainMenu")
		{
			continue;
		}
	}

	return 0;
}