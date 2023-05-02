#include "tools.h"
#include <stdio.h>
#include <string.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// 载入PNG图并去透明部分
//void _putimagePNG(int  picture_x, int picture_y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
//{
//	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
//	DWORD* draw = GetImageBuffer();
//	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
//	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
//	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
//	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
//	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
//	int dstX = 0;    //在显存里像素的角标
//
//	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
//	for (int iy = 0; iy < picture_height; iy++)
//	{
//		for (int ix = 0; ix < picture_width; ix++)
//		{
//			int srcX = ix + iy * picture_width; //在显存里像素的角标
//			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
//			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
//			int sg = ((src[srcX] & 0xff00) >> 8);   //G
//			int sb = src[srcX] & 0xff;              //B
//			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
//			{
//				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
//				int dr = ((dst[dstX] & 0xff0000) >> 16);
//				int dg = ((dst[dstX] & 0xff00) >> 8);
//				int db = dst[dstX] & 0xff;
//				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)
//					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)
//					| (sb * sa / 255 + db * (255 - sa) / 255);
//			}
//		}
//	}
//}


void putimageTMD(int  picture_x, int picture_y, IMAGE* picture, int tmd) //x为载入图片的X坐标，y为Y坐标
{
	if (picture_y < 0)return;
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			if (tmd < 255) {
				if (sa > 200) sa = tmd;
				else continue;
			}
			
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)
					| (sb * sa / 255 + db * (255 - sa) / 255);
			}
		}
	}
}

//// 适用于 y <0 以及x<0的任何情况
//void putimagePNG(int x, int y, IMAGE* picture) {
//
//	IMAGE imgTmp, imgTmp2, imgTmp3;
//	int winWidth = getwidth();
//	int winHeight = getheight();
//	if (y < 0) {
//		SetWorkingImage(picture);
//		getimage(&imgTmp, 0, -y,
//			picture->getwidth(), picture->getheight() + y);
//		SetWorkingImage();
//		y = 0;
//		picture = &imgTmp;
//	}
//	else if (y >= getheight() || x >= getwidth()) {
//		return;
//	}
//	else if (y + picture->getheight() > winHeight) {
//		SetWorkingImage(picture);
//		getimage(&imgTmp, x, y, picture->getwidth(), winHeight - y);
//		SetWorkingImage();
//		picture = &imgTmp;
//	}
//
//	if (x < 0) {
//		SetWorkingImage(picture);
//		getimage(&imgTmp2, -x, 0, picture->getwidth() + x, picture->getheight());
//		SetWorkingImage();
//		x = 0;
//		picture = &imgTmp2;
//	}
//
//	if (x > winWidth - picture->getwidth()) {
//		SetWorkingImage(picture);
//		getimage(&imgTmp3, 0, 0, winWidth - x, picture->getheight());
//		SetWorkingImage();
//		picture = &imgTmp3;
//	}
//
//
//	_putimagePNG(x, y, picture);
//}

int getDelay() {
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount();
	if (lastTime == 0) {
		lastTime = currentTime;
		return 0;
	}
	else {
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}
}

void setFont(const char* fontName, int fontWidth, int fontHeight) {
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = fontHeight;                      // 设置字体高度为 48
	f.lfWidth = fontWidth;
	strcpy(f.lfFaceName, fontName);    // 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	setbkmode(TRANSPARENT);
	settextstyle(&f);
}

void  preLoadSound(const char* name) {
	char cmd[512];
	sprintf_s(cmd, sizeof(cmd), "open %s alias %s-1", name, name);
	mciSendString(cmd, 0, 0, 0);
	sprintf_s(cmd, sizeof(cmd), "open %s alias %s-2", name, name);
	mciSendString(cmd, 0, 0, 0);
}

void  playSound(const char* name) {
	static int index = 1;
	char cmd[512];

	if (index == 1) {
		sprintf_s(cmd, sizeof(cmd), "play %s-1", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "close %s-2", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "open %s alias %s-2", name, name);
		mciSendString(cmd, 0, 0, 0);
		index++;
	}
	else if (index == 2) {
		sprintf_s(cmd, sizeof(cmd), "play %s-2", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "close %s-1", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "open %s alias %s-1", name, name);
		mciSendString(cmd, 0, 0, 0);
		index = 1;
	}
}

bool rectIntersect(int x01, int y01, int x02, int y02,
	int x11, int y11, int x12, int y12)
{
	int zx = abs(x01 + x02 - x11 - x12);
	int x = abs(x01 - x02) + abs(x11 - x12);
	int zy = abs(y01 + y02 - y11 - y12);
	int y = abs(y01 - y02) + abs(y11 - y12);
	return  (zx <= x && zy <= y);
}