#pragma once



//構造体
struct MARK
{
	XY pos;
	XY size;
	int aniCnt;
	int flag;
	int type;
};


//プロトタイプ宣言
bool MarkSystemInit(void);
void MarkReGameInit(void);
bool MarkGameInit(void);
void MarkGameDraw(void);

void MarkControl();
bool MarkHitCheck(STAGE_ID Id, XY pPos, XY size);

extern MARK mark[];