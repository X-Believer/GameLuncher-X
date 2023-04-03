#include"FiveChess.h"
#include"Transparent.h"
#include<cmath>
#include<string>
#include<string.h>
#include"FiveChessAi.h"
#include"SystemManager.h"
namespace
{
	int Turn = 0;//落子顺序
	int flag = 0;//结束标志
	int isAi = 0;//是否人机
	int xAi = 0, yAi = 0;//Ai最后落子位置
	int xNow = 0, yNow = 0;//最后落子位置
	int LBotton = 0, RBotton = 0;//棋盘和交互键_R=1悔棋,R=2清空,R=3AI,R=4主题,R=5菜单
	int board[18][18] = { 0 };//棋盘数组

	IMAGE bgp; IMAGE FiveChessBoard; IMAGE AI; IMAGE GamePic;
	IMAGE Retract; IMAGE SelectTheme; IMAGE GoMainMenu; IMAGE ClearBoard;
	IMAGE Black; IMAGE White; IMAGE BlackWin; IMAGE WhiteWin; IMAGE ClearBoard_glow;
	IMAGE Retract_glow; IMAGE SelectTheme_glow; IMAGE AI_glow; IMAGE GoMainMenu_glow;
	IMAGE GameSettings; IMAGE GameSettings_glow;

	FiveChessAi* Ai;
}

//构造函数
FiveChess::FiveChess(string name)
{
	this->m_PlayerName = name;
}

//显示界面
void FiveChess::putboard()
{
	putimagePNG(NULL, 0, 0, &bgp);
	putimagePNG(NULL, 44, 1, &FiveChessBoard);
	putimagePNG(NULL, 696, 127, &Retract);
	putimagePNG(NULL, 696, 205, &ClearBoard);
	putimagePNG(NULL, 696, 283, &AI);
	putimagePNG(NULL, 696, 361, &GameSettings);
	putimagePNG(NULL, 696, 439, &GoMainMenu);
}

//落子实现
void FiveChess::drawchess(int m, int n)
{
	int x, y;
	x = abs(m - 70) / 30 + 1;
	y = abs(n - 10) / 30 + 1;
	xNow = x; yNow = y;

	if (board[x][y] != 0)
		return;

	board[x][y] = Turn == 1 ? 2 : 1;//1是黑，2是白

	if (Turn == 0)Turn = 1;
	else if (Turn == 1 && isAi == 0)Turn = 0;
}

//用户交互
int FiveChess::UserDo()
{
	ExMessage msg;
	getmessage(&msg);

	//落子判断
	if (flag != 1 && msg.x > 40 && msg.x < 590 && msg.y>1 && msg.y < 530 && msg.message == WM_LBUTTONDOWN)
	{
		if (isAi == 0 || isAi == 1 && Turn == 0)
		{
			mciSendString("play Audio/FiveChess/ChessDown.mp3", 0, 0, 0);
			drawchess(msg.x, msg.y);
		}
		return 0;
	}

	//悔棋
	else if (msg.x > 696 && msg.x < 920 && msg.y>130 && msg.y < 190)
	{
		RBotton = 1;
		if (flag != 1 && msg.message == WM_LBUTTONDOWN)
		{
			mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
			return 1;
		}
		return 0;
	}

	//清空棋盘
	else if (msg.x > 696 && msg.x < 920 && msg.y>205 && msg.y < 265)
	{
		RBotton = 2;
		if (msg.message == WM_LBUTTONDOWN)
		{
			mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
			return 1;
		}
		return 0;
	}

	//AI对战
	else if (msg.x > 696 && msg.x < 920 && msg.y>280 && msg.y < 345)
	{
		RBotton = 3;
		if (msg.message == WM_LBUTTONDOWN)
		{
			mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
			return 1;
		}
		return 0;
	}

	//游戏设置
	else if (msg.x > 696 && msg.x < 920 && msg.y>360 && msg.y < 425)
	{
		RBotton = 4;
		if (msg.message == WM_LBUTTONDOWN)
		{
			mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
			return 1;
		}
		return 0;
	}

	//返回主菜单
	else if (msg.x > 696 && msg.x < 920 && msg.y>440 && msg.y < 505)
	{
		RBotton = 5;
		if (msg.message == WM_LBUTTONDOWN)
		{
			mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
			return 1;
		}
		return 0;
	}

	else
	{
		RBotton = 0;
		return 0;//0表示未接触任何交互点
	}
}

//判断输赢
bool FiveChess::checkwin(int x, int y)
{
	int cnt = 0;
	if (board[x][y] == 0)return false;
	for (int i = x >= 5 ? x - 4 : 1; i <= 16 && i <= x + 4; i++)
	{
		if (board[i][y] == board[x][y])cnt++;
		else cnt = 0;
		if (cnt >= 5)return true;
	}
	cnt = 0;
	for (int i = y >= 5 ? y - 4 : 1; i <= 16 && i <= y + 4; i++)
	{
		if (board[x][i] == board[x][y])cnt++;
		else cnt = 0;
		if (cnt >= 5)return true;
	}
	cnt = 0; int i = 0, j = 0;
	if (x >= 5 && y >= 5)
		i = x - 4, j = y - 4;
	else
		i = x > y ? x - y + 1 : 1, j = x > y ? 1 : y - x + 1;

	for (; i <= 16 && j <= 16 && i <= x + 4 && j <= y + 4; i++, j++)
	{
		if (board[i][j] == board[x][y])cnt++;
		else cnt = 0;
		if (cnt >= 5)return true;
	}
	cnt = 0, i = 0, j = 0;
	if (x >= 5 && y <= 12)
		i = x - 4, j = y + 4;
	else
	{
		if (x > 16 - y)i = x - (16 - y), j = 16;
		else i = 1, j = y + x - 1;
	}
	for (; i <= 16 && j >= 1 && i <= x + 4 && j >= y - 4; i++, j--)
	{
		if (board[i][j] == board[x][y])cnt++;
		else cnt = 0;
		if (cnt >= 5)return true;
	}
	return false;
}

//显示设置
void FiveChess::ShowGameMenu()
{

}

//运行游戏
void FiveChess::RunGame()
{
	//cleardevice();

	memset(board, 0, sizeof(board)); Turn = 0; flag = 0; 
	xAi = 0; yAi = 0; xNow = 0; yNow = 0; Ai = new FiveChessAi;

	//载入图片
	if (1)
	{
		loadimage(&bgp, "Graph/FiveChess/FiveChessMenu.png");
		loadimage(&FiveChessBoard, "Graph/FiveChess/BoardBlue.png");
		loadimage(&ClearBoard, "Graph/FiveChess/ClearBoard.png"); loadimage(&ClearBoard_glow, "Graph/FiveChess/ClearBoard_glow.png");
		loadimage(&GoMainMenu, "Graph/FiveChess/GoMainMenu.png"); loadimage(&GoMainMenu_glow, "Graph/FiveChess/GoMainMenu_glow.png");
		loadimage(&GamePic, "Graph/FiveChess/GameName.png");
		loadimage(&Retract, "Graph/FiveChess/Retract.png"); loadimage(&Retract_glow, "Graph/FiveChess/Retract_glow.png");
		loadimage(&SelectTheme, "Graph/FiveChess/SelectTheme.png"); loadimage(&SelectTheme_glow, "Graph/FiveChess/SelectTheme_glow.png");
		loadimage(&White, "Graph/FiveChess/White.png"); loadimage(&GameSettings_glow, "Graph/FiveChess/GameSettings_glow.png");
		loadimage(&Black, "Graph/FiveChess/Black.png"); loadimage(&GameSettings, "Graph/FiveChess/GameSettings.png");
		loadimage(&BlackWin, "Graph/FiveChess/BlackWin.png");
		loadimage(&WhiteWin, "Graph/FiveChess/WhiteWin.png");
		if (isAi == 0)//玩家对战
		{
			loadimage(&AI, "Graph/FiveChess/AI.png"); loadimage(&AI_glow, "Graph/FiveChess/AI_glow.png");
		}
		else if (isAi == 1)//人机对战
		{
			loadimage(&AI, "Graph/FiveChess/VSPlayer.png"); loadimage(&AI_glow, "Graph/FiveChess/VSPlayer_glow.png");

		}
	}

	
	while (1)
	{
		//赢棋之后不再判断
		if (flag == 0)
		{
			if (checkwin(xNow, yNow))
			{
				mciSendString("play Audio/FiveChess/Win.mp3", 0, 0, 0);
				flag = 1;
			}	

			if (isAi == 1 && checkwin(xAi, yAi))
			{
				mciSendString("play Audio/FiveChess/Win.mp3", 0, 0, 0);
				flag = 1;
			}
		}
		
		int status = UserDo();

		//Ai落子
		if (isAi == 1 && Turn == 1 && checkwin(xNow, yNow) == 0)
		{
			for (int i = 1; i <= 17; i++)
			{
				for (int j = 1; j <= 17; j++)
				{
					if (board[i][j] == 1)putimagePNG(NULL, 70 + (i - 1) * 30, 10 + (j - 1) * 30, &Black);
					else if (board[i][j] == 2)putimagePNG(NULL, 70 + (i - 1) * 30, 10 + (j - 1) * 30, &White);
				}
			}
			Sleep(200);
			Ai->PutChess(board,xAi,yAi);
			Turn = 0;
		}

		BeginBatchDraw();
		putboard();

		//悔棋
		if (RBotton == 1)
		{
			putimagePNG(NULL, 696, 127, &Retract_glow);
			if (status == 1 && board[xNow][yNow] != 0)
			{
				if (isAi == 0)
				{
					board[xNow][yNow] = 0;
					Turn = Turn == 1 ? 0 : 1;
				}
				else if (isAi == 1 && xNow != xAi && yNow != yAi)
				{
					board[xNow][yNow] = 0;
					board[xAi][yAi] = 0;
					Turn = 0;
				}
			}
		}

		//清空棋盘
		else if (RBotton == 2)
		{
			putimagePNG(NULL, 696, 205, &ClearBoard_glow);
			if (status == 1)
			{
				memset(board, 0, sizeof(board));
				flag = 0;
				Turn = 0;
			}
		}

		//AI对战
		else if (RBotton == 3)
		{
			putimagePNG(NULL, 696, 283, &AI_glow);
			if (status == 1)
			{
				isAi = isAi == 0 ? 1 : 0;
				delete Ai;
				EndBatchDraw();
				RunGame();
				return;
			}
		}

		//游戏设置
		else if (RBotton == 4)
		{
			putimagePNG(NULL, 696, 361, &GameSettings_glow);
			if (status == 1)
			{
				SystemManager* sm=new SystemManager;
				string settingchoice = sm->SettingMenu("FiveChess");

				//设置中选择返回主菜单
				if (settingchoice == "MainMenu")
				{
					EndBatchDraw();
					return;
				}

				//设置中选择退出登录
				else if (settingchoice == "LogOut")
				{
					EndBatchDraw();
					return;
				}

				//设置中选择选择关卡
				else if (settingchoice == "ChooseLevel")
				{
					
				}

				delete sm;
			}
		}

		//返回主菜单
		else if (RBotton == 5)
		{
			putimagePNG(NULL, 696, 439, &GoMainMenu_glow);
			if (status == 1)
			{
				memset(board, 0, sizeof(board));
				Turn = 0;
				flag = 0;
				isAi = 0;
				EndBatchDraw();
				delete Ai;
				return;
			}
		}
	
		//打印棋子
		for (int i = 1; i <= 17; i++)
		{
			for (int j = 1; j <= 17; j++)
			{
				if (board[i][j] == 1)putimagePNG(NULL, 70 + (i - 1) * 30, 10 + (j - 1) * 30, &Black);
				else if (board[i][j] == 2)putimagePNG(NULL, 70 + (i - 1) * 30, 10 + (j - 1) * 30, &White);
			}
		}

		//胜负输出
		if (flag == 1)
		{			
			if (Turn == 1)
			{
				putimagePNG(NULL, 100, 300, &BlackWin);
			}
			else
			{
				putimagePNG(NULL, 100, 300, &WhiteWin);
			}
		}

		EndBatchDraw();
	}
	return;
}

//析构函数
FiveChess::~FiveChess()
{

}