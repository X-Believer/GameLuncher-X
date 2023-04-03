#include "SuperMario.h"

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

//������ͼ
bool SuperMario::MapInit()
{
	char* content= getFileContent("Graph/SuperMario/TileProject/Map1.tmj");
	cJSON* tree = cJSON_Parse(content);

	//����ʧ��
	if (tree == NULL)
	{
		return false;
	}

	//cJSON_GetObjectItem��ȡָ���ڵ��ֵ
	cJSON* node = cJSON_GetObjectItem(tree, "width");
	gameMap.width=node->valueint;
	gameMap.height = cJSON_GetObjectItem(tree, "width")->valueint;
	cJSON* layer_node = cJSON_GetObjectItem(tree, "layers");
	gameMap.layerCount = cJSON_GetArraySize(layer_node);

	gameMap.layers = (layer*)malloc(sizeof(layer) * gameMap.layerCount);

	for (int i = 0; i < gameMap.layerCount; i++)
	{
		//��ȡͼ�������ָ����Ա
		cJSON *layer=cJSON_GetArrayItem(layer_node, i);

		strcpy(gameMap.layers[i].name, cJSON_GetObjectItem(layer, "name")->valuestring);

		cJSON* data_node = cJSON_GetObjectItem(layer, "data");
		int count= cJSON_GetArraySize(data_node);

		gameMap.layers[i].tiles = (int*)malloc(sizeof(int) * count);
		for (int k = 0; k < count; k++)
		{
			gameMap.layers[i].tiles[k] = cJSON_GetArrayItem(data_node, k)->valueint;
		}

	}

	return true;
}

//��ʾ����
void SuperMario::ShowGameMenu()
{

}

//������Ϸ
void SuperMario::RunGame()
{

}
