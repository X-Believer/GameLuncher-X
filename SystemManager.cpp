#include "SystemManager.h"
#include "Transparent.h"
#include "Games.h"
#include "五子棋.h"
namespace
{
	//主菜单图片
	IMAGE mainBg; IMAGE gamePlayer; IMAGE castle; IMAGE Setting; IMAGE Setting_glow;
	IMAGE Select; IMAGE warning; IMAGE russiaBlock;
	IMAGE fiveChess; IMAGE mario; IMAGE snake; IMAGE Exit;
	IMAGE russiaBlock_Glow; IMAGE fiveChess_Glow; IMAGE mario_Glow; IMAGE snake_Glow;

	//设置菜单图片
	IMAGE AdjustVolume; IMAGE AdjustVolume_glow; IMAGE AudioRound; IMAGE BGM; IMAGE BGM_glow;
	IMAGE ChangeAccount; IMAGE ChangeAccount_glow; IMAGE ChooseLevel; IMAGE ChooseLevel_glow;
	IMAGE GameSound; IMAGE GameSound_glow; IMAGE GoBack; IMAGE GoMainMenu; IMAGE GoMainMenu_glow;
	IMAGE LeaderBoard; IMAGE LeaderBoard_glow; IMAGE LogOut; IMAGE LogOut_glow; IMAGE SettingMenuBg;
	IMAGE SystemVersion; IMAGE GoBack_glow;

	int LBotton = 0; int RBotton = 0;
	int MusicFlag = 1;
	//0游戏机 >10城堡 >10小游戏1 >20小游戏2 >30小游戏3 >40小游戏4
}

//构造函数
SystemManager::SystemManager()
{

}

//设置窗口
string SystemManager::SettingMenu(string page)
{
	//加载图片
	if (1)
	{
		loadimage(&SettingMenuBg, "Graph/SettingMenu/SettingMenu.png"); loadimage(&Exit, "Graph/SettingMenu/Exit.png");
		loadimage(&AdjustVolume, "Graph/SettingMenu/AdjustVolume.png"); loadimage(&AdjustVolume_glow, "Graph/SettingMenu/AdjustVolume_glow.png");
		loadimage(&AudioRound, "Graph/SettingMenu/AudioRound.png"); loadimage(&GoBack, "Graph/SettingMenu/GoBack.png");
		loadimage(&BGM, "Graph/SettingMenu/BGM.png"); loadimage(&BGM_glow, "Graph/SettingMenu/BGM_glow.png");
		loadimage(&ChangeAccount, "Graph/SettingMenu/ChangeAccount.png"); loadimage(&ChangeAccount_glow, "Graph/SettingMenu/ChangeAccount_glow.png");
		loadimage(&ChooseLevel, "Graph/SettingMenu/ChooseLevel.png"); loadimage(&ChooseLevel_glow, "Graph/SettingMenu/ChooseLevel_glow.png");
		loadimage(&GameSound, "Graph/SettingMenu/GameSound.png"); loadimage(&GameSound_glow, "Graph/SettingMenu/GameSound_glow.png");
		loadimage(&GoMainMenu, "Graph/SettingMenu/GoMainMenu.png"); loadimage(&GoMainMenu_glow, "Graph/SettingMenu/GoMainMenu_glow.png");
		loadimage(&LeaderBoard, "Graph/SettingMenu/LeaderBoard.png"); loadimage(&LeaderBoard_glow, "Graph/SettingMenu/LeaderBoard_glow.png");
		loadimage(&LogOut, "Graph/SettingMenu/LogOut.png"); loadimage(&LogOut_glow, "Graph/SettingMenu/LogOut_glow.png");
		loadimage(&SystemVersion, "Graph/SettingMenu/SystemVersion.png"); loadimage(&GoBack_glow, "Graph/SettingMenu/GoBack_glow.png");
	}

	while (1)
	{
		int status = UserDO("SettingMenu");
		BeginBatchDraw();
		putimagePNG(NULL, 0, 0, &SettingMenuBg); putimagePNG(NULL, 838, 495, &Exit);
		putimagePNG(NULL, 177, 206, &AdjustVolume); putimagePNG(NULL, 398, 206, &BGM);
		putimagePNG(NULL, 398, 378, &ChangeAccount); putimagePNG(NULL, 398, 292, &ChooseLevel);
		putimagePNG(NULL, 398, 141, &GameSound); putimagePNG(NULL, 19, 26, &GoBack);
		putimagePNG(NULL, 177, 291, &GoMainMenu); putimagePNG(NULL, 398, 438, &LeaderBoard);
		putimagePNG(NULL, 177, 378, &LogOut); putimagePNG(NULL, 8, 370, &SystemVersion);

		EndBatchDraw();
	}
}

//用户交互
int SystemManager::UserDO(string page)
{
	ExMessage msg;
	getmessage(&msg);

	//主菜单交互
	if (page == "MainMenu")
	{
		//游戏机和城堡
		if (msg.x > 180 && msg.x < 400 && msg.y>80 && msg.y < 250)
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				LBotton = (LBotton == 0) ? 10 : 0;
				mciSendString("play Audio/MainMenu/Botton1.mp3", 0, 0, 0);
				return 1;//有点击
			}
		}

		//五子棋
		else if (msg.x > 540 && msg.x < 725 && msg.y>70 && msg.y < 200)
		{
			RBotton = 10;
			if (msg.message == WM_LBUTTONDOWN)
			{
				mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				return 1;//有点击
			}
		}

		//马里奥
		else if (msg.x > 760 && msg.x < 945 && msg.y>70 && msg.y < 200)
		{
			RBotton = 20;
			if (msg.message == WM_LBUTTONDOWN)
			{
				mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				return 1;//有点击
			}
		}

		//贪吃蛇
		else if (msg.x > 540 && msg.x < 725 && msg.y>230 && msg.y < 360)
		{
			RBotton = 30;
			if (msg.message == WM_LBUTTONDOWN)
			{
				mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				return 1;//有点击
			}
		}

		//俄罗斯方块
		else if (msg.x > 760 && msg.x < 945 && msg.y>230 && msg.y < 360)
		{
			RBotton = 40;
			if (msg.message == WM_LBUTTONDOWN)
			{
				mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				return 1;//有点击
			}
		}

		//退出应用
		else if (msg.x > 840 && msg.x < 955 && msg.y>500 && msg.y < 530)
		{
			RBotton = 50;
			if (msg.message == WM_LBUTTONDOWN)
			{
				mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				return 1;//有点击
			}
		}

		//游戏设置
		else if (msg.x > 20 && msg.x < 60 && msg.y>480 && msg.y < 522)
		{
			RBotton = 60;
			if (msg.message == WM_LBUTTONDOWN)
			{
				mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				return 1;//有点击
			}
		}

		else
		{
			RBotton = 0;
			return 0;//0表示未接触任何交互点
		}
	}
	
	//设置菜单交互
	else if (page == "SettingMenu")
	{
		return 0;
	}

	else
	{
		return 0;
	}
}

//显示主菜单
string SystemManager::ShowMenu(int page)
{

	//加载背景图片
	if (page == 1)
	{
		loadimage(&mainBg, "Graph/MainMenu/MainMenu.png"); loadimage(&gamePlayer, "Graph/MainMenu/GamePlayer.png");
		loadimage(&castle, "Graph/MainMenu/Castle.png"); loadimage(&Select, "Graph/MainMenu/SelectGame.png");
		loadimage(&warning, "Graph/MainMenu/Warning.png"); loadimage(&russiaBlock, "Graph/MainMenu/RussiaBlock.png");
		loadimage(&fiveChess, "Graph/MainMenu/FiveChess.png"); loadimage(&mario, "Graph/MainMenu/Mario.png");
		loadimage(&snake, "Graph/MainMenu/Snake.png"); loadimage(&russiaBlock_Glow, "Graph/MainMenu/RussiaBlock_glow.png");
		loadimage(&fiveChess_Glow, "Graph/MainMenu/FiveChess_glow.png"); loadimage(&mario_Glow, "Graph/MainMenu/Mario_glow.png");
		loadimage(&snake_Glow, "Graph/MainMenu/Snake_glow.png"); loadimage(&Exit, "Graph/MainMenu/Exit.png");
		loadimage(&Setting, "Graph/MainMenu/Setting.png"); loadimage(&Setting_glow, "Graph/MainMenu/Setting_glow.png");
	}

	//播放背景音乐
	mciSendString("open Audio/MainMenu/Theme.mp3 alias MainTheme", 0, 0, 0);
	mciSendString("play MainTheme repeat", 0, 0, 0);

	while (1)
	{
		int status = UserDO("MainMenu");
		BeginBatchDraw();//开始缓冲
		putimagePNG(NULL, 0, 0, &mainBg); putimagePNG(NULL, 840, 500, &Exit);
		putimagePNG(NULL, 540, 70, &fiveChess); putimagePNG(NULL, 760, 70, &mario);
		putimagePNG(NULL, 760, 230, &russiaBlock); putimagePNG(NULL, 540, 230, &snake);
		putimagePNG(NULL, 20, 480, &Setting);

		//打印游戏机
		if (LBotton == 0)
		{
		    putimagePNG(NULL, 140, 10, &gamePlayer);
		}

		//打印城堡
		else if(LBotton == 10)
		{
			putimagePNG(NULL, 20, 1, &castle);
		}

		//五子棋
		if (RBotton == 10)
		{
			putimagePNG(NULL, 540, 70, &fiveChess_Glow);
			if (status == 1)
			{
				EndBatchDraw();
				return "FiveChess";
			}
		}

		//马里奥
		else if (RBotton == 20)
		{
			putimagePNG(NULL, 760, 70, &mario_Glow);
			if (status == 1)
			{
				/*EndBatchDraw();
				return "Mario";*/
			}
		}

		//贪吃蛇
		else if (RBotton == 30)
		{
			putimagePNG(NULL, 540, 230, &snake_Glow);
			if (status == 1)
			{
				/*EndBatchDraw();
				return "Snake";*/
			}
		}

		//俄罗斯方块
		else if (RBotton == 40)
		{
			putimagePNG(NULL, 760, 230, &russiaBlock_Glow);
			if (status == 1)
			{
				/*EndBatchDraw();
				return "RussiaBlock";*/
			}
		}

		//退出应用
		else if (RBotton == 50 && status == 1)
		{
			EndBatchDraw();
			return "Exit";
		}

		//游戏设置
		else if (RBotton == 60)
		{
			putimagePNG(NULL, 20, 480, &Setting_glow);
			if (status == 1)
			{
				string settingchoice = SettingMenu("MainMenu");
				if (settingchoice == "Break")
				{
					EndBatchDraw();
					return 
				}
				/*MusicFlag = MusicFlag == 1 ? 0 : 1;
				if(MusicFlag==0)
				    mciSendString("pause MainTheme", 0, 0, 0);
				else if (MusicFlag == 1)
					mciSendString("resume MainTheme", 0, 0, 0);*/
			}
		}

		EndBatchDraw();//结束缓冲
	}
}

//析构函数
SystemManager::~SystemManager()
{

}
