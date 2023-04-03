#include<iostream>
#include<string>
#include"SystemManager.h"
#include"Games.h"
#include"FiveChess.h"
using namespace std;

#define WIN_WIDTH  960//�˵����ڴ�С
#define WIN_HEIGHT 540
string Choice;

int main()
{
	//������Ϸ����
	initgraph(WIN_WIDTH, WIN_HEIGHT);

	//ȫ����ʾ
	/*HWND hwnd = GetHWnd();
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CXSCREEN), SWP_SHOWWINDOW);*/

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

		//�ص����˵�
		else if (Choice == "MainMenu")
		{
			continue;
		}
	}

	return 0;
}