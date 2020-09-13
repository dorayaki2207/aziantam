#pragma once





#define ZINGI_OLD  0
#define ZINGI_NEW  1


//列挙型
enum ITEM_TYPE_B
{
	ITEM_TYPE_KEN,				//	三種の神器・剣
	ITEM_TYPE_KAGAMI,			//	三種の神器・鏡
	ITEM_TYPE_MAGATAMA,			//	三種の神器・勾玉
	ITEM_TYPE_B_MAX
};


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