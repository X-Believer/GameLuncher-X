#include "SuperMario.h"

namespace
{
	//对象物体
	struct object
	{
		double x;
		double y;
		char* type;
		char* name;
	};

	//每个地图图层
	struct layer
	{
		char name[32];
		int* tiles;
		int width;
		int height;
		int type;
		//type:[0]图块层；[1]对象层；[2]图像层
		int objectsCount;
		object* objects;
	};

	//地图集
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

	//地图
	struct MarioMap
	{
		int width;//单位:图块(42*42)
		int height;
		int pixelWidth;//像素宽高
		int pixelHeight;
		int x;//地图位移
		int y;

		struct tileset tileSet;
		struct layer* layers;//存储图层信息
		int layerCount;

		IMAGE* imageTiles;//存储每个图块图片
		IMAGE* imgLayer;//存储每个图层图片
		IMAGE imgBg;
	};

	MarioMap gameMap;//当前加载的地图变量

	string NowLevel = "Graph/SuperMario/TileProject/LevelMap/Level1-1.tmj";
	string NowTileSet = "Graph/SuperMario/TileProject/MapSet.tsj";
	string NowTilePic = "Graph/SuperMario/TileProject/tileset.png";

	int NowDis = 0;

	IMAGE TilePic; IMAGE test;
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

//解析地图
bool SuperMario::MapInit()
{
	char* content= getFileContent(NowLevel.c_str());
	cJSON* tree = cJSON_Parse(content);

	//解析失败
	if (tree == NULL)
	{
		return false;
	}

	//cJSON_GetObjectItem获取指定节点的值
	cJSON* node = cJSON_GetObjectItem(tree, "width");
	gameMap.width=node->valueint;
	gameMap.height = cJSON_GetObjectItem(tree, "height")->valueint;
	cJSON* layer_node = cJSON_GetObjectItem(tree, "layers");
	gameMap.layerCount = cJSON_GetArraySize(layer_node);

	gameMap.layers = (layer*)malloc(sizeof(layer) * gameMap.layerCount);

	for (int i = 0; i < gameMap.layerCount; i++)
	{
		//获取图层数组的指定成员
		cJSON *layer=cJSON_GetArrayItem(layer_node, i);

		strcpy(gameMap.layers[i].name, cJSON_GetObjectItem(layer, "name")->valuestring);
		const char* type = cJSON_GetObjectItem(layer, "type")->valuestring;

		//解析图块层
		if (strcmp(type, "tilelayer") == 0)
		{
			gameMap.layers[i].type = 0;
			//data_node存储每个图块
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

		//解析对象层
		else if (strcmp(type, "objectgroup") == 0)
		{
			gameMap.layers[i].type = 1;
			//data_node存储每个图块
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

//创建地图
void SuperMario::CreateMap()
{
	//图片集提取图片
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

	//地图提取图片
	gameMap.imgLayer = new IMAGE[gameMap.layerCount];
	for (int i = 0; i < gameMap.layerCount; i++)
	{
		gameMap.imgLayer[i].Resize(gameMap.pixelWidth, gameMap.pixelHeight);
		SetWorkingImage(&gameMap.imgLayer[i]);

		//对象层提取图片
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

		//图块层提取图片
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

//更新界面
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

//用户交互
void SuperMario::UserDo()
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
}

//显示设置
void SuperMario::ShowGameMenu()
{

}

//运行游戏
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
	loadimage(&test, "Graph/SuperMario/attack.png");
	while (1)
	{
		putimage(0,0,&test);
		UserDo();
		UpdateWindow();
	}

	return;
}

//析构函数
SuperMario::~SuperMario()
{

}
