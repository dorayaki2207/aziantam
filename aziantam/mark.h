#pragma once



//�\����
struct MARK
{
	XY pos;
	XY size;
	int aniCnt;
	int flag;
	int type;
};


//�v���g�^�C�v�錾
bool MarkSystemInit(void);
void MarkReGameInit(void);
bool MarkGameInit(void);
void MarkGameDraw(void);

void MarkControl();
bool MarkHitCheck(STAGE_ID Id, XY pPos, XY size);

extern MARK mark[];