#include "SuperMario.h"

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

//解析地图
bool SuperMario::MapInit()
{
	char* content= getFileContent("Graph/SuperMario/TileProject/Map1.tmj");
	cJSON* tree = cJSON_Parse(content);

	//解析失败
	if (tree == NULL)
	{
		return false;
	}

	//cJSON_GetObjectItem获取指定节点的值
	cJSON* node = cJSON_GetObjectItem(tree, "width");
	gameMap.width=node->valueint;
	gameMap.height = cJSON_GetObjectItem(tree, "width")->valueint;
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
			cJSON* data_node = cJSON_GetObjectItem(layer, "data");
			gameMap.layers[i].height = cJSON_GetObjectItem(layer, "height")->valueint;
			gameMap.layers[i].width = cJSON_GetObjectItem(layer, "width")->valueint;
			int count = cJSON_GetArraySize(data_node);

			gameMap.layers[i].tiles = (int*)malloc(sizeof(int) * count);
			for (int k = 0; k < count; k++)
			{
				gameMap.layers[i].tiles[k] = cJSON_GetArrayItem(data_node, k)->valueint;
			}
		}


	}

	return true;
}

//显示设置
void SuperMario::ShowGameMenu()
{

}

//运行游戏
void SuperMario::RunGame()
{

}
