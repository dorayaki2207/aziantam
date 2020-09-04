#pragma once

struct MARK
{
	XY pos;
	XY size;
	int aniCnt;
	int flag;
	
};

bool MarkSystemInit(void);
bool MarkGameInit(void);
void MarkGameDraw(void);

bool MarkHitCheck(STAGE_ID Id, XY pPos, XY size);
