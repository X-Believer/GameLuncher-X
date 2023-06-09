#include "SystemManager.h"
#include "Transparent.h"
#include "Games.h"
#include "FiveChess.h"
#include"GlobalFile.h"
namespace
{
	//主菜单图片
	IMAGE mainBg; IMAGE gamePlayer; IMAGE castle; IMAGE Setting; IMAGE Setting_glow;
	IMAGE Select; IMAGE warning; IMAGE russiaBlock; IMAGE Account; IMAGE Login;
	IMAGE fiveChess; IMAGE mario; IMAGE snake; IMAGE Exit; IMAGE NotLogin;
	IMAGE russiaBlock_Glow; IMAGE fiveChess_Glow; IMAGE mario_Glow; IMAGE snake_Glow;

	//设置菜单图片
	IMAGE AdjustVolume; IMAGE AdjustVolume_glow; IMAGE AudioRound; IMAGE BGM; IMAGE BGM_glow;
	IMAGE ChangeAccount; IMAGE ChangeAccount_glow; IMAGE ChooseLevel; IMAGE ChooseLevel_glow;
	IMAGE GameSound; IMAGE GameSound_glow; IMAGE GoBack; IMAGE GoMainMenu; IMAGE GoMainMenu_glow;
	IMAGE LeaderBoard; IMAGE LeaderBoard_glow; IMAGE LogOut; IMAGE LogOut_glow; IMAGE SettingMenuBg;
	IMAGE SystemVersion; IMAGE GoBack_glow;

	//账户菜单图片
	IMAGE Accountmenu; IMAGE Account1; IMAGE Achievement; IMAGE Achievement_glow; IMAGE Avatar;
	IMAGE CancelAccount; IMAGE CancelAccount_glow; IMAGE NowOp_glow; IMAGE NowMSG; IMAGE bg;
	IMAGE Login1; IMAGE Login_glow; IMAGE Logout; IMAGE Logout_glow; IMAGE Manager; IMAGE Password;
	IMAGE Problem; IMAGE Problem_glow; IMAGE UserName; IMAGE UserName_glow; IMAGE Window; IMAGE NowOp;
	IMAGE Account1_glow; IMAGE Password_glow; IMAGE EndScan;

	//信息窗口图片
	IMAGE No_glow;IMAGE No; IMAGE Yes; IMAGE Success; IMAGE Sure; 
	IMAGE Wrong; IMAGE Yes_glow; IMAGE Word;

	//管理员菜单图片
	IMAGE Before; IMAGE Before_glow; IMAGE Next; IMAGE Next_glow; IMAGE Delete; IMAGE Delete_glow;
	IMAGE Edit; IMAGE Edit_glow; IMAGE ManagerMenu; IMAGE Preference; IMAGE Preference_glow;
	IMAGE ShowPerson;

	//加载页面图片
	IMAGE LoadingMenuBg; IMAGE LoadInfo1; IMAGE LoadInfo2; IMAGE LoadStage[8]; IMAGE LoadNum[8];
	IMAGE LoadingMenuPic;

	//主菜单控制量
	int LBotton = 0; int RBotton = 0; 
	Identity* Person = NULL; int NowRank = 1;//当前用户指针、当前排名

	//设置菜单控制量
	int Botton = 0;
	int Xvolume = 293;//音量圆圈所在位置

	//账号菜单控制量
	int BottonAccount = 0; int nowOp=1;//1登录，2注册
	string Accountin; string Pwdin;//用户输入的账号密码
	int isscan = 0;

	//信息窗口控制量
	int BottonWindow = 0;

	//加载页面控制量
	int LoadWait[8] = { 500,400,200,200,150,400,200,500 };

	//管理员菜单控制量
	int BottonManager = 0; vector<User>UserInfo;//存储所有用户信息
	int cnt = 0; int Page=1;//当前读取条数、页数
}

int MusicFlag = 1;//是否播放音乐
int SoundFlag = 1;//是否打开游戏音效
int IsLogin = 0;//是否登录

//默认构造
SystemManager::SystemManager()
{

}

//构造函数
SystemManager::SystemManager(string name,string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->m_isVip = 1;
}

//设置菜单
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
		loadimage(&GameSound, "Graph/SettingMenu/GameSound.png"); loadimage(&GameSound_glow, "Graph/SettingMenu/GameSound_glow.png");
		loadimage(&GoMainMenu, "Graph/SettingMenu/GoMainMenu.png"); loadimage(&GoMainMenu_glow, "Graph/SettingMenu/GoMainMenu_glow.png");
		loadimage(&LeaderBoard, "Graph/SettingMenu/LeaderBoard.png"); loadimage(&LeaderBoard_glow, "Graph/SettingMenu/LeaderBoard_glow.png");
		loadimage(&LogOut, "Graph/SettingMenu/LogOut.png"); loadimage(&LogOut_glow, "Graph/SettingMenu/LogOut_glow.png");
		loadimage(&SystemVersion, "Graph/SettingMenu/SystemVersion.png"); loadimage(&GoBack_glow, "Graph/SettingMenu/GoBack_glow.png");
		if (page != "MainMenu")
		{
			loadimage(&ChooseLevel, "Graph/SettingMenu/ChooseLevel.png"); loadimage(&ChooseLevel_glow, "Graph/SettingMenu/ChooseLevel_glow.png");
		}
		else
		{
			loadimage(&ChooseLevel, "Graph/SettingMenu/SelectTheme.png"); loadimage(&ChooseLevel_glow, "Graph/SettingMenu/SelectTheme_glow.png");
		}	
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
		putimagePNG(NULL, Xvolume, 216, &AudioRound);

		//调节音量
		if (Botton == 1)
		{
			putimagePNG(NULL, 177, 206, &AdjustVolume_glow);
			MOUSEMSG audiomsg = GetMouseMsg();
			if (audiomsg.x <= Xvolume + 13 &&
				audiomsg.x >= 229 && audiomsg.x <= 293 &&
				audiomsg.y >= 212 && audiomsg.y <= 232 && audiomsg.mkLButton == true)
			{
				Xvolume = audiomsg.x;
			}
		}

		//返回主菜单
		else if (Botton == 2)
		{
			putimagePNG(NULL, 177, 291, &GoMainMenu_glow);
			if (status == 1)
			{
				if (page != "MainMenu")
				{
					if (SoundFlag == 1)
					{
						mciSendString("play Audio/MainMenu/Tip.mp3", 0, 0, 0);
					}					
					int windowChoice = MSGWindow("Sure", "Graph/MSGWindow/MSGLoss.png");
					if (windowChoice != 2)
					{
						continue;
					}
				}
				EndBatchDraw();
				return "MainMenu";
			}
		}

		//退出登录
		else if (Botton == 3)
		{
			putimagePNG(NULL, 177, 378, &LogOut_glow);
			if (status == 1)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Tip.mp3", 0, 0, 0);
				}

				//当前已登录
				if (IsLogin == 1)
				{
					if (page == "MainMenu")
					{
						int windowChoice = MSGWindow("Sure", "Graph/MSGWindow/MSGIsLogout.png");
						if (windowChoice != 2)
						{
							continue;
						}
					}
					else if (page != "MainMenu")
					{
						int windowChoice = MSGWindow("Sure", "Graph/MSGWindow/MSGLoss.png");
						if (windowChoice != 2)
						{
							continue;
						}
					}
				}

				//当前未登录
				else
				{
					if (SoundFlag == 1)
					{
						mciSendString("play Audio/MainMenu/Tip.mp3", 0, 0, 0);
					}
					EndBatchDraw();
                    MSGWindow("Wrong", "Graph/MSGWindow/MSGNoLogin.png");
					continue;	
				}

				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Tip1.mp3", 0, 0, 0);
				}
				IsLogin = 0;
				MSGWindow("Success", "Graph/MSGWindow/MSGLogout.png");
				EndBatchDraw();
				return "LogOut";
			}
		}

		//游戏音效
		else if (Botton == 4)
		{
			putimagePNG(NULL, 398, 141, &GameSound_glow);
			if (status == 1)
			{
				SoundFlag = SoundFlag == 1 ? 0 : 1;
			}
		}

		//背景音乐
		else if (Botton == 5)
		{
			putimagePNG(NULL, 398, 206, &BGM_glow);
			if (status == 1)
			{
				MusicFlag = MusicFlag == 1 ? 0 : 1;
				if (page == "MarioMenu")
				{
					if (MusicFlag == 0)
						mciSendString("pause MarioTheme", 0, 0, 0);
					else if (MusicFlag == 1)
						mciSendString("resume MarioTheme", 0, 0, 0);
				}

				else if (page == "MarioGame")
				{
					if (MusicFlag == 0)
						mciSendString("pause MarioGameTheme", 0, 0, 0);
					else if (MusicFlag == 1)
						mciSendString("resume MarioGameTheme", 0, 0, 0);
				}

				else
				{
					if (MusicFlag == 0)
						mciSendString("pause MainTheme", 0, 0, 0);
					else if (MusicFlag == 1)
						mciSendString("resume MainTheme", 0, 0, 0);
				}
			}
		}

		//选择关卡
		else if (Botton == 6)
		{
			putimagePNG(NULL, 398, 292, &ChooseLevel_glow);
			if (status == 1)
			{
				if (page == "MarioMenu"|| page == "MarioGame")
				{
					EndBatchDraw();
				    return "ChooseLevel";
				}
			}
		}

		//切换账号
		else if (Botton == 7)
		{
			putimagePNG(NULL, 398, 378, &ChangeAccount_glow);
			if (status == 1)
			{
		        AccountMenu("SettingMenu");
				EndBatchDraw();
				continue;
			}
		}

		//查看排行榜
		else if (Botton == 8)
		{
			putimagePNG(NULL, 398, 438, &LeaderBoard_glow);
			if (status == 1)
			{
				/*EndBatchDraw();
				return "LeaderBoard";*/
			}
		}

		//返回
		else if (Botton == 9)
		{
			putimagePNG(NULL, 19, 26, &GoBack_glow);
			if (status == 1)
			{
				EndBatchDraw();
				return "GoBack";
			}
		}

		//退出应用
		else if (Botton == 10)
		{
			if (status == 1)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Tip.mp3", 0, 0, 0);
				}
				int windowChoice = MSGWindow("Sure", "Graph/MSGWindow/MSGExit.png");
				if (windowChoice != 2)
				{
					continue;
				}
				EndBatchDraw();
				exit(0);
			}
		}

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
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton1.mp3", 0, 0, 0);
				}			
				return 1;//有点击
			}
		}

		//五子棋
		else if (msg.x > 540 && msg.x < 725 && msg.y>70 && msg.y < 200)
		{
			RBotton = 10;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}			
				return 1;//有点击
			}
		}

		//马里奥
		else if (msg.x > 760 && msg.x < 945 && msg.y>70 && msg.y < 200)
		{
			RBotton = 20;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;//有点击
			}
		}

		//贪吃蛇
		else if (msg.x > 540 && msg.x < 725 && msg.y>230 && msg.y < 360)
		{
			RBotton = 30;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;//有点击
			}
		}

		//俄罗斯方块
		else if (msg.x > 760 && msg.x < 945 && msg.y>230 && msg.y < 360)
		{
			RBotton = 40;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;//有点击
			}
		}

		//退出应用
		else if (msg.x > 840 && msg.x < 955 && msg.y>500 && msg.y < 530)
		{
			RBotton = 50;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;//有点击
			}
		}

		//游戏设置
		else if (msg.x > 20 && msg.x < 60 && msg.y>480 && msg.y < 522)
		{
			RBotton = 60;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;//有点击
			}
		}

		//账户管理
		else if (msg.x > 70 && msg.x < 154 && msg.y>493 && msg.y < 520)
		{
			RBotton = 70;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
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
		//调节音量
		if (msg.x > 177 && msg.x < 327 && msg.y>206 && msg.y < 237)
		{
			Botton = 1;
			return 0;
		}

		//返回主菜单
		else if (msg.x > 177 && msg.x < 327 && msg.y>291 && msg.y < 323)
		{
			Botton = 2;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
		    }
		}

		//退出登录
		else if (msg.x > 177 && msg.x < 327 && msg.y>378 && msg.y < 410)
		{
			Botton = 3;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//游戏音效
		else if (msg.x > 398 && msg.x < 548 && msg.y>141 && msg.y < 173)
		{
			Botton = 4;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//背景音乐
		else if (msg.x > 398 && msg.x < 548 && msg.y>206 && msg.y < 238)
		{
			Botton = 5;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//选择关卡
		else if (msg.x > 398 && msg.x < 548 && msg.y>292 && msg.y < 324)
		{
			Botton = 6;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//切换账号
		else if (msg.x > 398 && msg.x < 548 && msg.y>378 && msg.y < 410)
		{
			Botton = 7;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//排行榜
		else if (msg.x > 398 && msg.x < 548 && msg.y>438 && msg.y < 470)
		{
			Botton = 8;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//返回
		else if (msg.x > 19 && msg.x < 80 && msg.y>26 && msg.y < 65)
		{
			Botton = 9;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//退出应用
		else if (msg.x > 837 && msg.x < 950 && msg.y>496 && msg.y < 523)
		{
			Botton = 10;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//无任何操作
		else
		{
		    Botton = 0;
			return 0;
        }	
	}

	//账户菜单交互
	else if (page == "AccountMenu")
	{
	    //未登录界面
	    if (IsLogin == 0)
	    {
			//返回
			if (msg.x > 21 && msg.x < 81 && msg.y>16 && msg.y < 55)
			{
				BottonAccount = 1;
				if (msg.message == WM_LBUTTONDOWN)
				{
					if (SoundFlag == 1)
					{
						mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
					}
					return 1;
				}
			}

			//登录/注册
			else if (msg.x > 345 && msg.x < 480 && msg.y>323 && msg.y < 353)
			{
				BottonAccount = 2;
				if (msg.message == WM_LBUTTONDOWN)
				{
					if (SoundFlag == 1)
					{
						mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
					}
					return 1;
				}
			}

			//遇到问题
			else if (msg.x > 532 && msg.x < 616 && msg.y>330 && msg.y < 346)
			{
				BottonAccount = 3;
				if (msg.message == WM_LBUTTONDOWN)
				{
					if (SoundFlag == 1)
					{
						mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
					}
					return 1;
				}
			}

			//注册账号
			else if (msg.x > 444 && msg.x < 516 && msg.y>428 && msg.y < 441)
			{
				BottonAccount = 4;
				if (msg.message == WM_LBUTTONDOWN)
				{
					if (SoundFlag == 1)
					{
						mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
					}
					return 1;
				}
			}

			//输入账号
			else if (msg.x > 374 && msg.x < 620 && msg.y>213 && msg.y < 243)
			{
				BottonAccount = 5;
				isscan = 1;
				if (msg.message == WM_LBUTTONDOWN)
				{
					if (SoundFlag == 1)
					{
						mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
					}
					return 1;
				}
			}

			//输入密码
			else if (msg.x > 374 && msg.x < 620 && msg.y>267 && msg.y < 295)
			{
				BottonAccount = 6;
				isscan = 1;
				if (msg.message == WM_LBUTTONDOWN)
				{
					if (SoundFlag == 1)
					{
						mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
					}
					return 1;
				}
			}

			//无操作
			else
			{
				BottonAccount = 0;
				return 0;
			}
		}

		//已登录界面
		if (IsLogin == 1)
		{
			//返回
			if (msg.x > 21 && msg.x < 81 && msg.y>16 && msg.y < 55)
			{
				BottonAccount = 1;
				if (msg.message == WM_LBUTTONDOWN)
				{
					if (SoundFlag == 1)
					{
						mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
					}
					return 1;
				}
			}

			//查看成就
			else if (msg.x > 353 && msg.x < 608 && msg.y>252 && msg.y < 359)
			{
				BottonAccount = 7;
				if (msg.message == WM_LBUTTONDOWN)
				{
					if (SoundFlag == 1)
					{
						mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
					}
					return 1;
				}
			}

			//退出登录
			else if (msg.x > 451 && msg.x < 508 && msg.y>420 && msg.y < 434)
			{
				BottonAccount = 8;
				if (msg.message == WM_LBUTTONDOWN)
				{
					if (SoundFlag == 1)
					{
						mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
					}
					return 1;
				}
			}

			//注销账户
			else if (msg.x > 451 && msg.x < 508 && msg.y>450 && msg.y < 464)
			{
				BottonAccount = 9;
				if (msg.message == WM_LBUTTONDOWN)
				{
					if (SoundFlag == 1)
					{
						mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
					}
					return 1;
				}
			}

			//无操作
			else
			{
				BottonAccount = 0;
				return 0;
			}
		}
	}

	//管理员菜单交互
	else if (page == "ManagerMenu")
	{
	    //返回
		if (msg.x > 21 && msg.x < 81 && msg.y>16 && msg.y < 55)
		{
			BottonManager = 1;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//删除1
		else if (msg.x > 680 && msg.x < 710 && msg.y>158 && msg.y < 188)
		{
			BottonManager = 21;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//编辑1
		else if (msg.x > 637 && msg.x < 667 && msg.y>158 && msg.y < 188)
		{
			BottonManager = 31;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//删除2
		else if (msg.x > 680 && msg.x < 710 && msg.y>209 && msg.y < 239)
		{
			BottonManager = 22;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//编辑2
		else if (msg.x > 637 && msg.x < 667 && msg.y>209 && msg.y < 239)
		{
			BottonManager = 32;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//删除3
		else if (msg.x > 680 && msg.x < 710 && msg.y>260 && msg.y < 290)
		{
			BottonManager = 23;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//编辑3
		else if (msg.x > 637 && msg.x < 667 && msg.y>260 && msg.y < 290)
		{
			BottonManager = 33;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//删除4
		else if (msg.x > 680 && msg.x < 710 && msg.y>311 && msg.y < 341)
		{
			BottonManager = 24;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//编辑4
		else if (msg.x > 637 && msg.x < 667 && msg.y>311 && msg.y < 341)
		{
		BottonManager = 34;
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (SoundFlag == 1)
			{
				mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
			}
			return 1;
		}
		}

		//删除5
		else if (msg.x > 680 && msg.x < 710 && msg.y>362 && msg.y < 392)
		{
			BottonManager = 25;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//编辑5
		else if (msg.x > 637 && msg.x < 667 && msg.y>362 && msg.y < 392)
		{
		    BottonManager = 35;
		    if (msg.message == WM_LBUTTONDOWN)
		    {
			    if (SoundFlag == 1)
			    {
				    mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
			    }
			    return 1;
		    }
		}

		//上一页
		else if (msg.x > 350 && msg.x < 396 && msg.y>483 && msg.y < 517)
		{
		    BottonManager = 4;
		    if (msg.message == WM_LBUTTONDOWN)
		    {
			    if (SoundFlag == 1)
			    {
				    mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
			    }
			    return 1;
		    }
		}

		//下一页
		else if (msg.x > 565 && msg.x < 612 && msg.y>483 && msg.y < 517)
		{
		    BottonManager = 5;
		    if (msg.message == WM_LBUTTONDOWN)
		    {
			    if (SoundFlag == 1)
			    {
				    mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
			    }
			    return 1;
		    }
		}

		//偏好设置
		else if (msg.x > 418 && msg.x < 541 && msg.y>449 && msg.y < 469)
		{
		    BottonManager = 6;
		    if (msg.message == WM_LBUTTONDOWN)
		    {
			    if (SoundFlag == 1)
			    {
				    mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
			    }
			    return 1;
		    }
		}

		//无操作
		else
		{
		    BottonManager = 0;
			return 0;
        }
    }

	//信息窗口交互
	else if (page == "MSGWindow")
	{
	    //左侧按钮
		if (msg.x > 357 && msg.x < 436 && msg.y>325 && msg.y < 352)
		{
			BottonWindow = 1;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//右侧按钮
		else if (msg.x > 498 && msg.x < 575 && msg.y>325 && msg.y < 352)
		{
			BottonWindow = 2;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;
			}
		}

		//无操作
		else
		{
			BottonWindow = 0;
			return 0;
		}
    }
	
    //无操作
	else
	{
		return 0;
	}
}

//主菜单
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
		loadimage(&Account, "Graph/MainMenu/Account.png"); loadimage(&Login, "Graph/MainMenu/Login.png");
		loadimage(&NotLogin, "Graph/MainMenu/NotLogin.png");
	}

	//播放背景音乐
	if (MusicFlag == 1)
	{
		mciSendString("open Audio/MainMenu/Theme.mp3 alias MainTheme", 0, 0, 0);
		mciSendString("play MainTheme repeat", 0, 0, 0);
	}

	//每次进入主菜单都更新登录状态
	if (IsLogin == 0 && Person != NULL)
	{
		delete Person;
		Person = NULL;
	}

	while (1)
	{
		int status = UserDO("MainMenu");

		BeginBatchDraw();
	
		putimagePNG(NULL, 0, 0, &mainBg); putimagePNG(NULL, 840, 500, &Exit);
		putimagePNG(NULL, 540, 70, &fiveChess); putimagePNG(NULL, 760, 70, &mario);
		putimagePNG(NULL, 760, 230, &russiaBlock); putimagePNG(NULL, 540, 230, &snake);
		putimagePNG(NULL, 20, 480, &Setting); 
		if(RBotton==70)putimagePNG(NULL, 70, 493, &Account);
		else
		{
			if (IsLogin == 1)putimagePNG(NULL, 70, 493, &Login);
			else putimagePNG(NULL, 70, 493, &NotLogin);
		}

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
				LoadingMenu();
				return "FiveChess";
			}
		}

		//马里奥
		else if (RBotton == 20)
		{
			putimagePNG(NULL, 760, 70, &mario_Glow);
			if (status == 1)
			{
				EndBatchDraw();
				LoadingMenu();
				return "Mario";
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
			if (SoundFlag == 1)
			{
				mciSendString("play Audio/MainMenu/Tip.mp3", 0, 0, 0);
			}
			int windowChoice = MSGWindow("Sure", "Graph/MSGWindow/MSGExit.png");
			if (windowChoice != 2)
			{
				continue;
			}
			EndBatchDraw();
			exit(0);
		}

		//游戏设置
		else if (RBotton == 60)
		{
			putimagePNG(NULL, 20, 480, &Setting_glow);
			if (status == 1)
			{
				string settingchoice = SettingMenu("MainMenu");

				//设置中选择返回主菜单
				if (settingchoice == "MainMenu"|| settingchoice == "LogOut")
				{
					EndBatchDraw();
					return "MainMenu";
				}

			}
		}

		//账户管理
		else if (RBotton == 70)
		{
			if (status == 1)
			{
				string accountchoice = AccountMenu("MainMenu");

				//设置中选择返回主菜单
				if (accountchoice == "MainMenu" || accountchoice == "LogOut")
				{
					EndBatchDraw();
					return "MainMenu";
				}
			}
		}

		EndBatchDraw();
	}
}

//加载页面
string SystemManager::LoadingMenu()
{
	//加载图片
	if (1)
	{
		loadimage(&LoadingMenuBg, "Graph/LoadMenu/LoadMenu.png"); loadimage(&LoadInfo1, "Graph/LoadMenu/Studio.png"); 
		loadimage(&LoadInfo2, "Graph/LoadMenu/Info.png"); loadimage(&LoadingMenuPic, "Graph/LoadMenu/LoadMenuPic.png");
		for (int i = 0; i < 8; i++)
		{
			string a = "Graph/LoadMenu/Stage" + to_string(i+1) + ".png";
			string b = "Graph/LoadMenu/" + to_string(i+1) + ".png";
			loadimage(LoadStage+i, a.c_str()); loadimage(LoadNum+i, b.c_str());
		}
	}

	for (int i = 0; i < 8; i++)
	{
		BeginBatchDraw();
		putimagePNG(NULL, 100, 0, LoadStage + i);
		putimagePNG(NULL, 0, 0, &LoadingMenuBg);
		putimagePNG(NULL, 322, 480, &LoadInfo1);
		putimagePNG(NULL, 322, 509, &LoadInfo2);		
		putimagePNG(NULL, 763, 488, LoadNum + i);
		EndBatchDraw();
		Sleep(LoadWait[i]);
	}

	return "OK";
}

//账户菜单
string SystemManager::AccountMenu(string page)
{
	//加载图片
	if (1)
	{
		loadimage(&Accountmenu, "Graph/AccountMenu/AccountMenu.png"); loadimage(&Account1, "Graph/AccountMenu/Account.png");
		loadimage(&Achievement, "Graph/AccountMenu/Achievement.png"); loadimage(&Achievement_glow, "Graph/AccountMenu/Achievement_glow.png");
		loadimage(&Avatar, "Graph/AccountMenu/Avatar.png"); loadimage(&CancelAccount, "Graph/AccountMenu/CancelAccount.png");
		loadimage(&CancelAccount_glow, "Graph/AccountMenu/CancelAccount_glow.png");  loadimage(&Login1, "Graph/AccountMenu/Login.png");
		loadimage(&Login_glow, "Graph/AccountMenu/Login_glow.png"); loadimage(&Logout, "Graph/AccountMenu/Logout.png");
		loadimage(&Logout_glow, "Graph/AccountMenu/Logout_glow.png"); loadimage(&Logout, "Graph/AccountMenu/Logout.png");
		loadimage(&Manager, "Graph/AccountMenu/Manager.png"); loadimage(&Password, "Graph/AccountMenu/Password.png"); loadimage(&bg, "Graph/AccountMenu/bg.png");
		loadimage(&Problem, "Graph/AccountMenu/Problem.png"); loadimage(&Problem_glow, "Graph/AccountMenu/Problem_glow.png");
		loadimage(&UserName, "Graph/AccountMenu/UserName.png"); loadimage(&UserName_glow, "Graph/AccountMenu/UserName_glow.png");
		loadimage(&Window, "Graph/AccountMenu/Window.png"); loadimage(&GoBack, "Graph/SettingMenu/GoBack.png"); loadimage(&GoBack_glow, "Graph/SettingMenu/GoBack_glow.png");
		loadimage(&Account1_glow, "Graph/AccountMenu/Account_glow.png"); loadimage(&Password_glow, "Graph/AccountMenu/Password_glow.png");
		loadimage(&EndScan, "Graph/AccountMenu/EndScan.png");
	}

	settextcolor(WHITE);
	settextstyle(24, 9, _T("Arial"));
	setbkmode(TRANSPARENT);
	LOGFONT textF;
	gettextstyle(&textF);
	textF.lfQuality= ANTIALIASED_QUALITY;

	while (1)
	{
		int status = UserDO("AccountMenu");

		if (nowOp == 2)
		{
			loadimage(&NowOp, "Graph/AccountMenu/ToLogin.png");
			loadimage(&NowOp_glow, "Graph/AccountMenu/ToLogin_glow.png");
			loadimage(&NowMSG, "Graph/AccountMenu/NowCreate.png");
		}
		else if (nowOp == 1)
		{
			loadimage(&NowOp, "Graph/AccountMenu/CreateAccount.png");
			loadimage(&NowOp_glow, "Graph/AccountMenu/CreateAccount_glow.png");
			loadimage(&NowMSG, "Graph/AccountMenu/NowLogin.png");
		}

		BeginBatchDraw();

		putimagePNG(NULL, 0, 0, &Accountmenu); putimagePNG(NULL, 102, 16, &Window); putimagePNG(NULL, 19, 26, &GoBack);
		putimagePNG(NULL, 423, 131, &Avatar); putimagePNG(NULL, 911, 498, &Manager); 
		if (IsLogin == 0)
		{
			putimagePNG(NULL, 351, 213, &Account1); putimagePNG(NULL, 351, 267, &Password);
			putimagePNG(NULL, 345, 323, &Login1); putimagePNG(NULL, 532, 330, &Problem);
			putimagePNG(NULL, 444, 428, &NowOp); putimagePNG(NULL, 423, 385, &NowMSG);
			outtextxy(395, 213, _T(Accountin.c_str())); outtextxy(395, 268, _T(Pwdin.c_str()));
		}
		else
		{
			 putimagePNG(NULL, 352, 252, &Achievement);
			putimagePNG(NULL, 452, 420, &Logout); putimagePNG(NULL, 452, 451, &CancelAccount);
			Accountin.clear(); Pwdin.clear(); outtextxy(478-5*(Person->m_Name.length()), 205, _T(Person->m_Name.c_str()));
		}

		//返回
		if (BottonAccount == 1)
		{
			putimagePNG(NULL, 19, 26, &GoBack_glow);
			if (status == 1)
			{
				nowOp = 1;
				EndBatchDraw();
				return "MainMenu";
			}
		}

		//登录/注册
		else if (BottonAccount == 2)
		{
			putimagePNG(NULL, 345, 323, &Login_glow);
			if (status == 1)
			{
				//用户输入为空
				if (Accountin.empty() || Pwdin.empty())
				{
					if (SoundFlag == 1)
					{
						mciSendString("play Audio/MainMenu/Tip.mp3", 0, 0, 0);
					}
					EndBatchDraw();
					MSGWindow("Wrong", "Graph/MSGWindow/MSGEmpty.png");
					continue;
				}

				//验证信息
				else
				{
					string MSGLogin = SystemLogin(Accountin, Pwdin, USER_FILE, nowOp);

					//文件不存在
					if (MSGLogin == "NoFile")
					{
						if (SoundFlag == 1)
						{
							mciSendString("play Audio/MainMenu/Tip.mp3", 0, 0, 0);
						}
						EndBatchDraw();
						MSGWindow("Wrong", "Graph/MSGWindow/MSGNoFile.png");
						continue;
					}

					//登录无匹配
					else if (MSGLogin == "NotMatch")
					{
						if (SoundFlag == 1)
						{
							mciSendString("play Audio/MainMenu/Tip.mp3", 0, 0, 0);
						}
						EndBatchDraw();
						MSGWindow("Wrong", "Graph/MSGWindow/MSGWrongpwd.png");
						continue;
					}

					//登录匹配
					else if (MSGLogin == "Match")
					{
						if (SoundFlag == 1)
						{
							mciSendString("play Audio/MainMenu/Tip1.mp3", 0, 0, 0);
						}
						IsLogin = 1;
						EndBatchDraw();
						MSGWindow("Success", "Graph/MSGWindow/MSGHasLogin.png");
						if (Accountin == "00000000" || Accountin == "Admin")
						{
							ShowInfo();
						}
						continue;
					}

					//注册重复
					else if (MSGLogin == "CreateRepeat")
					{
						if (SoundFlag == 1)
						{
							mciSendString("play Audio/MainMenu/Tip.mp3", 0, 0, 0);
						}
						EndBatchDraw();
						MSGWindow("Wrong", "Graph/MSGWindow/MSGUserName.png");
						continue;
					}

					//注册成功(返回值是Id)
					else 
					{
						if (SoundFlag == 1)
						{
							mciSendString("play Audio/MainMenu/Tip1.mp3", 0, 0, 0);
						}
						nowOp = 1;
						EndBatchDraw();
						MSGWindow("Success", "Graph/MSGWindow/MSGCreate.png");
						continue;
					}
				}
			}
		}

		//遇到问题
		else if (BottonAccount == 3)
		{
			putimagePNG(NULL, 532, 330, &Problem_glow);
			if (status == 1)
			{
				EndBatchDraw();
				//return "MainMenu";
			}
		}

		//注册/登录转换
		else if (BottonAccount == 4)
		{
			putimagePNG(NULL, 444, 428, &NowOp_glow);
			if (status == 1)
			{
				nowOp = nowOp == 1 ? 2 : 1;
				EndBatchDraw();
				continue;
			}
		}

		//输入账号
		else if (BottonAccount == 5)
		{
			if (status == 1)
			{
				putimagePNG(NULL, 351, 213, &Account1_glow);
				putimagePNG(NULL, 414, 192, &EndScan);
				char c;
				EndBatchDraw();
				while ((c = _getch()) != '\r')
				{
					if (c == '\b' && (!Accountin.empty()))
					{
						Accountin.pop_back();
						putimagePNG(NULL, 388, 213, &bg);
						outtextxy(395, 213, _T(Accountin.c_str()));
					}
					else if (c==27||c==9)
					{
						break;
					}
					else
					{
						if (Accountin.size() < 15 && c != '\b' && c != 32)
							Accountin += c;
					}
					putimagePNG(NULL, 388, 213, &bg);
					outtextxy(395, 213, _T(Accountin.c_str()));
				}
				
			}
		}

		//输入密码
		else if (BottonAccount == 6)
		{
			if (status == 1)
			{
				char c;
				putimagePNG(NULL, 351, 267, &Password_glow);
				putimagePNG(NULL, 414, 192, &EndScan);
				EndBatchDraw();
				while ((c = _getch()) != '\r')
				{
					if (c == '\b' && (!Pwdin.empty()))
					{
						Pwdin.pop_back();
						putimagePNG(NULL, 388, 266, &bg);
						outtextxy(395, 268, _T(Pwdin.c_str()));
					}
					else if (c == 27 || c == 9)
					{
						break;
					}
					else
					{
						if(Pwdin.size()<15 && c != '\b' && c != 32)
						    Pwdin += c;
					}
					putimagePNG(NULL, 388, 266, &bg);
					outtextxy(395, 268, _T(Pwdin.c_str()));
				}
				
				EndBatchDraw();
			}
		}

		//查看成就
		else if (BottonAccount == 7)
		{
			putimagePNG(NULL, 352, 252, &Achievement_glow);
			if (status == 1)
			{
				EndBatchDraw();
				//return "MainMenu";
			}
		}

		//退出登录
		else if (BottonAccount == 8)
		{
			putimagePNG(NULL, 452, 420, &Logout_glow);
			if (status == 1)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Tip.mp3", 0, 0, 0);
				}
				
				int windowChoice = MSGWindow("Sure", "Graph/MSGWindow/MSGIsLogout.png");
				if (windowChoice != 2)
				{
					continue;
				}

				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Tip1.mp3", 0, 0, 0);
				}
				IsLogin = 0;
				if (Person != NULL)
				{
					delete Person;
					Person = NULL;
				}
				MSGWindow("Success", "Graph/MSGWindow/MSGLogout.png");
				EndBatchDraw();
				continue;

				EndBatchDraw();
			}
		}

		//注销账户
		else if (BottonAccount == 9)
		{
			putimagePNG(NULL, 452, 451, &CancelAccount_glow);
			if (status == 1)
			{
				EndBatchDraw();
				//return "MainMenu";
			}
		}

		EndBatchDraw();
	}
}

//信息窗口
int SystemManager::MSGWindow(string page,const char* word)
{
	loadimage(&No, "Graph/MSGWindow/No.png"); loadimage(&Success, "Graph/MSGWindow/Success.png"); loadimage(&Sure, "Graph/MSGWindow/Sure.png"); loadimage(&No_glow, "Graph/MSGWindow/No_glow.png");
	loadimage(&Word, "Graph/MSGWindow/MSGLoss.png");loadimage(&Wrong, "Graph/MSGWindow/Wrong.png"); loadimage(&Yes, "Graph/MSGWindow/Yes.png"); loadimage(&Yes_glow, "Graph/MSGWindow/Yes_glow.png"); loadimage(&Word, word);

	//操作成功/失败窗口
	if (page == "Success" || page == "Wrong")
	{
		if (page == "Success")
		{
			putimagePNG(NULL, 276, 144, &Success);
		}

		else if (page == "Wrong")
		{
			putimagePNG(NULL, 276, 144, &Wrong);
		}
		putimagePNG(NULL, 389, 239, &Word);
		//putimagePNG(NULL, 357, 324, &Yes);

		Sleep(1000);
		return 0;
	}

	//操作确认窗口
	else if (page == "Sure")
	{
		putimagePNG(NULL, 276, 144, &Sure);
		putimagePNG(NULL, 389, 239, &Word);
		putimagePNG(NULL, 357, 324, &No);
		putimagePNG(NULL, 498, 324, &Yes);
		while (1)
		{
			int status = UserDO("MSGWindow");

			BeginBatchDraw();
			
			//点击取消
			if (BottonWindow == 1)
			{
				//putimagePNG(NULL, 357, 324, &No_glow);
				if (status == 1)
				{
					EndBatchDraw();
					return 1;
				}
			}

			//点击确认
			if (BottonWindow == 2)
			{
				//putimagePNG(NULL, 498, 324, &Yes_glow);
				if (status == 1)
				{
					EndBatchDraw();
					return 2;
				}
			}

			EndBatchDraw();
		}
	}

	else return 0;
}

//登录验证(type:1登录，2注册)
string SystemManager::SystemLogin(string name, string pwd, string filename, int type)
{
	ifstream ifs;
	ifs.open(filename, ios::in);

	//文件不存在
	if(!ifs.is_open())
	{
		ifs.close();
		return "NoFile";
	}

	//登录文件匹配
	if (type == 1)
	{
		string fId; string fName; string fPwd; int fVip = 0;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd && ifs >> fVip)
		{
			if ((name == fId || name == fName) && pwd == fPwd)
			{
				//管理员登录
				if (fId == "00000000")
				{
					Person = new SystemManager(fName, fPwd);
					ifs.close();
					return "Match";
				}

				//普通用户登录
				else
				{
					Person = new User(fId, fName, fPwd, fVip);
					ifs.close();
					return "Match";
				}
			}
		}
		ifs.close();
		return "NotMatch";
	}
	
	//注册文件匹配
	if (type == 2)
	{
		string fId; string fName; string fPwd; int fVip = 0;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd && ifs >> fVip)
		{
			//用户名重复
			if (name == fId || name == fName)
			{
				ifs.close();
				return "CreateRepeat";
			}
		}
		ifs.close();

	    //写入新用户
		ofstream ofs;

		ofs.open(filename, ios::out | ios::app);
		time_t now = time(0);
		//tm *ltm = localtime(&now);获取系统时间结构体
		string id = to_string(now % 100000000);
		ofs << id << " " << name << " " << pwd << " " << 0 << endl;
		ofs.close();
		return id;
	}
}

//显示信息(管理员窗口)
void SystemManager::ShowInfo()
{
	//加载图片
	if (1)
	{
		loadimage(&ManagerMenu, "Graph/ManagerMenu/ManagerMenu.png"); loadimage(&GoBack_glow, "Graph/SettingMenu/GoBack_glow.png");
		loadimage(&GoBack, "Graph/SettingMenu/GoBack.png"); loadimage(&Before, "Graph/ManagerMenu/Before.png");
		loadimage(&Before_glow, "Graph/ManagerMenu/Before_glow.png"); loadimage(&Next, "Graph/ManagerMenu/Next.png");
		loadimage(&Next_glow, "Graph/ManagerMenu/Next_glow.png"); loadimage(&Delete, "Graph/ManagerMenu/Delete.png");
		loadimage(&Delete_glow, "Graph/ManagerMenu/Delete_glow.png"); loadimage(&Edit, "Graph/ManagerMenu/Edit.png");
		loadimage(&Edit_glow, "Graph/ManagerMenu/Edit_glow.png"); loadimage(&Preference, "Graph/ManagerMenu/Preference.png");
		loadimage(&Preference_glow, "Graph/ManagerMenu/Preference_glow.png"); loadimage(&ShowPerson, "Graph/ManagerMenu/ShowPerson.png");
		loadimage(&bg, "Graph/AccountMenu/bg.png",347);
	}

	//设置字体
	settextcolor(WHITE);
	settextstyle(24, 9, _T("Arial"));
	setbkmode(TRANSPARENT);
	LOGFONT textF;
	gettextstyle(&textF);
	textF.lfQuality = ANTIALIASED_QUALITY;

	//读取所有用户
	ifstream ifs;
	ifs.open(USER_FILE, ios::in);

	//文件不存在
	if (!ifs.is_open())
	{
		ifs.close();
		if (SoundFlag == 1)
		{
			mciSendString("play Audio/MainMenu/Tip.mp3", 0, 0, 0);
		}
		MSGWindow("Wrong", "Graph/MSGWindow/MSGNoFile.png");
		return;
	}

	else
	{
		string fId; string fName; string fPwd; int fVip = 0;
		cnt = 0;//记录读取的条数
		User temp; UserInfo.clear();
		while (ifs >> fId && ifs >> fName && ifs >> fPwd && ifs >> fVip)
		{
			temp.m_Id = fId; temp.m_Name = fName; temp.m_Pwd = fPwd; temp.m_isVip = fVip;
			UserInfo.push_back(temp);
			cnt++;
		}
		ifs.close();
	}
	

	while (1)
	{
		int status = UserDO("ManagerMenu");

		BeginBatchDraw();

		putimagePNG(NULL, 0, 0, &ManagerMenu); putimagePNG(NULL, 19, 26, &GoBack);

		//打印用户信息
		for (int i = 1 + (Page - 1) * 5, j = 1; i <= cnt-1 && j <= 5; i++, j++)
		{
			string InfoT = UserInfo[i].m_Id + " " + UserInfo[i].m_Name;
			outtextxy(285, 155+(j-1)*51, _T(InfoT.c_str()));
		}

		//返回
		if (BottonManager == 1)
		{
			putimagePNG(NULL, 19, 26, &GoBack_glow);
			if (status == 1)
			{
				delete Person;
				Person = NULL;
				IsLogin = 0;
				EndBatchDraw();
				return;
			}
		}

		//删除
		else if (BottonManager >= 21 && BottonManager < 30)
		{
			putimagePNG(NULL, 680, 158 + (BottonManager - 21)*51, &Delete_glow);
			if (status == 1 && (BottonManager - 20) + (Page - 1) * 5 <= UserInfo.size() - 1)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Tip.mp3", 0, 0, 0);
				}
				int windowChoice = MSGWindow("Sure", "Graph/MSGWindow/MSGCancel.png");
				if (windowChoice != 2)
				{
					continue;
				}
				//重新写入文件
				DeleteAccount(BottonManager-20 + (Page - 1) * 5, USER_FILE);

				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Tip1.mp3", 0, 0, 0);
				}
				MSGWindow("Success", "Graph/MSGWindow/MSGHasDelete.png");
				putimagePNG(NULL, 285, 155, &bg); putimagePNG(NULL, 285, 206, &bg); putimagePNG(NULL, 285, 257, &bg);
			    putimagePNG(NULL, 285, 308, &bg); putimagePNG(NULL, 285, 359, &bg);
			}
		}

		//编辑
		else if (BottonManager >= 31 && BottonManager < 40)
		{
			putimagePNG(NULL, 637, 160 + (BottonManager - 31) * 51, &Edit_glow);
			if (status == 1)
			{
				
			}
		}

		//上一页
		else if (BottonManager == 4)
		{
			putimagePNG(NULL, 351, 483 , &Before_glow);
			if (status == 1)
			{
				if (Page >= 2)
				{
					Page--;
				}
			}
		}

		//下一页
		else if (BottonManager == 5)
		{
			putimagePNG(NULL, 567, 483, &Next_glow);
			if (status == 1)
			{
				if (Page <= (cnt-1)/5)
				{
					Page++;
				}
			}
		}

		//偏好设置
		else if (BottonManager == 6)
		{
			putimagePNG(NULL, 418, 449, &Preference_glow);
			if (status == 1)
			{

			}
		}

	    EndBatchDraw();	
	}
}

//删除账号
void SystemManager::DeleteAccount(int pos,string filename)
{
	UserInfo.erase(UserInfo.begin() + pos);
	ofstream ofs;
	ofs.open(filename, ios::trunc);

	for (vector<User>::iterator it = UserInfo.begin(); it != UserInfo.end(); it++)
	{
		ofs << it->m_Id << " " << it->m_Name << " " << it->m_Pwd << " " << it->m_isVip << endl;
	}
	ofs.close();

	//重新读入
	ifstream ifs;
	ifs.open(USER_FILE, ios::in);
	UserInfo.clear();

	string fId; string fName; string fPwd; int fVip = 0;
	cnt = 0;//记录读取的条数
	User temp; 

	while (ifs >> fId && ifs >> fName && ifs >> fPwd && ifs >> fVip)
	{
		temp.m_Id = fId; temp.m_Name = fName; temp.m_Pwd = fPwd; temp.m_isVip = fVip;
		UserInfo.push_back(temp);
		cnt++;
	}
	ifs.close();
}

//析构函数
SystemManager::~SystemManager()
{

}
