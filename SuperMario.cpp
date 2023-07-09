#include "SuperMario.h"

namespace
{
	MarioMap* gameMap = NULL;//当前加载的地图变量

	blockInfo tempInfo{"air",false,false,0};

	string NowLevelFile = "Graph/SuperMario/TileProject/LevelMap/Level1-1.tmj";
	string NowTileSet = "Graph/SuperMario/TileProject/MapSet.tsj";
	string NowTilePic = "Graph/SuperMario/TileProject/tileset.png";
	string ShowLevelX; string ShowLevelX_1;
	string ShowLevelY; string ShowLevelY_1;

	int NowDis = 0; int isGaming = 0; int NowLevel = 0;
	int Button = 0; int TVButton = 0; int isChoosing = 0;
	int LevelX = 1; int LevelY = 1; int GameButton = 0;

	//游戏菜单图片
	IMAGE TilePic; IMAGE ChooseLevel; IMAGE ChooseLevel_glow; IMAGE Coin; IMAGE Info; IMAGE Title;
	IMAGE MainMenu; IMAGE MainMenu_glow; IMAGE MarioMenu; IMAGE Power; IMAGE Power_glow;
	IMAGE Screen; IMAGE Setting; IMAGE Setting_glow; IMAGE Signal; IMAGE TV; IMAGE Num1_glow; IMAGE Num2_glow;
	IMAGE Start; IMAGE Start_glow; IMAGE Button_glow; IMAGE Bar; IMAGE BlackScreen; IMAGE Num3_glow;
	IMAGE Num1; IMAGE Num2; IMAGE Num3; IMAGE Level; IMAGE Click; IMAGE Angry; IMAGE Level_glow;

	//游戏内图片
	IMAGE BG; IMAGE Pause;

	//角色和生物
	Mario* mario;
}

//构造函数
SuperMario::SuperMario (string name)
{
	this->m_PlayerName = name;
}

//读取地图文件
char* SuperMario::getFileContent(const char* fileName)
{
	FILE* fp = fopen(fileName, "r");

	if (fp == NULL)
	{
		fclose(fp);
		return NULL;
	}

	//在堆存储字符串
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

//解析图块集
bool SuperMario::TileInit()
{
	char* content = getFileContent(NowTileSet.c_str());
	cJSON* tree = cJSON_Parse(content);
	
	//解析失败
	if (tree == NULL)
	{
		return false;
	}

	cJSON* node = cJSON_GetObjectItem(tree, "tilewidth");
	gameMap->tileSet.tileWidth = node->valueint; TileWid = gameMap->tileSet.tileWidth;
	gameMap->tileSet.tileHeight = cJSON_GetObjectItem(tree, "tileheight")->valueint; TileHei = gameMap->tileSet.tileHeight;
	gameMap->tileSet.margin = cJSON_GetObjectItem(tree, "margin")->valueint;
	gameMap->tileSet.tileCount = cJSON_GetObjectItem(tree, "tilecount")->valueint;
	gameMap->tileSet.row = cJSON_GetObjectItem(tree, "columns")->valueint;
	gameMap->tileSet.col = gameMap->tileSet.tileCount / gameMap->tileSet.row;

	cJSON_Delete(tree);
	free(content);
	return true;
}

//解析地图
bool SuperMario::MapInit()
{
	char* content= getFileContent(NowLevelFile.c_str());
	cJSON* tree = cJSON_Parse(content);

	//解析失败
	if (tree == NULL)
	{
		return false;
	}

	//cJSON_GetObjectItem获取指定节点的值
	cJSON* node = cJSON_GetObjectItem(tree, "width");
	gameMap->width = node->valueint; MapWid = gameMap->width;
	gameMap->height = cJSON_GetObjectItem(tree, "height")->valueint; MapHei = gameMap->height;
	cJSON* layer_node = cJSON_GetObjectItem(tree, "layers");
	gameMap->layerCount = cJSON_GetArraySize(layer_node);

	gameMap->layers = (layer*)malloc(sizeof(layer) * gameMap->layerCount);

	for (int i = 0; i < gameMap->layerCount; i++)
	{
		//获取图层数组的指定成员
		cJSON *layer=cJSON_GetArrayItem(layer_node, i);

		strcpy(gameMap->layers[i].name, cJSON_GetObjectItem(layer, "name")->valuestring);
		const char* type = cJSON_GetObjectItem(layer, "type")->valuestring;

		//解析图块层
		if (strcmp(type, "tilelayer") == 0)
		{
			gameMap->layers[i].type = 0;
			//data_node存储每个图块
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

		//解析对象层
		else if (strcmp(type, "objectgroup") == 0)
		{
			gameMap->layers[i].type = 1;
			//data_node存储每个图块
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

	//指定地图像素宽高
	gameMap->pixelWidth = gameMap->tileSet.tileWidth * gameMap->width;
	gameMap->pixelHeight = gameMap->tileSet.tileHeight * gameMap->height;

	cJSON_Delete(tree);
	free(content);

	return true;
}

//创建地图
void SuperMario::CreateMap()
{
	//碰撞图层容器初始化
	CollideVec.resize(gameMap->layers[0].height);
	for (int i = 0; i < gameMap->layers[0].height; i++)
	{
		CollideVec[i].resize(gameMap->layers[0].width);
	}

	//图片集提取图片
	loadimage(&TilePic, NowTilePic.c_str());
	SetWorkingImage(&TilePic);
	int Row = gameMap->tileSet.row; int Col = gameMap->tileSet.col;
	int margin = gameMap->tileSet.margin;

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

	for (int i = 0; i < gameMap->layerCount; i++)
	{
		//生物层作为辅助图层不显示
		if (!strcmp(gameMap->layers[i].name , "Creature"))
		{
			for (int row = 0; row < gameMap->layers[i].height; row++)
			{ 
				for (int col = 0; col < gameMap->layers[i].width; col++)
				{
					int index = gameMap->layers[i].tiles[row * gameMap->layers[i].width + col];
					if (index != 0)
					{
						//位置有板栗
						if (index == 456)
						{
							CreatureVec.push_back(ChestNut(row, col));
						}
						//位置有绿乌龟
						else if (index == 457)
						{
							CreatureVec.push_back(GreenTortoise(row, col));
						}
						//位置有飞行乌龟
						else if (index == 461)
						{
							CreatureVec.push_back(FlyTortoise(row, col));
						}
						//位置有花朵
						else if (index == 463)
						{
							CreatureVec.push_back(Flower(row, col));
						}
						//位置有蘑菇
						else if (index == 464)
						{
							CreatureVec.push_back(Mushroom(row, col));
						}
						//位置有问号砖
						else if (index == 465)
						{
							CreatureVec.push_back(QuestionBlock(row, col));
						}
						//位置有金币
						else if (index == 466)
						{
							CreatureVec.push_back(MarioCoin(row, col));
						}
						//位置有食人花
						else if (index == 504)
						{
							CreatureVec.push_back(Corpse(row, col));
						}
						//位置有旗子
						else if (index == 505)
						{
							CreatureVec.push_back(MarioFlag(row, col));
						}
					}
				}
			}
			continue;
		}
		gameMap->imgLayer[i].Resize(gameMap->pixelWidth, gameMap->pixelHeight);
		SetWorkingImage(&gameMap->imgLayer[i]);

		//对象层提取图片
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
					CollideVec[row][col].first = 1001;
					CollideVec[row][col].second = { "QuestionBrick",true,true,101 };
					loadimage(&imgObj, "Graph/SuperMario/unknown_brick_0.png");
				}
				else if (!strcmp(obj->type, "NormalBrick"))
				{
					CollideVec[row][col].first = 1002;
					CollideVec[row][col].second = { "NormalBrick",true,true,102 };
					loadimage(&imgObj, "Graph/SuperMario/brick_normal.png");
				}
				else if (!strcmp(obj->type, "HardBrick"))
				{
					CollideVec[row][col].first = 1003;
					CollideVec[row][col].second = { "HardBrick",true,true,103 };
					loadimage(&imgObj, "Graph/SuperMario/hard_brick.png");
				}
				putimage(x, y, &imgObj);
			}
		}

		//图块层提取图片
		else
		{
			for (int row = 0; row < gameMap->layers[i].height; row++)
			{
				for (int col = 0; col < gameMap->layers[i].width; col++)
				{
					int index = gameMap->layers[i].tiles[row * gameMap->layers[i].width + col];
					if (index == 0)
					{
						if (CollideVec[row][col].first == 0)
						{
							CollideVec[row][col].second = { "air",false,false,0 };
							continue;
						}						
						else continue;
					}
					if (!strcmp(gameMap->layers[i].name,"Ground")|| !strcmp(gameMap->layers[i].name ,"Barrier"))
					{
						CollideVec[row][col].first = 1;
						CollideVec[row][col].second = { "block",true,true,0 };
					}
					else if (!strcmp(gameMap->layers[i].name, "Environment") ||!strcmp(gameMap->layers[i].name, "Background"))
					{
						if (CollideVec[row][col].first == 0)
						{
							CollideVec[row][col].first = 2;
							CollideVec[row][col].second = { "Background",false,false,0 };
						}
					}
					IMAGE* img = &gameMap->imageTiles[index - 1];
					putimage(col * gameMap->tileSet.tileWidth, row * gameMap->tileSet.tileHeight, img);
				}
			}
		}

		SetWorkingImage();
	}
}

//创建图像
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

//用户交互
int SuperMario::UserDo(string page)
{
	//游戏内交互
	if (page == "Game")
	{
		ExMessage msg;

		//D键按下
		if (KEY_DOWN('D'))
		{
			mario->direction = 1;
			mario->m_X += 0.4;
			if (MapMov + 640 < gameMap->pixelWidth)
			{
				if (mario->m_X - MapMov > 640)
				{
					MapMov = mario->m_X - 640;
					gameMap->x = -int(MapMov);
				}
			}
			if (MarioStatus == 1)
			{
				mario->UpdateStatus(2);
			}
			return 0;
		}

		//A键按下
		else if (KEY_DOWN('A'))
		{
			mario->direction = 0;
			mario->m_X -= 0.4;
			if (MapMov > 0)
			{
				if (mario->m_X - MapMov < 320)
				{				
					MapMov = mario->m_X - 320;
					gameMap->x = -int(MapMov);
				}
			}
			if (MarioStatus == 1)
			{
				mario->UpdateStatus(2);
			}
			return 0;
		}

		//空格键按下
		else if (KEY_DOWN(' '))
		{
			mario->m_Y -= 0.2;
		}

		//P键按下
		else if (KEY_DOWN('P'))
		{
			GameButton = -1;
			if (SoundFlag == 1)
			{
				mciSendString("play Audio/MainMenu/Botton.mp3", 0, 0, 0);
			}
			return 1;
		}

		//没有按按键
		else
		{
			if (MarioStatus != 3 && MarioStatus != 5)
			{
				if (StaTimer >= 500)
				{
					mario->UpdateStatus(1);
					StaTimer = 0;
					return 0;
				}
			}
		}

		if (peekmessage(&msg))
		{
			//鼠标操作
			if (msg.message == WM_LBUTTONDOWN)
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

	//游戏菜单交互
	else if (page == "MarioMenu")
	{
		ExMessage msg;
		getmessage(&msg);

		//选择关卡
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

		//游戏设置
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

		//返回主菜单
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

		//电视天线
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

		//电视按钮上
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

		//电视按钮下
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

		//开始游戏
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

		//电视插头
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

		//无操作
		else
		{
			Button = 0;
			return 0;
		}
	}
}

//显示菜单
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

//运行游戏
void SuperMario::RunGame()
{
	//游戏菜单
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

		//加载图片
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

			//选择关卡
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

			//游戏设置
			else if (Button == 2)
			{
				putimagePNG(NULL, 39, 366, &Setting_glow);
				putimagePNG(NULL, 407, 362, &Coin);
				if (status == 1)
				{
					SystemManager* sm = new SystemManager("Admin", "123Cptbtptp");
					string settingchoice = sm->SettingMenu("MarioMenu");

					//设置中选择返回主菜单
					if (settingchoice == "MainMenu")
					{
						EndBatchDraw();
						delete sm;;
						mciSendString("pause MarioTheme", 0, 0, 0);
						return;
					}

					//设置中选择退出登录
					else if (settingchoice == "LogOut")
					{
						EndBatchDraw();
						delete sm;
						mciSendString("pause MarioTheme", 0, 0, 0);
						return;
					}

					//设置中选择选择关卡
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

			//返回主菜单
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

			//电视天线
			else if (Button == 4)
			{
				putimagePNG(NULL, 629, 36, &Signal);
				if (status == 1)
				{
					TVButton = TVButton == 0 ? 1 : 0;
				}
			}

			//开始游戏
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
					break;
				}
			}

			//电视插头
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

	//进入游戏
	if (isGaming == 1)
	{
		if (gameMap != NULL)
		{
			delete(gameMap);
			gameMap = NULL;
		}
		gameMap = new(MarioMap);

		//加载图片
		if (1)
		{
			loadimage(&BG, "Graph/SuperMario/BGBright.png");
			loadimage(&Pause, "Graph/SuperMario/Pause.png");
		}

		SystemManager* sm = new(SystemManager);
		sm->LoadingMenu();
		delete sm;

		TileInit();
		MapInit();
		CreateMap();
		
		mciSendString("pause MarioTheme", 0, 0, 0);
		if (MusicFlag == 1)
		{
			mciSendString("open Audio/SuperMario/main_Theme.mp3 alias MarioGameTheme", 0, 0, 0);
			mciSendString("seek MarioGameTheme to start", 0, 0, 0);
			mciSendString("play MarioGameTheme repeat", 0, 0, 0);
		}

		gameMap->x = 0;
		mario = new Mario;
		MarioStatus = 1;

		while (1)
		{
			int status = UserDo("Game");
			LastDelay = getDelay();
			AniTimer += LastDelay;
			StaTimer += LastDelay;
			IdleTimer += LastDelay;

			//动画帧变化
			if (AniTimer >= 100)
			{
				AniTimer = 0;
				gameIndex++;
				marioIndex++;
			}
			//待机帧变化
			if (IdleTimer >= 800)
			{
				IdleTimer = 0;
				idleIndex++;
			}

			BeginBatchDraw();

			mario->SpeedCal();
			putimagePNG(NULL, 0, 0, &BG);
			if(mario->isOnFloor)
			putimagePNG(NULL, 899, 19, &Pause);

			//打印每个图层
			for (int i = 0; i < gameMap->layerCount; i++)
			{
				putimagePNG(NULL, gameMap->x, 0, &gameMap->imgLayer[i]);
			}

			//打印马里奥
			mario->Render(mario->m_X-MapMov, mario->m_Y);


			//暂停游戏
			if (GameButton == -1)
			{
				SystemManager* sm = new SystemManager("Admin", "123Cptbtptp");
				string settingchoice = sm->SettingMenu("MarioGame");

				//设置中选择返回主菜单
				if (settingchoice == "MainMenu")
				{
					EndBatchDraw();
					isGaming = 0; GameButton = 0;
					delete sm;
					mciSendString("pause MarioGameTheme", 0, 0, 0);
					return;
				}

				//设置中选择退出登录
				else if (settingchoice == "LogOut")
				{
					EndBatchDraw();
					isGaming = 0; GameButton = 0;
					delete sm;
					mciSendString("pause MarioGameTheme", 0, 0, 0);
					return;
				}

				//设置中选择选择关卡
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

				//设置中选择返回
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

//析构函数
SuperMario::~SuperMario()
{

}
