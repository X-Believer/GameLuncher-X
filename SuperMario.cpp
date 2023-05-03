#include "SuperMario.h"

namespace
{
	//��������
	struct object
	{
		double x;
		double y;
		char* type;
		char* name;
	};

	//ÿ����ͼͼ��
	struct layer
	{
		char name[32];
		int* tiles;
		int width;
		int height;
		int type;
		//type:[0]ͼ��㣻[1]����㣻[2]ͼ���
		int objectsCount;
		object* objects;
	};

	//��ͼ��
	struct tileset
	{
		int tileWidth;
		int tileHeight;
		int margin;

		int row;
		int col;
		int tileCount;

		string tileFile;
	};

	//��ͼ
	struct MarioMap
	{
		int width;//��λ:ͼ��(42*42)
		int height;
		int pixelWidth;//���ؿ��
		int pixelHeight;
		int x;//��ͼλ��
		int y;

		struct tileset tileSet;
		struct layer* layers;//�洢ͼ����Ϣ
		int layerCount;

		IMAGE* imageTiles;//�洢ÿ��ͼ��ͼƬ
		IMAGE* imgLayer;//�洢ÿ��ͼ��ͼƬ
		IMAGE imgBg;
	};

	MarioMap* gameMap=NULL;//��ǰ���صĵ�ͼ����

	string NowLevelFile = "Graph/SuperMario/TileProject/LevelMap/Level1-1.tmj";
	string NowTileSet = "Graph/SuperMario/TileProject/MapSet.tsj";
	string NowTilePic = "Graph/SuperMario/TileProject/tileset.png";
	string ShowLevelX; string ShowLevelX_1;
	string ShowLevelY; string ShowLevelY_1;

	int NowDis = 0; int isGaming = 0; int NowLevel = 0;
	int Button = 0; int TVButton = 0; int isChoosing = 0;
	int LevelX = 1; int LevelY = 1; int GameButton = 0;

	//��Ϸ�˵�ͼƬ
	IMAGE TilePic; IMAGE ChooseLevel; IMAGE ChooseLevel_glow; IMAGE Coin; IMAGE Info; IMAGE Title;
	IMAGE MainMenu; IMAGE MainMenu_glow; IMAGE MarioMenu; IMAGE Power; IMAGE Power_glow;
	IMAGE Screen; IMAGE Setting; IMAGE Setting_glow; IMAGE Signal; IMAGE TV; IMAGE Num1_glow; IMAGE Num2_glow;
	IMAGE Start; IMAGE Start_glow; IMAGE Button_glow; IMAGE Bar; IMAGE BlackScreen; IMAGE Num3_glow;
	IMAGE Num1; IMAGE Num2; IMAGE Num3; IMAGE Level; IMAGE Click; IMAGE Angry; IMAGE Level_glow;

	//��Ϸ��ͼƬ
	IMAGE BG; IMAGE Pause;
}

//���캯��
SuperMario::SuperMario (string name)
{
	this->m_PlayerName = name;
}

//��ȡ��ͼ�ļ�
char* SuperMario::getFileContent(const char* fileName)
{
	FILE* fp = fopen(fileName, "r");

	if (fp == NULL)
	{
		fclose(fp);
		return NULL;
	}

	//�ڶѴ洢�ַ���
	fseek(fp, 0, SEEK_END);
	int len=ftell(fp);

	char* fileMsg = (char*)malloc(len + 1);
	fseek(fp, 0, SEEK_SET);
	char* p = fileMsg;

	while (1)
	{
		int ret=fread(p, sizeof(char), 1024, fp);
		if (ret <= 0)break;
		p += ret;
	}
	*p = '\0';
	fclose(fp);
	return fileMsg;
}

//����ͼ�鼯
bool SuperMario::TileInit()
{
	char* content = getFileContent(NowTileSet.c_str());
	cJSON* tree = cJSON_Parse(content);
	
	//����ʧ��
	if (tree == NULL)
	{
		return false;
	}

	cJSON* node = cJSON_GetObjectItem(tree, "tilewidth");
	gameMap->tileSet.tileWidth = node->valueint;
	gameMap->tileSet.tileHeight = cJSON_GetObjectItem(tree, "tileheight")->valueint;
	gameMap->tileSet.margin = cJSON_GetObjectItem(tree, "margin")->valueint;
	gameMap->tileSet.tileCount = cJSON_GetObjectItem(tree, "tilecount")->valueint;
	gameMap->tileSet.row = cJSON_GetObjectItem(tree, "columns")->valueint;
	gameMap->tileSet.col = gameMap->tileSet.tileCount / gameMap->tileSet.row;

	cJSON_Delete(tree);
	free(content);
	return true;
}

//������ͼ
bool SuperMario::MapInit()
{
	char* content= getFileContent(NowLevelFile.c_str());
	cJSON* tree = cJSON_Parse(content);

	//����ʧ��
	if (tree == NULL)
	{
		return false;
	}

	//cJSON_GetObjectItem��ȡָ���ڵ��ֵ
	cJSON* node = cJSON_GetObjectItem(tree, "width");
	gameMap->width=node->valueint;
	gameMap->height = cJSON_GetObjectItem(tree, "height")->valueint;
	cJSON* layer_node = cJSON_GetObjectItem(tree, "layers");
	gameMap->layerCount = cJSON_GetArraySize(layer_node);

	gameMap->layers = (layer*)malloc(sizeof(layer) * gameMap->layerCount);

	for (int i = 0; i < gameMap->layerCount; i++)
	{
		//��ȡͼ�������ָ����Ա
		cJSON *layer=cJSON_GetArrayItem(layer_node, i);

		strcpy(gameMap->layers[i].name, cJSON_GetObjectItem(layer, "name")->valuestring);
		const char* type = cJSON_GetObjectItem(layer, "type")->valuestring;

		//����ͼ���
		if (strcmp(type, "tilelayer") == 0)
		{
			gameMap->layers[i].type = 0;
			//data_node�洢ÿ��ͼ��
			cJSON* data_node = cJSON_GetObjectItem(layer, "data");
			gameMap->layers[i].height = cJSON_GetObjectItem(layer, "height")->valueint;
			gameMap->layers[i].width = cJSON_GetObjectItem(layer, "width")->valueint;
			int count = cJSON_GetArraySize(data_node);

			gameMap->layers[i].tiles = (int*)malloc(sizeof(int) * count);
			if (gameMap->layers[i].tiles == NULL)
			{
				cout << "No Memory!" << endl;
				return false;
			}
			for (int k = 0; k < count; k++)
			{
				gameMap->layers[i].tiles[k] = cJSON_GetArrayItem(data_node, k)->valueint;
			}
		}

		//���������
		else if (strcmp(type, "objectgroup") == 0)
		{
			gameMap->layers[i].type = 1;
			//data_node�洢ÿ��ͼ��
			cJSON* object_node = cJSON_GetObjectItem(layer, "objects");
			gameMap->layers[i].objectsCount = cJSON_GetArraySize(object_node);
			gameMap->layers[i].objects = (struct object*)malloc(sizeof(struct object) * gameMap->layers[i].objectsCount);
			
			for (int k = 0; k < gameMap->layers[i].objectsCount; k++)
			{
				cJSON* object = cJSON_GetArrayItem(object_node, k);
				strcpy(gameMap->layers[i].objects[k].type, cJSON_GetObjectItem(object, "class")->valuestring);
				strcpy(gameMap->layers[i].objects[k].name, cJSON_GetObjectItem(object, "name")->valuestring);
				gameMap->layers[i].objects[k].x = cJSON_GetObjectItem(object, "x")->valuedouble;
				gameMap->layers[i].objects[k].y = cJSON_GetObjectItem(object, "y")->valuedouble;
			}
		}
	}

	gameMap->pixelWidth = gameMap->tileSet.tileWidth * gameMap->width;
	gameMap->pixelHeight = gameMap->tileSet.tileHeight * gameMap->height;

	cJSON_Delete(tree);
	free(content);

	return true;
}

//������ͼ
void SuperMario::CreateMap()
{
	//ͼƬ����ȡͼƬ
	loadimage(&TilePic, NowTilePic.c_str());
	SetWorkingImage(&TilePic);
	int Row = gameMap->tileSet.row; int Col = gameMap->tileSet.col;
	int margin = gameMap->tileSet.margin;

	gameMap->imageTiles = new IMAGE[gameMap->tileSet.tileCount];
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			getimage(&gameMap->imageTiles[i * Col + j], margin + j * gameMap->tileSet.tileWidth,
				margin + i * gameMap->tileSet.tileHeight, gameMap->tileSet.tileWidth,
				gameMap->tileSet.tileHeight);
		}
	}
	SetWorkingImage();

	gameMap->imgLayer = new IMAGE[gameMap->layerCount];

	if (gameMap->imgLayer == NULL)cout << "?";
	for (int i = 0; i < gameMap->layerCount; i++)
	{
		gameMap->imgLayer[i].Resize(gameMap->pixelWidth, gameMap->pixelHeight);
		SetWorkingImage(&gameMap->imgLayer[i]);

		//�������ȡͼƬ
		if(gameMap->layers[i].type==1)
		{
			for (int k = 0; k < gameMap->layers[i].objectsCount; k++)
			{
				struct object* obj = &gameMap->layers[i].objects[k];
				int row = obj->y / gameMap->tileSet.tileHeight;
				int col = obj->x / gameMap->tileSet.tileWidth;
				int x = col * gameMap->tileSet.tileWidth;
				int y = row * gameMap->tileSet.tileHeight;

				IMAGE imgObj;
				if (!strcmp(obj->type, "QuestionBrick"))
				{
					loadimage(&imgObj, "Graph/SuperMario/unknown_brick_0.png");
				}
				else if (!strcmp(obj->type, "NormalBrick"))
				{
					loadimage(&imgObj, "Graph/SuperMario/brick_normal.png");
				}
				else if (!strcmp(obj->type, "HardBrick"))
				{
					loadimage(&imgObj, "Graph/SuperMario/hard_brick.png");
				}

				putimage(x, y, &imgObj);
			}
		}

		//ͼ�����ȡͼƬ
		else
		{
			for (int row = 0; row < gameMap->layers[i].height; row++)
			{
				for (int col = 0; col < gameMap->layers[i].width; col++)
				{
					int index = gameMap->layers[i].tiles[row * gameMap->layers[i].width + col];
					if (index == 0)continue;
					IMAGE* img = &gameMap->imageTiles[index - 1];
					putimage(col * gameMap->tileSet.tileWidth, row * gameMap->tileSet.tileHeight, img);
				}
			}
		}

		SetWorkingImage();
	}
}

//����ͼ��
void SuperMario::CreateImgLine(IMAGE* img, const char* name)
{
	IMAGE imgLine, imgLine2;
	loadimage(&imgLine, name);
	float k = imgLine.getheight() * 1.0 / img->getheight();
	loadimage(&imgLine2, name, imgLine.getwidth() / k, img->getheight(), true);

	int w = imgLine2.getwidth();
	SetWorkingImage(img);
	for (int x = 0; x < img->getwidth(); x += w)
	{
		putimage(x, 0, &imgLine2);
	}
	SetWorkingImage();
}

//�û�����
int SuperMario::UserDo(string page)
{
	//��Ϸ�ڽ���
	if (page == "Game")
	{
		ExMessage msg;

		if (peekmessage(&msg))
		{
			//���̲���
			if (msg.message == WM_KEYDOWN)
			{
				char c = _getch();

				//D������
				if (c == 'd')
				{
					if (gameMap->x - 8 > -(gameMap->pixelWidth - 960))
					{
						gameMap->x -= 8;
					}
					else if (gameMap->x - 8 < -(gameMap->pixelWidth - 960))
					{
						gameMap->x = -(gameMap->pixelWidth - 960);
					}
					return 0;
				}

				//A������
				if (c == 'a')
				{
					if (gameMap->x + 8 < 0)
					{
						gameMap->x += 8;
					}
					else if (gameMap->x + 8 > 0)
					{
						gameMap->x = 0;
					}
					return 0;
				}
			}

			//������
			else if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.x > 900 && msg.x < 940 && msg.y>19 && msg.y < 71)
				{
					GameButton = -1;
					if (SoundFlag == 1)
					{
						mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
					}
					return 1;
				}
			}
			
		}
		return 0;
	}

	//��Ϸ�˵�����
	else if (page == "MarioMenu")
	{
		ExMessage msg;
		getmessage(&msg);

		//ѡ��ؿ�
		if (msg.x > 39 && msg.x < 360 && msg.y>312 && msg.y < 340)
		{
			Button = 1;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/SuperMario/Button/Tip2.mp3", 0, 0, 0);
				}
				isChoosing = isChoosing == 0 ? 1 : 0;
				return 1;
			}
			return 0;
		}

		//��Ϸ����
		else if (msg.x > 39 && msg.x < 360 && msg.y>366 && msg.y < 394)
		{
			Button = 2;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/SuperMario/Button/Tip2.mp3", 0, 0, 0);
				}
				return 1;
			}
			return 0;
		}

		//�������˵�
		else if (msg.x > 39 && msg.x < 360 && msg.y>420 && msg.y < 448)
		{
			Button = 3;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/SuperMario/Button/Tip2.mp3", 0, 0, 0);
				}
				return 1;
			}
			return 0;
		}

		//��������
		else if (msg.x > 629 && msg.x < 797 && msg.y>36 && msg.y < 124)
		{
			Button = 4;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/SuperMario/Button/Tip2.mp3", 0, 0, 0);
				}
				putimagePNG(NULL, 559, 160, &Screen);
				Sleep(500);
			
				return 1;
			}
			return 0;
		}

		//���Ӱ�ť��
		else if (isChoosing == 1 && msg.x > 867 && msg.x < 941 && msg.y>264 && msg.y < 284)
		{
			Button = 5;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/SuperMario/Button/Tip1.mp3", 0, 0, 0);
				}
				
				LevelX++;
				if (LevelX > 9)LevelX = 1;
				ShowLevelX = "Graph/SuperMario/MarioMenu/" + to_string(LevelX) + ".png";
				ShowLevelX_1 = "Graph/SuperMario/MarioMenu/" + to_string(LevelX) + "_glow.png";
				NowLevel = (LevelX - 1) * 10 + LevelY;
				
				return 1;
			}
			return 0;
		}

		//���Ӱ�ť��
		else if (isChoosing == 1 && msg.x > 867 && msg.x < 941 && msg.y>299 && msg.y < 319)
		{
			Button = 6;
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (SoundFlag == 1)
				{
					mciSendString("play Audio/SuperMario/Button/Tip1.mp3", 0, 0, 0);
				}
				
				LevelY++;
				if (LevelY > 9)LevelY = 1;
				ShowLevelY = "Graph/SuperMario/MarioMenu/"+to_string(LevelY)+".png";
				ShowLevelY_1 = "Graph/SuperMario/MarioMenu/" + to_string(LevelY) + "_glow.png";
				NowLevel = (LevelX - 1) * 10 + LevelY;

				return 1;
			}
			return 0;
		}

		//��ʼ��Ϸ
		else if (isChoosing == 1 && msg.x > 620 && msg.x < 770 && msg.y>209 && msg.y < 311)
		{
		Button = 7;
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (SoundFlag == 1)
			{
				mciSendString("play Audio/SuperMario/Button/Tip1.mp3", 0, 0, 0);
			}
			return 1;
		}
		return 0;
		}

		//���Ӳ�ͷ
		else if (msg.x > 867 && msg.x < 960 && msg.y>369 && msg.y < 501)
		{
		Button = 8;
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (SoundFlag == 1)
			{
				mciSendString("play Audio/SuperMario/Button/Tip1.mp3", 0, 0, 0);
			}
			putimagePNG(NULL, 620, 209, &BlackScreen);
			putimagePNG(NULL, 636, 198, &Angry);
			Sleep(500);
			return 1;
		}
		return 0;
		}

		//�޲���
		else
		{
			Button = 0;
			return 0;
		}
	}
}

//��ʾ�˵�
void SuperMario::ShowGameMenu()
{
	putimagePNG(NULL, 0, 0, &MarioMenu);
	putimagePNG(NULL, 39, 50, &Title);
	putimagePNG(NULL, 39, 312, &ChooseLevel);
	putimagePNG(NULL, 39, 366, &Setting);
	putimagePNG(NULL, 39, 420, &MainMenu);
	putimagePNG(NULL, 39, 506, &Info);
	putimagePNG(NULL, 512, 37, &TV);
	putimagePNG(NULL, 868, 370, &Power);
}

//������Ϸ
void SuperMario::RunGame()
{
	//��Ϸ�˵�
	if (isGaming == 0)
	{
		mciSendString("pause MainTheme", 0, 0, 0);
		if (MusicFlag == 1)
		{
			mciSendString("open Audio/SuperMario/start.mp3 alias MarioTheme", 0, 0, 0);
			mciSendString("seek MarioTheme to start", 0, 0, 0);
			mciSendString("play MarioTheme repeat", 0, 0, 0);
		}
		ShowLevelX = "Graph/SuperMario/MarioMenu/1.png"; ShowLevelY = "Graph/SuperMario/MarioMenu/1.png";
		ShowLevelX_1 = "Graph/SuperMario/MarioMenu/1_glow.png"; ShowLevelY_1 = "Graph/SuperMario/MarioMenu/1_glow.png";

		settextcolor(WHITE);
		settextstyle(24, 9, _T("Arial"));
		setbkmode(TRANSPARENT);
		LOGFONT textF;
		gettextstyle(&textF);
		textF.lfQuality = ANTIALIASED_QUALITY;

		NowDis = 0; NowLevel = 0; NowLevelFile.clear();
		Button = 0; TVButton = 0; isChoosing = 0;
		LevelX = 1; LevelY = 1; GameButton = 0;

		//����ͼƬ
		if (1)
		{
			loadimage(&ChooseLevel, "Graph/SuperMario/MarioMenu/ChooseLevel.png"); loadimage(&ChooseLevel_glow, "Graph/SuperMario/MarioMenu/ChooseLevel_glow.png");
			loadimage(&Coin, "Graph/SuperMario/MarioMenu/Coin.png"); loadimage(&Info, "Graph/SuperMario/MarioMenu/Info.png"); loadimage(&MainMenu, "Graph/SuperMario/MarioMenu/MainMenu.png");
			loadimage(&MainMenu_glow, "Graph/SuperMario/MarioMenu/MainMenu_glow.png"); loadimage(&MarioMenu, "Graph/SuperMario/MarioMenu/MarioMenu.png");
			loadimage(&Power, "Graph/SuperMario/MarioMenu/Power.png"); loadimage(&Power_glow, "Graph/SuperMario/MarioMenu/Power_glow.png"); loadimage(&Screen, "Graph/SuperMario/MarioMenu/Screen.png");
			loadimage(&Setting, "Graph/SuperMario/MarioMenu/Setting.png"); loadimage(&Setting_glow, "Graph/SuperMario/MarioMenu/Setting_glow.png");
			loadimage(&Signal, "Graph/SuperMario/MarioMenu/Signal.png"); loadimage(&Start, "Graph/SuperMario/MarioMenu/Start.png"); loadimage(&Start_glow, "Graph/SuperMario/MarioMenu/Start_glow.png");
			loadimage(&Title, "Graph/SuperMario/MarioMenu/Title.png"); loadimage(&TV, "Graph/SuperMario/MarioMenu/TV.png"); loadimage(&Button_glow, "Graph/SuperMario/MarioMenu/Button_glow.png");
			loadimage(&BlackScreen, "Graph/SuperMario/MarioMenu/BlackScreen.png"); loadimage(&Bar, "Graph/SuperMario/MarioMenu/Bar.png"); loadimage(&Num1, "Graph/SuperMario/MarioMenu/5.png");
			loadimage(&Num3, "Graph/SuperMario/MarioMenu/-.png"); loadimage(&Level, "Graph/SuperMario/MarioMenu/Level.png"); loadimage(&Num2, "Graph/SuperMario/MarioMenu/5.png");
			loadimage(&Click, "Graph/SuperMario/MarioMenu/Click.png"); loadimage(&Angry, "Graph/SuperMario/MarioMenu/Angry.png"); loadimage(&Level_glow, "Graph/SuperMario/MarioMenu/Level_glow.png");
			loadimage(&Num1_glow, "Graph/SuperMario/MarioMenu/5_glow.png"); loadimage(&Num2_glow, "Graph/SuperMario/MarioMenu/5_glow.png"); loadimage(&Num3_glow, "Graph/SuperMario/MarioMenu/-_glow.png");
		}

		while (1)
		{
			int status = UserDo("MarioMenu");

			BeginBatchDraw();

			ShowGameMenu();

			if (isChoosing == 1)
			{
				loadimage(&Num1, ShowLevelX.c_str()); loadimage(&Num2, ShowLevelY.c_str());
				loadimage(&Num1_glow, ShowLevelX_1.c_str()); loadimage(&Num2_glow, ShowLevelY_1.c_str());

				putimagePNG(NULL, 39, 310, &Bar);
				putimagePNG(NULL, 39, 312, &Level);
				putimagePNG(NULL, 867, 264, &Button_glow);
				putimagePNG(NULL, 867, 299, &Button_glow);
				putimagePNG(NULL, 873, 239, &Click);
				putimagePNG(NULL, 189, 312, &Num1);
				putimagePNG(NULL, 245, 312, &Num2);
				putimagePNG(NULL, 217, 324, &Num3);
				putimagePNG(NULL, 620, 209, &Start);
			}

			//ѡ��ؿ�
			if (Button == 1)
			{
				putimagePNG(NULL, 407, 308, &Coin);
				if (isChoosing == 0)
				{
					putimagePNG(NULL, 39, 310, &Bar);
					putimagePNG(NULL, 39, 312, &ChooseLevel_glow);
				}
				else if (isChoosing == 1)
				{
					putimagePNG(NULL, 39, 312, &Level_glow);
					putimagePNG(NULL, 189, 312, &Num1_glow);
					putimagePNG(NULL, 245, 312, &Num2_glow);
					putimagePNG(NULL, 217, 324, &Num3_glow);
				}
			}

			//��Ϸ����
			else if (Button == 2)
			{
				putimagePNG(NULL, 39, 366, &Setting_glow);
				putimagePNG(NULL, 407, 362, &Coin);
				if (status == 1)
				{
					SystemManager* sm = new SystemManager("Admin", "123Cptbtptp");
					string settingchoice = sm->SettingMenu("MarioMenu");

					//������ѡ�񷵻����˵�
					if (settingchoice == "MainMenu")
					{
						EndBatchDraw();
						delete sm;;
						mciSendString("pause MarioTheme", 0, 0, 0);
						return;
					}

					//������ѡ���˳���¼
					else if (settingchoice == "LogOut")
					{
						EndBatchDraw();
						delete sm;
						mciSendString("pause MarioTheme", 0, 0, 0);
						return;
					}

					//������ѡ��ѡ��ؿ�
					else if (settingchoice == "ChooseLevel")
					{
						isChoosing = isChoosing == 0 ? 1 : 0;
						EndBatchDraw();
						delete sm;
						continue;
					}

					delete sm;
				}
			}

			//�������˵�
			else if (Button == 3)
			{
				putimagePNG(NULL, 39, 420, &MainMenu_glow);
				putimagePNG(NULL, 407, 416, &Coin);
				if (status == 1)
				{
					EndBatchDraw();
					mciSendString("pause MarioTheme", 0, 0, 0);
					return;
				}
			}

			//��������
			else if (Button == 4)
			{
				putimagePNG(NULL, 629, 36, &Signal);
				if (status == 1)
				{
					TVButton = TVButton == 0 ? 1 : 0;
				}
			}

			//��ʼ��Ϸ
			else if (isChoosing == 1 && Button == 7)
			{
				putimagePNG(NULL, 620, 209, &Start_glow);
				if (status == 1)
				{
					NowLevelFile= "Graph/SuperMario/TileProject/LevelMap/Level"+to_string(LevelX)+"-"+ to_string(LevelY)+".tmj";
					FILE* fp = fopen(NowLevelFile.c_str(), "r");

					if (fp == NULL)
					{
						continue;
					}
					else
					{
						fclose(fp);
					}

					isGaming = 1;
					mciSendString("pause MarioTheme", 0, 0, 0);
					break;
				}
			}

			//���Ӳ�ͷ
			else if (Button == 8)
			{
				putimagePNG(NULL, 867, 369, &Power_glow);
			}

			if (isGaming == 1)
			{
				EndBatchDraw();
				break;
			}
			EndBatchDraw();
		}
	}

	//������Ϸ
	if (isGaming == 1)
	{
		if (gameMap != NULL)
		{
			delete(gameMap);
			gameMap = NULL;
		}

		gameMap = new(MarioMap);

		if (MusicFlag == 1)
		{
			mciSendString("open Audio/SuperMario/main_Theme.mp3 alias MarioGameTheme", 0, 0, 0);
			mciSendString("seek MarioGameTheme to start", 0, 0, 0);
			mciSendString("play MarioGameTheme repeat", 0, 0, 0);
		}

		//����ͼƬ
		if (1)
		{
			loadimage(&BG, "Graph/SuperMario/BGBright.png");
			loadimage(&Pause, "Graph/SuperMario/Pause.png");
		}

		TileInit();
		MapInit();
		CreateMap();

		gameMap->x = 0;

		while (1)
		{
			int status = UserDo("Game");
			BeginBatchDraw();

			putimagePNG(NULL, 0, 0, &BG);
			putimagePNG(NULL, 899, 19, &Pause);

			//��ӡÿ��ͼ��
			for (int i = 0; i < gameMap->layerCount; i++)
			{
				putimagePNG(NULL, gameMap->x, 0, &gameMap->imgLayer[i]);
			}

			//��ͣ��Ϸ
			if (GameButton == -1)
			{
				SystemManager* sm = new SystemManager("Admin", "123Cptbtptp");
				string settingchoice = sm->SettingMenu("MarioGame");

				//������ѡ�񷵻����˵�
				if (settingchoice == "MainMenu")
				{
					EndBatchDraw();
					isGaming = 0; GameButton = 0;
					delete sm;
					mciSendString("pause MarioGameTheme", 0, 0, 0);
					return;
				}

				//������ѡ���˳���¼
				else if (settingchoice == "LogOut")
				{
					EndBatchDraw();
					isGaming = 0; GameButton = 0;
					delete sm;
					mciSendString("pause MarioGameTheme", 0, 0, 0);
					return;
				}

				//������ѡ��ѡ��ؿ�
				else if (settingchoice == "ChooseLevel")
				{
					isChoosing = 1;
					isGaming = 0; GameButton = 0;
					EndBatchDraw();
					delete sm;
					mciSendString("pause MarioGameTheme", 0, 0, 0);
					RunGame();
					return;
				}

				//������ѡ�񷵻�
				else if (settingchoice == "GoBack")
				{
					GameButton = 0;
					EndBatchDraw();
					delete sm;
				}

				else
				{
					delete sm;
				}
			}

			EndBatchDraw();
		}

		return;
	}
}

//��������
SuperMario::~SuperMario()
{

}
