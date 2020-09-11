#pragma once



//構造体
struct MARK
{
	XY pos;
	XY size;
	int aniCnt;
	int flag;
	
};


//プロトタイプ宣言
bool MarkSystemInit(void);
bool MarkGameInit(void);
void MarkGameDraw(void);

bool MarkHitCheck(STAGE_ID Id, XY pPos, XY size);

extern MARK mark[];