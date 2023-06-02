#include "SystemManager.h"
#include "Transparent.h"
#include "Games.h"
#include "FiveChess.h"
#include"GlobalFile.h"
namespace
{
	//���˵�ͼƬ
	IMAGE mainBg; IMAGE gamePlayer; IMAGE castle; IMAGE Setting; IMAGE Setting_glow;
	IMAGE Select; IMAGE warning; IMAGE russiaBlock; IMAGE Account; IMAGE Login;
	IMAGE fiveChess; IMAGE mario; IMAGE snake; IMAGE Exit; IMAGE NotLogin;
	IMAGE russiaBlock_Glow; IMAGE fiveChess_Glow; IMAGE mario_Glow; IMAGE snake_Glow;

	//���ò˵�ͼƬ
	IMAGE AdjustVolume; IMAGE AdjustVolume_glow; IMAGE AudioRound; IMAGE BGM; IMAGE BGM_glow;
	IMAGE ChangeAccount; IMAGE ChangeAccount_glow; IMAGE ChooseLevel; IMAGE ChooseLevel_glow;
	IMAGE GameSound; IMAGE GameSound_glow; IMAGE GoBack; IMAGE GoMainMenu; IMAGE GoMainMenu_glow;
	IMAGE LeaderBoard; IMAGE LeaderBoard_glow; IMAGE LogOut; IMAGE LogOut_glow; IMAGE SettingMenuBg;
	IMAGE SystemVersion; IMAGE GoBack_glow;

	//�˻��˵�ͼƬ
	IMAGE Accountmenu; IMAGE Account1; IMAGE Achievement; IMAGE Achievement_glow; IMAGE Avatar;
	IMAGE CancelAccount; IMAGE CancelAccount_glow; IMAGE NowOp_glow; IMAGE NowMSG; IMAGE bg;
	IMAGE Login1; IMAGE Login_glow; IMAGE Logout; IMAGE Logout_glow; IMAGE Manager; IMAGE Password;
	IMAGE Problem; IMAGE Problem_glow; IMAGE UserName; IMAGE UserName_glow; IMAGE Window; IMAGE NowOp;
	IMAGE Account1_glow; IMAGE Password_glow; IMAGE EndScan;

	//��Ϣ����ͼƬ
	IMAGE No_glow;IMAGE No; IMAGE Yes; IMAGE Success; IMAGE Sure; 
	IMAGE Wrong; IMAGE Yes_glow; IMAGE Word;

	//����Ա�˵�ͼƬ
	IMAGE Before; IMAGE Before_glow; IMAGE Next; IMAGE Next_glow; IMAGE Delete; IMAGE Delete_glow;
	IMAGE Edit; IMAGE Edit_glow; IMAGE ManagerMenu; IMAGE Preference; IMAGE Preference_glow;
	IMAGE ShowPerson;

	//����ҳ��ͼƬ
	IMAGE LoadingMenuBg; IMAGE LoadInfo1; IMAGE LoadInfo2; IMAGE LoadStage[8]; IMAGE LoadNum[8];
	IMAGE LoadingMenuPic;

	//���˵�������
	int LBotton = 0; int RBotton = 0; 
	Identity* Person = NULL; int NowRank = 1;//��ǰ�û�ָ�롢��ǰ����

	//���ò˵�������
	int Botton = 0;
	int Xvolume = 293;//����ԲȦ����λ��

	//�˺Ų˵�������
	int BottonAccount = 0; int nowOp=1;//1��¼��2ע��
	string Accountin; string Pwdin;//�û�������˺�����
	int isscan = 0;

	//��Ϣ���ڿ�����
	int BottonWindow = 0;

	//����ҳ�������
	int LoadWait[8] = { 500,400,200,200,150,400,200,500 };

	//����Ա�˵�������
	int BottonManager = 0; vector<User>UserInfo;//�洢�����û���Ϣ
	int cnt = 0; int Page=1;//��ǰ��ȡ������ҳ��
}

int MusicFlag = 1;//�Ƿ񲥷�����
int SoundFlag = 1;//�Ƿ����Ϸ��Ч
int IsLogin = 0;//�Ƿ��¼

//Ĭ�Ϲ���
SystemManager::SystemManager()
{

}

//���캯��
SystemManager::SystemManager(string name,string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->m_isVip = 1;
}

//���ò˵�
string SystemManager::SettingMenu(string page)
{
	//����ͼƬ
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

		//��������
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

		//�������˵�
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

		//�˳���¼
		else if (Botton == 3)
		{
			putimagePNG(NULL, 177, 378, &LogOut_glow);
			if (status == 1)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Tip.mp3", 0, 0, 0);
				}

				//��ǰ�ѵ�¼
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

				//��ǰδ��¼
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

		//��Ϸ��Ч
		else if (Botton == 4)
		{
			putimagePNG(NULL, 398, 141, &GameSound_glow);
			if (status == 1)
			{
				SoundFlag = SoundFlag == 1 ? 0 : 1;
			}
		}

		//��������
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

		//ѡ��ؿ�
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

		//�л��˺�
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

		//�鿴���а�
		else if (Botton == 8)
		{
			putimagePNG(NULL, 398, 438, &LeaderBoard_glow);
			if (status == 1)
			{
				/*EndBatchDraw();
				return "LeaderBoard";*/
			}
		}

		//����
		else if (Botton == 9)
		{
			putimagePNG(NULL, 19, 26, &GoBack_glow);
			if (status == 1)
			{
				EndBatchDraw();
				return "GoBack";
			}
		}

		//�˳�Ӧ��
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

//�û�����
int SystemManager::UserDO(string page)
{
	ExMessage msg;
	getmessage(&msg);

	//���˵�����
	if (page == "MainMenu")
	{
		//��Ϸ���ͳǱ�
		if (msg.x > 180 && msg.x < 400 && msg.y>80 && msg.y < 250)
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				LBotton = (LBotton == 0) ? 10 : 0;
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton1.mp3", 0, 0, 0);
				}			
				return 1;//�е��
			}
		}

		//������
		else if (msg.x > 540 && msg.x < 725 && msg.y>70 && msg.y < 200)
		{
			RBotton = 10;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}			
				return 1;//�е��
			}
		}

		//�����
		else if (msg.x > 760 && msg.x < 945 && msg.y>70 && msg.y < 200)
		{
			RBotton = 20;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;//�е��
			}
		}

		//̰����
		else if (msg.x > 540 && msg.x < 725 && msg.y>230 && msg.y < 360)
		{
			RBotton = 30;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;//�е��
			}
		}

		//����˹����
		else if (msg.x > 760 && msg.x < 945 && msg.y>230 && msg.y < 360)
		{
			RBotton = 40;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;//�е��
			}
		}

		//�˳�Ӧ��
		else if (msg.x > 840 && msg.x < 955 && msg.y>500 && msg.y < 530)
		{
			RBotton = 50;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;//�е��
			}
		}

		//��Ϸ����
		else if (msg.x > 20 && msg.x < 60 && msg.y>480 && msg.y < 522)
		{
			RBotton = 60;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;//�е��
			}
		}

		//�˻�����
		else if (msg.x > 70 && msg.x < 154 && msg.y>493 && msg.y < 520)
		{
			RBotton = 70;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
				}
				return 1;//�е��
			}
		}

		else
		{
			RBotton = 0;
			return 0;//0��ʾδ�Ӵ��κν�����
		}
	}
	
	//���ò˵�����
	else if (page == "SettingMenu")
	{
		//��������
		if (msg.x > 177 && msg.x < 327 && msg.y>206 && msg.y < 237)
		{
			Botton = 1;
			return 0;
		}

		//�������˵�
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

		//�˳���¼
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

		//��Ϸ��Ч
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

		//��������
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

		//ѡ��ؿ�
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

		//�л��˺�
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

		//���а�
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

		//����
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

		//�˳�Ӧ��
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

		//���κβ���
		else
		{
		    Botton = 0;
			return 0;
        }	
	}

	//�˻��˵�����
	else if (page == "AccountMenu")
	{
	    //δ��¼����
	    if (IsLogin == 0)
	    {
			//����
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

			//��¼/ע��
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

			//��������
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

			//ע���˺�
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

			//�����˺�
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

			//��������
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

			//�޲���
			else
			{
				BottonAccount = 0;
				return 0;
			}
		}

		//�ѵ�¼����
		if (IsLogin == 1)
		{
			//����
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

			//�鿴�ɾ�
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

			//�˳���¼
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

			//ע���˻�
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

			//�޲���
			else
			{
				BottonAccount = 0;
				return 0;
			}
		}
	}

	//����Ա�˵�����
	else if (page == "ManagerMenu")
	{
	    //����
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

		//ɾ��1
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

		//�༭1
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

		//ɾ��2
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

		//�༭2
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

		//ɾ��3
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

		//�༭3
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

		//ɾ��4
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

		//�༭4
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

		//ɾ��5
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

		//�༭5
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

		//��һҳ
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

		//��һҳ
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

		//ƫ������
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

		//�޲���
		else
		{
		    BottonManager = 0;
			return 0;
        }
    }

	//��Ϣ���ڽ���
	else if (page == "MSGWindow")
	{
	    //��ఴť
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

		//�Ҳఴť
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

		//�޲���
		else
		{
			BottonWindow = 0;
			return 0;
		}
    }
	
    //�޲���
	else
	{
		return 0;
	}
}

//���˵�
string SystemManager::ShowMenu(int page)
{
	//���ر���ͼƬ
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

	//���ű�������
	if (MusicFlag == 1)
	{
		mciSendString("open Audio/MainMenu/Theme.mp3 alias MainTheme", 0, 0, 0);
		mciSendString("play MainTheme repeat", 0, 0, 0);
	}

	//ÿ�ν������˵������µ�¼״̬
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

		//��ӡ��Ϸ��
		if (LBotton == 0)
		{
		    putimagePNG(NULL, 140, 10, &gamePlayer);
		}

		//��ӡ�Ǳ�
		else if(LBotton == 10)
		{
			putimagePNG(NULL, 20, 1, &castle);
		}

		//������
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

		//�����
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

		//̰����
		else if (RBotton == 30)
		{
			putimagePNG(NULL, 540, 230, &snake_Glow);
			if (status == 1)
			{
				/*EndBatchDraw();
				return "Snake";*/
			}
		}

		//����˹����
		else if (RBotton == 40)
		{
			putimagePNG(NULL, 760, 230, &russiaBlock_Glow);
			if (status == 1)
			{
				/*EndBatchDraw();
				return "RussiaBlock";*/
			}
		}

		//�˳�Ӧ��
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

		//��Ϸ����
		else if (RBotton == 60)
		{
			putimagePNG(NULL, 20, 480, &Setting_glow);
			if (status == 1)
			{
				string settingchoice = SettingMenu("MainMenu");

				//������ѡ�񷵻����˵�
				if (settingchoice == "MainMenu"|| settingchoice == "LogOut")
				{
					EndBatchDraw();
					return "MainMenu";
				}

			}
		}

		//�˻�����
		else if (RBotton == 70)
		{
			if (status == 1)
			{
				string accountchoice = AccountMenu("MainMenu");

				//������ѡ�񷵻����˵�
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

//����ҳ��
string SystemManager::LoadingMenu()
{
	//����ͼƬ
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

//�˻��˵�
string SystemManager::AccountMenu(string page)
{
	//����ͼƬ
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

		//����
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

		//��¼/ע��
		else if (BottonAccount == 2)
		{
			putimagePNG(NULL, 345, 323, &Login_glow);
			if (status == 1)
			{
				//�û�����Ϊ��
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

				//��֤��Ϣ
				else
				{
					string MSGLogin = SystemLogin(Accountin, Pwdin, USER_FILE, nowOp);

					//�ļ�������
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

					//��¼��ƥ��
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

					//��¼ƥ��
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

					//ע���ظ�
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

					//ע��ɹ�(����ֵ��Id)
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

		//��������
		else if (BottonAccount == 3)
		{
			putimagePNG(NULL, 532, 330, &Problem_glow);
			if (status == 1)
			{
				EndBatchDraw();
				//return "MainMenu";
			}
		}

		//ע��/��¼ת��
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

		//�����˺�
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

		//��������
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

		//�鿴�ɾ�
		else if (BottonAccount == 7)
		{
			putimagePNG(NULL, 352, 252, &Achievement_glow);
			if (status == 1)
			{
				EndBatchDraw();
				//return "MainMenu";
			}
		}

		//�˳���¼
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

		//ע���˻�
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

//��Ϣ����
int SystemManager::MSGWindow(string page,const char* word)
{
	loadimage(&No, "Graph/MSGWindow/No.png"); loadimage(&Success, "Graph/MSGWindow/Success.png"); loadimage(&Sure, "Graph/MSGWindow/Sure.png"); loadimage(&No_glow, "Graph/MSGWindow/No_glow.png");
	loadimage(&Word, "Graph/MSGWindow/MSGLoss.png");loadimage(&Wrong, "Graph/MSGWindow/Wrong.png"); loadimage(&Yes, "Graph/MSGWindow/Yes.png"); loadimage(&Yes_glow, "Graph/MSGWindow/Yes_glow.png"); loadimage(&Word, word);

	//�����ɹ�/ʧ�ܴ���
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

	//����ȷ�ϴ���
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
			
			//���ȡ��
			if (BottonWindow == 1)
			{
				//putimagePNG(NULL, 357, 324, &No_glow);
				if (status == 1)
				{
					EndBatchDraw();
					return 1;
				}
			}

			//���ȷ��
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

//��¼��֤(type:1��¼��2ע��)
string SystemManager::SystemLogin(string name, string pwd, string filename, int type)
{
	ifstream ifs;
	ifs.open(filename, ios::in);

	//�ļ�������
	if(!ifs.is_open())
	{
		ifs.close();
		return "NoFile";
	}

	//��¼�ļ�ƥ��
	if (type == 1)
	{
		string fId; string fName; string fPwd; int fVip = 0;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd && ifs >> fVip)
		{
			if ((name == fId || name == fName) && pwd == fPwd)
			{
				//����Ա��¼
				if (fId == "00000000")
				{
					Person = new SystemManager(fName, fPwd);
					ifs.close();
					return "Match";
				}

				//��ͨ�û���¼
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
	
	//ע���ļ�ƥ��
	if (type == 2)
	{
		string fId; string fName; string fPwd; int fVip = 0;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd && ifs >> fVip)
		{
			//�û����ظ�
			if (name == fId || name == fName)
			{
				ifs.close();
				return "CreateRepeat";
			}
		}
		ifs.close();

	    //д�����û�
		ofstream ofs;

		ofs.open(filename, ios::out | ios::app);
		time_t now = time(0);
		//tm *ltm = localtime(&now);��ȡϵͳʱ��ṹ��
		string id = to_string(now % 100000000);
		ofs << id << " " << name << " " << pwd << " " << 0 << endl;
		ofs.close();
		return id;
	}
}

//��ʾ��Ϣ(����Ա����)
void SystemManager::ShowInfo()
{
	//����ͼƬ
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

	//��������
	settextcolor(WHITE);
	settextstyle(24, 9, _T("Arial"));
	setbkmode(TRANSPARENT);
	LOGFONT textF;
	gettextstyle(&textF);
	textF.lfQuality = ANTIALIASED_QUALITY;

	//��ȡ�����û�
	ifstream ifs;
	ifs.open(USER_FILE, ios::in);

	//�ļ�������
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
		cnt = 0;//��¼��ȡ������
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

		//��ӡ�û���Ϣ
		for (int i = 1 + (Page - 1) * 5, j = 1; i <= cnt-1 && j <= 5; i++, j++)
		{
			string InfoT = UserInfo[i].m_Id + " " + UserInfo[i].m_Name;
			outtextxy(285, 155+(j-1)*51, _T(InfoT.c_str()));
		}

		//����
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

		//ɾ��
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
				//����д���ļ�
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

		//�༭
		else if (BottonManager >= 31 && BottonManager < 40)
		{
			putimagePNG(NULL, 637, 160 + (BottonManager - 31) * 51, &Edit_glow);
			if (status == 1)
			{
				
			}
		}

		//��һҳ
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

		//��һҳ
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

		//ƫ������
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

//ɾ���˺�
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

	//���¶���
	ifstream ifs;
	ifs.open(USER_FILE, ios::in);
	UserInfo.clear();

	string fId; string fName; string fPwd; int fVip = 0;
	cnt = 0;//��¼��ȡ������
	User temp; 

	while (ifs >> fId && ifs >> fName && ifs >> fPwd && ifs >> fVip)
	{
		temp.m_Id = fId; temp.m_Name = fName; temp.m_Pwd = fPwd; temp.m_isVip = fVip;
		UserInfo.push_back(temp);
		cnt++;
	}
	ifs.close();
}

//��������
SystemManager::~SystemManager()
{

}
