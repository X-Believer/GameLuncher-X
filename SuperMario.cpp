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

	MarioMap gameMap;//��ǰ���صĵ�ͼ����

	string NowLevel = "Graph/SuperMario/TileProject/LevelMap/Level1-1.tmj";
	string NowTileSet = "Graph/SuperMario/TileProject/MapSet.tsj";
	string NowTilePic = "Graph/SuperMario/TileProject/tileset.png";

	int NowDis = 0; int isGaming = 0; int NowLevel = 0;
	int Button = 0; int TVButton = 0;

	IMAGE TilePic; IMAGE ChooseLevel; IMAGE ChooseLevel_glow; IMAGE Coin; IMAGE Info; IMAGE Title;
	IMAGE MainMenu; IMAGE MainMenu_glow; IMAGE MarioMenu; IMAGE Power; IMAGE Power_glow;
	IMAGE Screen; IMAGE Setting; IMAGE Setting_glow; IMAGE Signal; IMAGE TV;
	IMAGE Start; IMAGE Start_glow;
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
	gameMap.tileSet.tileWidth = node->valueint;
	gameMap.tileSet.tileHeight = cJSON_GetObjectItem(tree, "tileheight")->valueint;
	gameMap.tileSet.margin = cJSON_GetObjectItem(tree, "margin")->valueint;
	gameMap.tileSet.tileCount = cJSON_GetObjectItem(tree, "tilecount")->valueint;
	gameMap.tileSet.row = cJSON_GetObjectItem(tree, "columns")->valueint;
	gameMap.tileSet.col = gameMap.tileSet.tileCount / gameMap.tileSet.row;

	cJSON_Delete(tree);
	free(content);
	return true;
}

//������ͼ
bool SuperMario::MapInit()
{
	char* content= getFileContent(NowLevel.c_str());
	cJSON* tree = cJSON_Parse(content);

	//����ʧ��
	if (tree == NULL)
	{
		return false;
	}

	//cJSON_GetObjectItem��ȡָ���ڵ��ֵ
	cJSON* node = cJSON_GetObjectItem(tree, "width");
	gameMap.width=node->valueint;
	gameMap.height = cJSON_GetObjectItem(tree, "height")->valueint;
	cJSON* layer_node = cJSON_GetObjectItem(tree, "layers");
	gameMap.layerCount = cJSON_GetArraySize(layer_node);

	gameMap.layers = (layer*)malloc(sizeof(layer) * gameMap.layerCount);

	for (int i = 0; i < gameMap.layerCount; i++)
	{
		//��ȡͼ�������ָ����Ա
		cJSON *layer=cJSON_GetArrayItem(layer_node, i);

		strcpy(gameMap.layers[i].name, cJSON_GetObjectItem(layer, "name")->valuestring);
		const char* type = cJSON_GetObjectItem(layer, "type")->valuestring;

		//����ͼ���
		if (strcmp(type, "tilelayer") == 0)
		{
			gameMap.layers[i].type = 0;
			//data_node�洢ÿ��ͼ��
			cJSON* data_node = cJSON_GetObjectItem(layer, "data");
			gameMap.layers[i].height = cJSON_GetObjectItem(layer, "height")->valueint;
			gameMap.layers[i].width = cJSON_GetObjectItem(layer, "width")->valueint;
			int count = cJSON_GetArraySize(data_node);

			gameMap.layers[i].tiles = (int*)malloc(sizeof(int) * count);
			if (gameMap.layers[i].tiles == NULL)
			{
				cout << "No Memory!" << endl;
				return false;
			}
			for (int k = 0; k < count; k++)
			{
				gameMap.layers[i].tiles[k] = cJSON_GetArrayItem(data_node, k)->valueint;
			}
		}

		//���������
		else if (strcmp(type, "objectgroup") == 0)
		{
			gameMap.layers[i].type = 1;
			//data_node�洢ÿ��ͼ��
			cJSON* object_node = cJSON_GetObjectItem(layer, "objects");
			gameMap.layers[i].objectsCount = cJSON_GetArraySize(object_node);
			gameMap.layers[i].objects = (struct object*)malloc(sizeof(struct object) * gameMap.layers[i].objectsCount);
			
			for (int k = 0; k < gameMap.layers[i].objectsCount; k++)
			{
				cJSON* object = cJSON_GetArrayItem(object_node, k);
				strcpy(gameMap.layers[i].objects[k].type, cJSON_GetObjectItem(object, "class")->valuestring);
				strcpy(gameMap.layers[i].objects[k].name, cJSON_GetObjectItem(object, "name")->valuestring);
				gameMap.layers[i].objects[k].x = cJSON_GetObjectItem(object, "x")->valuedouble;
				gameMap.layers[i].objects[k].y = cJSON_GetObjectItem(object, "y")->valuedouble;
			}
		}
	}

	gameMap.pixelWidth = gameMap.tileSet.tileWidth * gameMap.width;
	gameMap.pixelHeight = gameMap.tileSet.tileHeight * gameMap.height;

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
	int Row = gameMap.tileSet.row; int Col = gameMap.tileSet.col;
	int margin = gameMap.tileSet.margin;

	gameMap.imageTiles = new IMAGE[gameMap.tileSet.tileCount];
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			getimage(&gameMap.imageTiles[i * Col + j], margin + j * gameMap.tileSet.tileWidth,
				margin + i * gameMap.tileSet.tileHeight, gameMap.tileSet.tileWidth,
				gameMap.tileSet.tileHeight);
		}
	}
	SetWorkingImage();

	//��ͼ��ȡͼƬ
	gameMap.imgLayer = new IMAGE[gameMap.layerCount];
	for (int i = 0; i < gameMap.layerCount; i++)
	{
		gameMap.imgLayer[i].Resize(gameMap.pixelWidth, gameMap.pixelHeight);
		SetWorkingImage(&gameMap.imgLayer[i]);

		//�������ȡͼƬ
		if(gameMap.layers[i].type==1)
		{
			for (int k = 0; k < gameMap.layers[i].objectsCount; k++)
			{
				struct object* obj = &gameMap.layers[i].objects[k];
				int row = obj->y / gameMap.tileSet.tileHeight;
				int col = obj->x / gameMap.tileSet.tileWidth;
				int x = col * gameMap.tileSet.tileWidth;
				int y = row * gameMap.tileSet.tileHeight;

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
			for (int row = 0; row < gameMap.layers[i].height; row++)
			{
				for (int col = 0; col < gameMap.layers[i].width; col++)
				{
					int index = gameMap.layers[i].tiles[row * gameMap.layers[i].width + col];
					if (index == 0)continue;
					IMAGE* img = &gameMap.imageTiles[index - 1];
					putimage(col * gameMap.tileSet.tileWidth, row * gameMap.tileSet.tileHeight, img);
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

//���½���
void SuperMario::UpdateWindow()
{
	BeginBatchDraw();

	putimage(0, 0, &gameMap.imgBg);
	for (int i = 0; i < gameMap.layerCount; i++)
	{
		putimagePNG(gameMap.x, 0, &gameMap.imgLayer[i]);
	}

	EndBatchDraw();
}

//�û�����
int SuperMario::UserDo(string page)
{
	//��Ϸ�ڽ���
	if (page == "Game")
	{
		ExMessage msg;
		if (peekmessage(&msg) && msg.message == WM_KEYDOWN)
		{
			char c = _getch();
			if (c == 'd')
			{
				if (gameMap.x > -(gameMap.pixelWidth - gameMap.tileSet.tileWidth * 540))
				{
					gameMap.x -= 8;
				}
			}
		}
		return 0;
	}
	
	//��Ϸ�˵�����
	else if (page == "MarioMenu")
	{

	}
}

//��ʾ����
void SuperMario::ShowGameMenu()
{

}

//������Ϸ
void SuperMario::RunGame()
{
	TileInit();
	MapInit();
	CreateMap();

	if (0)
	{
		gameMap.imgBg.Resize(gameMap.tileSet.tileWidth * 960, gameMap.tileSet.tileWidth * 540);
		CreateImgLine(&gameMap.imgBg,"Graph/SuperMario/attack.png");
	}
	gameMap.x = 0;

	while (1)
	{
		UserDo("Game");
		UpdateWindow();
	}

	return;
}

//��������
SuperMario::~SuperMario()
{

}
