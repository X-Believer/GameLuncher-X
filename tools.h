#pragma once
#include <graphics.h>

void putimageTMD(int  picture_x, int picture_y, IMAGE* picture, int tmd);
int getDelay();
void setFont(const char* fontName, int fontWidth, int fontHeight);
void  preLoadSound(const char* name);
void  playSound(const char* name);
bool rectIntersect(int x01, int y01, int x02, int y02,
	int x11, int y11, int x12, int y12);