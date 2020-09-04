#pragma once

struct MARK
{
	XY pos;
	XY size;
	int aniCnt;
	int flag;
	STAGE_ID type;
	
};

bool MarkSystemInit(void);
bool MarkGameInit(void);
void MarkGameDraw(void);
void MarkGameControl(XY pos,int size);

bool MarkHitCheck(XY pPos,int size);
